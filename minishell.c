/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:48:50 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/10 16:38:36 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printing_prompt(minishell_t *line)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_error("Error while finding the current work directory\n");
	line->prompt = malloc(ft_strlen(cwd) + 4);
	if (!line->prompt)
	{
		free(cwd);
		ft_error("Error while allocating memory\n");
	}
	ft_strlcpy(line->prompt, cwd, ft_strlen(line->prompt) + ft_strlen(cwd) + 1);
	ft_strlcat(line->prompt, " % ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt); //this function already prints by itself
	free(cwd);
}

void	input_check(minishell_t *line)
{
	if (line->input[0] == '\0') //checks if the user just used enter without typing anything
		return ;
	else if (ft_strncmp(line->input, "exit") == 0) //checks if the user typed exit, if so, it exits the whole program with exit
		exit(EXIT_SUCCESS);
	else
		printf("%s\n", line->input); //else prints out user input
}
