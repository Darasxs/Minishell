/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/29 12:17:32 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_process(t_ms *ms, int i, int *input_fd, int *fd)
{
	if (setup_sigquit() != 0)
	{
		free_struct(ms);
		return ;
	}
	if(check_if_redirections(ms))
		handle_redirections(ms);
	if (ms->heredoc == true)
	{
		if (dup2(ms->heredoc_file_descriptor, STDIN_FILENO) == -1)
		{
			write(STDERR_FILENO,
				"Error duplicating file descriptor for heredoc\n", 47);
			close(ms->heredoc_file_descriptor);
			ms->heredoc_file_descriptor = -1;
			return ;
		}
		execute_command(ms);
		close(ms->heredoc_file_descriptor);
		ms->heredoc_file_descriptor = -1;
		ms->heredoc = false;
	}
	else
	{
		if (i > 0)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		if (ms->split_pipes[i + 1])
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		close(fd[0]);
		if (check_builtin(ms))
			handle_builtins(ms, i, input_fd, fd);
		else
			execute_command(ms);
	}
	exit(0);
}

void	handle_parent_process(t_ms *ms, int i, int *input_fd, int *fd)
{
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

void	execute_pipe_commands(t_ms *ms, int *input_fd, int i)
{
	int		fd[2];
	pid_t	pid;

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

void	minishell(t_ms *ms)
{
	int		status;
	int		input_fd;
	size_t	i;
	t_token	*token;

	input_fd = STDIN_FILENO;
	i = 0;
	token = ms->token;
	create_split_pipes(ms, token);
	if (setup_sigint_ignore() != 0)
	{
		free_struct(ms);
		return ;
	}
	while (ms->split_pipes[i])
	{
		token = create_split_commands(ms, token);
		i++;
	}
	i = 0;
	while (ms->split_commands[i])
	{
		if (ms->split_commands[i][0] == '<' && ms->split_commands[i][1] == '<')
			handle_double_input(ms, i);
		i++;
	}
	i = 0;
	token = ms->head;
	while (ms->split_pipes[i])
	{
		token = create_split_commands(ms, token);
		execute_pipe_commands(ms, &input_fd, i);
		free_split(ms->split_commands);
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->exit_status = 128 + WTERMSIG(status);
	}
	free_list(ms, ms->token);
	if (setup_sigint() != 0)
	{
		free_struct(ms);
		return ;
	}
}
