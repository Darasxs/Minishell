/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:48:50 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/11 18:03:15 by dpaluszk         ###   ########.fr       */
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
	ft_strlcpy(line->prompt, cwd, ft_strlen(cwd) + 4); // changed this
	ft_strlcat(line->prompt, " % ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt);
	line->split = ft_split(line->input, ' ');
	free(cwd);
}

//void	input_check(minishell_t *line)
//{
//	if (line->input[0] == '\0') //checks if the user just used enter without typing anything
//		return ;
//	else if (ft_strncmp(line->input, "exit") == 0) //checks if the user typed exit, if so, it exits the whole program with exit
//		exit(EXIT_SUCCESS);
//	else
//		printf("%s\n", line->input); //else prints out user input
//}
