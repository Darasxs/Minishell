/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/29 15:39:13 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BUFFER_SIZE 1024

void	handle_double_input(t_ms *ms, size_t i)
{
	const char	*temp_filename;
	char		*eof_delimiter;
	char		*buffer;

	ms->heredoc = true;
	temp_filename = ".temporary_heredoc_file";
	eof_delimiter = ms->split_commands[i + 1];
	ms->heredoc_file_descriptor = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ms->heredoc_file_descriptor == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
		return ;
	}
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
			return ;
		//if (buffer[ft_strlen(buffer - 1)] == '\n')
		//	buffer[ft_strlen(buffer - 1)] = '\0';
		if (ft_strncmp(buffer, eof_delimiter, ft_strlen(eof_delimiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(eof_delimiter))
			break ;

		write(ms->heredoc_file_descriptor, buffer, ft_strlen(buffer));
		write(ms->heredoc_file_descriptor, "\n", 1);
	}
	close(ms->heredoc_file_descriptor);
	ms->heredoc_file_descriptor = open(temp_filename, O_RDONLY);
	if (ms->heredoc_file_descriptor == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
	}
	//if (dup2(ms->heredoc_file_descriptor, STDIN_FILENO) == -1)
	//{
	//	write(STDERR_FILENO, "Error duplicating file descriptor for heredoc\n",
	//		47);
	//	close(ms->heredoc_file_descriptor);
	//	return ;
	//}
	//ms->heredoc = false;
	unlink(temp_filename);

	//execute_command(ms);
}
