/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:36:19 by daras             #+#    #+#             */
/*   Updated: 2024/09/17 17:51:51 by paprzyby         ###   ########.fr       */
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
		ft_error("Error while allocating memory\n", NULL, line);
	}
	ft_strlcpy(line->prompt, user_name, ft_strlen(user_name) + 1);
	ft_strlcat(line->prompt, " @ ", ft_strlen(line->prompt) + 4);
	ft_strlcat(line->prompt, split_cwd[i - 1], ft_strlen(line->prompt)
		+ ft_strlen(split_cwd[i - 1]) + 1);
	ft_strlcat(line->prompt, " $ ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt);
	free(cwd);
}
