/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/14 18:35:23 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtins(t_minishell *ms, int i, int *input_fd, int *fd)
{
	int	j;

	j = 0;
	while (ms->split_pipes[j])
		j++;
	if (ft_strncmp(ms->split_commands[0], "cd", 3) == 0)
	{
		if (j == 1 || i == j - 1)
			cd_builtin(ms);
	}
	execute_builtin(ms);
	if (ms->split_pipes[i + 1])
	{
		close(fd[1]);
		*input_fd = fd[0];
	}
}

void	handle_child_process(t_minishell *ms, int i, int *input_fd, int *fd)
{
	if (i > 0)
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	//else if (ms->input_fd != -1)
	//{
	//	dup2(ms->input_fd, STDIN_FILENO);
	//	close(ms->input_fd);
	//}
	if (ms->split_pipes[i + 1])
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	//else if (ms->output_fd != -1)
	//{
	//	dup2(ms->output_fd, STDOUT_FILENO);
	//	close(ms->output_fd);
	//}
	close(fd[0]);
	if	(check_if_redirections(ms))
		handle_redirections(ms);
	execute_command(ms);
	exit(0);
}

void	handle_parent_process(t_minishell *ms, int i, int *input_fd, int *fd)
{
	//if (ms->input_fd != -1)
	//{
	//	close(ms->input_fd);
	//	ms->input_fd = -1;
	//}
	//if (ms->output_fd != -1)
	//{
	//	close(ms->output_fd);
	//	ms->output_fd = -1;
	//}
	if (ms->split_pipes[i + 1])
	{
		close(fd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = fd[0];
	}
	else
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		close(fd[0]);
	}
}

void	execute_pipe_commands(t_minishell *ms, int *input_fd, int i)
{
	int		fd[2];
	pid_t	pid;

	if (ms->split_pipes[i + 1] && pipe(fd) == -1)
		ft_error("Error occurred while creating a pipe\n", ms);
	if (check_builtin(ms))
		handle_builtins(ms, i, input_fd, fd);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error("Error occurred while forking\n", ms);
		else if (pid == 0)
			handle_child_process(ms, i, input_fd, fd);
		else
			handle_parent_process(ms, i, input_fd, fd);
	}
}

void	minishell(t_minishell *ms)
{
	int		status;
	int		input_fd;
	size_t	i;

	input_fd = STDIN_FILENO;
	i = 0;
	while (ms->split_pipes[i])
	{
		ms->split_commands = ft_split(ms->split_pipes[i], ' ');
		execute_pipe_commands(ms, &input_fd, i);
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
	}
}
