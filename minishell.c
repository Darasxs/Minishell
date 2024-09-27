/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 01:17:37 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_helper(char **cwd, char **user_name, minishell_t *line)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
		ft_error("Error while finding the current work directory\n", NULL, line);
	*user_name = getenv("USER");
	if (!*user_name)
		ft_error("Error while finding the user name\n", NULL, line);
}

void	printing_prompt(minishell_t *line)
{
	char	*cwd;
	char	*user_name;
	char	**split_cwd;
	size_t	i;

	i = 0;
	prompt_helper(&cwd, &user_name, line);
	split_cwd = ft_split(cwd, '/');
	while (split_cwd[i])
		i++;
	line->prompt = malloc(ft_strlen(split_cwd[i - 1]) + 4);
	if (!line->prompt)
	{
		free(split_cwd);
		ft_error("Error while allocating the memory\n", NULL, line);
	}
	ft_strlcpy(line->prompt, user_name, ft_strlen(user_name) + 1);
	ft_strlcat(line->prompt, " @ ", ft_strlen(line->prompt) + 4);
	ft_strlcat(line->prompt, split_cwd[i - 1], ft_strlen(line->prompt)
		+ ft_strlen(split_cwd[i - 1]) + 1);
	ft_strlcat(line->prompt, " $ ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt);
	free(cwd);
}

void	minishell(minishell_t *line)
{
	size_t	i;
	char	**commands;
	int		status;
	int		input_fd;

	i = 0;
	input_fd = STDIN_FILENO;
	printing_prompt(line);
	if (line->input)
	{
		add_history(line->input);
		commands = ft_split(line->input, '|');
		while (commands[i])
		{
			execute_pipe_commands(line, commands, i, &input_fd);
			i++;
		}
		while (waitpid(-1, &status, 0) > 0)
		{
			if(WIFEXITED(status))
				line->exit_status = WEXITSTATUS(status);
		}
		free_split(commands);
	}
}
