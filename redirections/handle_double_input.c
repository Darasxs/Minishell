/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/27 11:41:10 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BUFFER_SIZE 1024

void	handle_double_input(t_ms *ms, size_t i)
{
	const char	*temp_filename;
	char		*eof_delimiter;
	int			file_descriptor;
	ssize_t		bytes_read;
	char		buffer[1024];

	temp_filename = ".temporary_heredoc_file";
	eof_delimiter = ms->split_commands[i + 1];
	file_descriptor = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_descriptor == -1)
	{
		write(2, "Error openin heredoc temporary file.\n", 38);
		return ;
	}
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (buffer[bytes_read - 1] == '\n')
		{
			buffer[bytes_read - 1] = '\0';
			bytes_read--;
		}
		if (ft_strncmp(buffer, eof_delimiter, ft_strlen(eof_delimiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(eof_delimiter))
			break ;
		write(file_descriptor, buffer, bytes_read);
		write(file_descriptor, "\n", 1);
	}
	close(file_descriptor);
	file_descriptor = open(temp_filename, O_RDONLY);
	if (file_descriptor == -1)
	{
		write(STDERR_FILENO,
			"Error opening heredoc temporary file for reading\n", 50);
		return ;
	}
	if (dup2(file_descriptor, STDIN_FILENO) == -1)
	{
		write(STDERR_FILENO, "Error duplicating file descriptor for heredoc\n",
			47);
		close(file_descriptor);
		return ;
	}
	close(file_descriptor);
	unlink(temp_filename);
}
