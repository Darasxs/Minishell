/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:52:47 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/18 10:14:14 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt_helper(char **cwd, char **user_name, t_ms *ms)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
		ft_error("Error while finding the current working directory\n", ms);
	*user_name = getenv("USER");
	if (!*user_name)
		ft_error("Error while finding the user name\n", ms);
}

void	printing_prompt(t_ms *ms)
{
	char	*cwd;
	char	*user_name;
	char	**split_cwd;
	size_t	i;

	i = 0;
	prompt_helper(&cwd, &user_name, ms);
	split_cwd = ft_split(cwd, '/');
	while (split_cwd[i])
		i++;
	ms->prompt = malloc(ft_strlen(split_cwd[i - 1]) + 4);
	if (!ms->prompt)
	{
		free(split_cwd);
		ft_error("Error while allocating the memory\n", ms);
	}
	ft_strlcpy(ms->prompt, user_name, ft_strlen(user_name) + 1);
	ft_strlcat(ms->prompt, " @ ", ft_strlen(ms->prompt) + 4);
	ft_strlcat(ms->prompt, split_cwd[i - 1], ft_strlen(ms->prompt)
		+ ft_strlen(split_cwd[i - 1]) + 1);
	ft_strlcat(ms->prompt, " $ ", ft_strlen(ms->prompt) + 4);
	ms->input = readline(ms->prompt);
	free(cwd);
}
