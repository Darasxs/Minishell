/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:27:39 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/24 16:48:31 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cd_and_unset(t_ms *ms, int i, int *input_fd, int *fd)
{
	int	j;

	j = 0;
	if (check_if_redirections(ms))
		handle_redirections(ms);
	while (ms->split_pipes[j])
		j++;
	if (ft_strncmp(ms->split_commands[0], "cd", 3) == 0)
	{
		if (j == 1 || i == j - 1)
			cd_builtin(ms);
	}
	else if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1])
		unset_builtin(ms);
	if (ms->split_pipes[i + 1])
	{
		close(fd[1]);
		*input_fd = fd[0];
	}
}

void	handle_builtins(t_ms *ms, int i, int *input_fd, int *fd)
{
	if (check_if_redirections(ms))
		handle_redirections(ms);
	if (ms->split_pipes[i + 1])
	{
		close(fd[1]);
		*input_fd = fd[0];
	}
	execute_builtin(ms);
}
void	execute_builtin(t_ms *ms)
{
	if (!ms->split_commands[0])
		return ;
	else if (ft_strncmp(ms->split_commands[0], "exit", 5) == 0)
		exit_builtin(ms);
	else if (ft_strncmp(ms->split_commands[0], "echo", 5) == 0)
		echo_builtin(ms, ms->token->next);
	else if (ft_strncmp(ms->split_commands[0], "pwd", 4) == 0)
		pwd_builtin(ms);
	else
		export_builtin(ms);
}
bool	check_cd_and_unset(t_ms *ms)
{
	if (ft_strncmp(ms->split_commands[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1])
		return (true);
	return (false);
}
bool	check_builtin(t_ms *ms)
{
	if (!ms->split_commands[0])
		return (false);
	else if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1])
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "exit", 5) == 0)
		return (true);
	else if (ft_strrchr(ms->split_commands[0], '=') != 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "pwd", 4) == 0)
		return (true);
	return (false);
}
