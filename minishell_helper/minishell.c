/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/10 19:18:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtins(t_minishell *ms, t_token *token, int *input_fd, int *fd)
{
	size_t	j;

	j = 0;
	while (token->value[j])
		j++;
	if (ft_strncmp(token->value, "cd", 3) == 0)
	{
		//if (j == 1 || i == j - 1)
			cd_builtin(ms, token);
	}
	execute_builtin(ms, token);
	if (token->next->value)
	{
		close(fd[1]);
		*input_fd = fd[0];
	}
}

void	handle_child_process(t_minishell *ms, t_token *token, int *input_fd, int *fd)
{
	if (ms->first_iteration)
		ms->first_iteration = false;
	else
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	//else if (ms->input_fd != -1)
	//{
	//	dup2(ms->input_fd, STDIN_FILENO);
	//	close(ms->input_fd);
	//}
	if (token->next->value)
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
	if (ft_strncmp(token->value, "env", 3) == 0)
		env_builtin(ms);
	else if (token->value[0] == '.' && token->value[1] == '/')
		execute_program_name(ms, token);
	else
		execute_command(ms, token);
	exit(0);
}

void	handle_parent_process(t_token *token, int *input_fd, int *fd)
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
	if (token->next)
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

void	execute_pipe_commands(t_minishell *ms, t_token *token, int *input_fd)
{
	int		fd[2];
	pid_t	pid;

	if (token->next && pipe(fd) == -1)
		ft_error("Error occurred while creating a pipe\n", ms);
	if (check_builtin(ms, token))
		handle_builtins(ms, token, input_fd, fd);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error("Error occurred while forking\n", ms);
		else if (pid == 0)
			handle_child_process(ms, token, input_fd, fd);
		else
			handle_parent_process(token, input_fd, fd);
	}
}

void	minishell(t_minishell *ms, t_token *token)
{
	int		status;
	int		input_fd;
	size_t	i;

	input_fd = STDIN_FILENO;
	i = 0;
	// splitted by pipes instead of spaces
	while (ms->split_commands[i])
	{
		printf("%s\n", ms->split_commands[i]);
		execute_pipe_commands(ms, token, &input_fd);
		token = token->next;
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
	}
}
