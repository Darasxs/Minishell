/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:52:47 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/06 19:18:47 by dpaluszk         ###   ########.fr       */
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

void	prompt_root(t_ms *ms, char *user_name)
{
	ms->prompt = malloc(sizeof(char) * (ft_strlen(user_name) + 8));
	if (!ms->prompt)
		ft_error("Error while allocating the memory\n", ms);
	ft_strlcpy(ms->prompt, user_name, ft_strlen(user_name) + 1);
	ft_strlcat(ms->prompt, " @ / $ ", ft_strlen(ms->prompt) + 8);
}

void	connect_prompt(t_ms *ms, size_t prompt_len, size_t i, char **split_cwd)
{
	ft_strlcpy(ms->prompt, ms->user_name, prompt_len);
	ft_strlcat(ms->prompt, " @ ", prompt_len);
	ft_strlcat(ms->prompt, split_cwd[i - 1], prompt_len);
	ft_strlcat(ms->prompt, " $ ", prompt_len);
}

void	prompt_cleanup(t_ms *ms, char **split_cwd, char *cwd)
{
	free(cwd);
	free(ms->prompt);
	free(ms->user_name);
	free_split(split_cwd);
}

void	prompt(t_ms *ms)
{
	char	*cwd;
	char	*user_name;
	size_t	i;
	size_t	prompt_len;
	char	**split_cwd;

	i = 0;
	prompt_helper(&cwd, &user_name, ms);
	ms->user_name = user_name;
	split_cwd = ft_split(cwd, '/');
	if (!split_cwd[0])
		prompt_root(ms, user_name);
	else
	{
		while (split_cwd[i])
			i++;
		prompt_len = ft_strlen(user_name) + 3 + ft_strlen(split_cwd[i - 1]) + 3
			+ 1;
		ms->prompt = malloc(sizeof(char) * prompt_len);
		if (!ms->prompt)
			ft_error("Error while allocating the memory\n", ms);
		connect_prompt(ms, prompt_len, i, split_cwd);
	}
	ms->input = readline(ms->prompt);
	prompt_cleanup(ms, split_cwd, cwd);
}
