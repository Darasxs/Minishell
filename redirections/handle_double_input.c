/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/10 19:31:48 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_double_input(t_minishell *ms, size_t i)
{
	char	*temp_filename;
	char	*EOF_delimiter;
	char	*input;
	int		file_descriptor;

	temp_filename = ".temporary_heredoc_file";
	EOF_delimiter = ms->split_commands[i + 1];
	file_descriptor = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!file_descriptor)
		ft_error("Error with '<<'.\n", ms);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break;// tu nie wiem czy break czy moze jakis ft_error lub cos podobnego
		if (ft_strncmp(input, EOF_delimiter, ft_strlen(input - 1)) == 0)
		{
			free(input);
			break ;
		}
		write(file_descriptor, input, ft_strlen(input));
		free(input);
	}
	close(file_descriptor);
	file_descriptor = open(temp_filename, O_RDONLY);
	if (file_descriptor == -1)
		ft_error("Error while opening temporary heredoc file.\n", ms);
	if (dup2(file_descriptor, STDIN_FILENO) == -1)
	{
		close(file_descriptor);
		ft_error("error with file descriptor '<<'.\n", ms);
	}
	close(file_descriptor);
	unlink(temp_filename);
}
