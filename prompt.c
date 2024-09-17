/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daras <daras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:36:19 by daras             #+#    #+#             */
/*   Updated: 2024/09/16 15:36:33 by daras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_helper(char **cwd, char **user_name)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
		ft_error("Error while finding the current work directory\n", NULL);
	*user_name = getenv("USER");
	if (!*user_name)
		ft_error("Error while finding the user name\n", NULL);
}

void	printing_prompt(minishell_t *line)
{
	char	*cwd;
	char	*user_name;
	char	**split_cwd;
	size_t	i;

	i = 0;
	prompt_helper(&cwd, &user_name);
	split_cwd = ft_split(cwd, '/');
	while (split_cwd[i])
		i++;
	line->prompt = malloc(ft_strlen(split_cwd[i - 1]) + 4);
	if (!line->prompt)
	{
		free(split_cwd);
		ft_error("Error while allocating memory\n", NULL);
	}
	ft_strlcpy(line->prompt, user_name, ft_strlen(user_name) + 1);
	ft_strlcat(line->prompt, " @ ", ft_strlen(line->prompt) + 4);
	ft_strlcat(line->prompt, split_cwd[i - 1], ft_strlen(line->prompt)
		+ ft_strlen(split_cwd[i - 1]) + 1);
	ft_strlcat(line->prompt, " % ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt);
	free(cwd);
}
