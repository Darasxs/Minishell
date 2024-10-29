/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:52:47 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/29 15:45:31 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prompt_helper(char **cwd, char **user_name, t_ms *ms)
{
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		ft_putstr_fd("Error while finding the current working directory\n", 2);
		ms->exit_status = 1;
		exit(ms->exit_status);
	}
	*user_name = ft_getenv("USER", ms);
	if (!*user_name)
	{
		ft_putstr_fd("Error while finding the user name\n", 2);
		ms->exit_status = 1;
		exit(ms->exit_status);
	}
}

void	prompt(t_ms *ms)
{
	char	*cwd;
	char	*user_name;
	char	**split_cwd;
	size_t	i;

	i = 0;
	prompt_helper(&cwd, &user_name, ms);
	split_cwd = ft_split(cwd, '/');
	if (!split_cwd[0])
	{
		ms->prompt = malloc(5);
		if (!ms->prompt)
			ft_error("Error while allocating the memory\n", ms);
		ft_strlcpy(ms->prompt, user_name, ft_strlen(user_name) + 1);
		ft_strlcat(ms->prompt, " @ / $ ", ft_strlen(ms->prompt) + 8);
		ms->input = readline(ms->prompt);
		free(cwd);
	}
	else
	{
		while (split_cwd[i])
			i++;
		ms->prompt = malloc(ft_strlen(split_cwd[i - 1]) + 4);
		if (!ms->prompt)
			ft_error("Error while allocating the memory\n", ms);
		ft_strlcpy(ms->prompt, user_name, ft_strlen(user_name) + 1);
		ft_strlcat(ms->prompt, " @ ", ft_strlen(ms->prompt) + 4);
		ft_strlcat(ms->prompt, split_cwd[i - 1], ft_strlen(ms->prompt)
			+ ft_strlen(split_cwd[i - 1]) + 1);
		ft_strlcat(ms->prompt, " $ ", ft_strlen(ms->prompt) + 4);
		ms->prompt[ft_strlen(ms->prompt)] = '\0';
		ms->input = readline(ms->prompt);
		free(cwd);
	}
}
