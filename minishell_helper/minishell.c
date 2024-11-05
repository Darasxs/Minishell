/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/05 18:33:37 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_process(t_ms *ms, int i, int *input_fd, int *fd)
{
	if (setup_sigquit() != 0)
		return (ft_putstr_fd("Error\n", 2));
	if (ms->heredoc_found == true)
		heredoc_setup(ms, i);
	if (check_if_redirections(ms))
		handle_redirections(ms);
	if (!ms->heredoc_found && i > 0)
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	if (ms->split_pipes[i + 1])
	{
		dup2(fd[1], STDOUT_FILENO);
		if (fd[1] != -1)
			close(fd[1]);
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (check_builtin(ms))
		handle_builtins(ms, i, input_fd, fd);
	else
		execute_command(ms);
	exit(ms->exit_status);
}

void	handle_parent_process(t_ms *ms, int i, int *input_fd, int *fd)
{
	if (ms->split_pipes[i + 1])
	{
		if (fd[1] != -1)
			close(fd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = fd[0];
	}
	else
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		if (fd[0] != -1)
			close(fd[0]);
	}
}

void	execute_pipe_commands(t_ms *ms, int *input_fd, int i)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (ms->split_pipes[i + 1] && pipe(fd) == -1)
		ft_error("Error occurred while creating a pipe\n", ms);
	check_exit_code(ms);
	if (check_cd_and_unset(ms))
		handle_cd_and_unset(ms, i, input_fd, fd);
	else if (ft_strncmp(ms->split_commands[0], "exit", 5) == 0)
		exit_builtin(ms);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			free(ms->input);
			ft_error("Error occurred while forking\n", ms);
		}
		else if (pid == 0)
			handle_child_process(ms, i, input_fd, fd);
		else
			handle_parent_process(ms, i, input_fd, fd);
	}
}

void	execution(t_ms *ms)
{
	int		input_fd;
	size_t	i;
	t_token	*token;

	input_fd = STDIN_FILENO;
	i = 0;
	token = ms->head;
	while (ms->split_pipes[i])
	{
		token = create_split_commands(ms, token);
		if (!syntax_check(ms))
			return ;
		expand_env(ms);
		execute_pipe_commands(ms, &input_fd, i);
		free_split(ms->split_commands);
		i++;
	}
}

void	minishell(t_ms *ms)
{
	t_token	*token;

	token = ms->head;
	create_split_pipes(ms, token);
	if (setup_sigint_ignore() != 0)
		return (ft_putstr_fd("Error\n", 2));
	double_input_check(ms);
	execution(ms);
	while (waitpid(-1, &ms->status, 0) > 0)
	{
		if (WIFEXITED(ms->status))
			ms->exit_status = WEXITSTATUS(ms->status);
		else if (WIFSIGNALED(ms->status))
			ms->exit_status = 128 + WTERMSIG(ms->status);
	}
	if (ms->heredoc_found == true)
		cleanup_heredocs(ms);
	free_split(ms->split_pipes);
	if (setup_sigint() != 0)
		return (ft_putstr_fd("Error\n", 2));
}
