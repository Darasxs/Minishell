/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/11 17:21:11 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_cleanup(t_minishell *ms, t_token *token)
{
	size_t	i;

	i = 0;
	while (token->value)
	{
		free(token->value);
		token->value = NULL;
		token = token->next;
	}
	free(token);
	ms->double_q = 0;
	ms->single_q = 0;
	ms->first_iteration = true;
	ms->input_pos = 0;
	ms->pipe = false;
	ms->token_count = 0;
}

int	count_pipe_len(t_token *token)
{
	int		len;
	int		i;

	len = 0;
	while (token->value[0] != '|' && token->value)
	{
		i = 0;
		while (token->value[i])
		{
			i++;
			len++;
		}
		if (!token->next->value)
			return (len);
		else if (token->next->value[0] != '|')
			len++;
		token = token->next;
	}
	return (len);
}

void	create_split_pipes(t_minishell *ms, t_token *token)
{
	t_token	*head;
	int		i;
	int		pipes_count;
	int		len;

	head = token;
	pipes_count = 1;
	while (token->value)
	{
		if (token->value[0] == '|')
			pipes_count++;
		token = token->next;
	}
	ms->split_pipes = malloc(sizeof(char *) * (pipes_count + 1));
	if (!ms->split_pipes)
		ft_error("Error while allocating the memory\n", ms);
	token = head;
	i = 0;
	len = 0;
	while (i < pipes_count && token->value)
	{
		if (token->value[0] != '|')
		{
			len = count_pipe_len(token);
			ms->split_pipes[i] = malloc(sizeof(char) * (len + 1));
			if (!ms->split_pipes[i])
				ft_error("Error while allocating the memory\n", ms);
			while (token->value && token->value[0] != '|')
			{
				ft_strlcat(ms->split_pipes[i], token->value,
					ft_strlen(token->value) + ft_strlen(ms->split_pipes[i])
					+ 1);
				if (token->next)
					ft_strlcat(ms->split_pipes[i], " ",
						ft_strlen(ms->split_pipes[i]) + 2);
				token = token->next;
			}
			i++;
		}
		token = token->next;
	}
	ms->split_pipes[i] = NULL;
	token = head;
}

void	create_split_commands(t_minishell *ms, t_token *token)
{
	int	i;

	ms->split_commands = malloc(sizeof(char *) * (ms->token_count + 1));
	if (!ms->split_commands)
		ft_error("Error while allocating the memory\n", ms);
	i = 0;
	while (i < ms->token_count && token)
	{
		if (token->value[0] != '|')
		{
			ms->split_commands[i] = ft_strdup(token->value);
			if (!ms->split_commands[i])
			{
				while (i--)
					free(token->value);
				free(token->value);
				exit(1);
			}
			i++;
		}
		token = token->next;
	}
	ms->split_commands[i] = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	if (ac != 1)
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		return (1);
	}
	ms = minishell_init(envp);
	while (1)
	{
		printing_prompt(ms);
		if (ms->input)
		{
			add_history(ms->input);
			ms->token = parsing(ms);
			create_split_pipes(ms, ms->token);
			create_split_commands(ms, ms->token);
			minishell(ms, ms->token);
			parsing_cleanup(ms, ms->token);
		}
	}
	free_struct(ms);
	return (0);
}
