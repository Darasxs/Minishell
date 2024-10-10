/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/10 19:17:11 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_init(t_minishell *ms)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("Error while allocating the memory\n", ms);
	token->value = NULL;
	return (token);
}

void	empty_quotes(t_minishell *ms, t_token *token)
{
	if (ms->input[ms->input_pos] == '\'')
		token->value = ft_strdup("\'\'");
	else
		token->value = ft_strdup("\"\"");
	ms->input_pos++;
}

bool	is_space(t_minishell *ms)
{
	if (ms->input[ms->input_pos] == ' ')
		return (true);
	else if (ms->input[ms->input_pos] == '\t')
		return (true);
	else if (ms->input[ms->input_pos] == '\n')
		return (true);
	else if (ms->input[ms->input_pos] == '\v')
		return (true);
	else if (ms->input[ms->input_pos] == '\f')
		return (true);
	else if (ms->input[ms->input_pos] == '\r')
		return (true);
	else
		return (false);
}

void	create_split_commands(t_minishell *ms, t_token *token)
{
	int	i;

	ms->split_commands = malloc(sizeof(char *) * (ms->token_count + 1));
	if (!ms->split_commands)
		ft_error("Error while allocating the memory\n", ms);
	i = 0;
	while (i < ms->token_count)
	{
		ms->split_commands[i] = strdup(token->value);
		if (!ms->split_commands[i])
		{
			while (i--)
				free(token->value);
			free(token->value);
			exit(1);
		}
		token = token->next;
		i++;
	}
	ms->split_commands[i] = NULL;
}

t_token	*parsing(t_minishell *ms)
{
	t_token	*token;
	t_token	*head;

	token = token_init(ms);
	ms->input_len = ft_strlen(ms->input);
	head = token;
	while (ms->input_len > ms->input_pos)
	{
		if (is_space(ms))
			ms->input_pos++;
		get_token(ms, token);
		ms->input_pos++;
		token->next = token_init(ms);
		ms->token_count++;
		token = token->next;
	}
	token->next = NULL;
	token = head;
	while (token->next)
	{
		//printf("value: %s\n", token->value);
		if (ft_strncmp(token->value, "|", 1) == 0 && ft_strncmp(token->next->value, "|", 1) == 0)
			ft_error("minishell: syntax error near unexpected token `||'", ms);
		//else if (ft_strncmp(token->value, ">", 1) == 0 || ft_strncmp(token->value, "<", 1) == 0)
		//	printf("unexpected token\n");
		else if (ft_strncmp(token->value, "|", 1) == 0)
			ms->pipe = true;
		token = token->next;
	}
	token = head;
	create_split_commands(ms, token);
	token = head;
	return (token);
	// i teraz trzeba zrobic funkcje ktora wyowala komendy
	//exit(0);
}

//funkcja do exit_statusu(nie wiem czy jej potrzebujemy):

//#include "../minishell.h"

//void	replace_exit_status(t_minishell *ms, char *exit_status_str, size_t *j,
//		size_t *k)
//{
//	ft_strlcpy(ms->exit_code + *k, exit_status_str, ft_strlen(exit_status_str)
//		+ 1);
//	*k += ft_strlen(exit_status_str);
//	*j += 2;
//}

//void	append_dollar_sign(t_minishell *ms, size_t *j, size_t *k)
//{
//	ft_strlcat(ms->exit_code + *k, "$", 2);
//	(*k)++;
//	(*j)++;
//}

//void	append_question_mark(t_minishell *ms, size_t *j, size_t *k)
//{
//	ft_strlcat(ms->exit_code + *k, "?", 2);
//	(*k)++;
//	(*j)++;
//}

//void	check_for_sign(t_minishell *ms, size_t i, size_t *j,
//		size_t *k)
//{
//	if (ms->split_commands[i][*j] == '$')
//		append_dollar_sign(ms, j, k);
//	else if (ms->split_commands[i][*j] == '?')
//		append_question_mark(ms, j, k);
//}

//void	handle_exit_code(t_minishell *ms, size_t i)
//{
//	size_t	j;
//	size_t	k;
//	char	*exit_status_str;

//	j = 0;
//	k = 0;
//	exit_status_str = ft_itoa(ms->exit_status);
//	ms->exit_code = malloc(ft_strlen(ms->split_commands[i])
//			+ ft_strlen(exit_status_str) + 1);
//	if (!ms->exit_code)
//		ft_error("Error while allocating memory\n", ms);
//	while (ms->split_commands[i][j])
//	{
//		if (ms->split_commands[i][j] == '$' && ms->split_commands[i][j
//			+ 1] == '?')
//			replace_exit_status(ms, exit_status_str, &j, &k);
//		else
//			check_for_sign(ms, i, &j, &k);
//	}
//	ms->exit_code[k] = '\0';
//	free(ms->split_commands[i]);
//	ms->split_commands[i] = ms->exit_code;
//	free(exit_status_str);
//}

//void	check_exit_code(t_minishell *ms)
//{
//	size_t	i;

//	i = 0;
//	while (ms->split_commands[i])
//	{
//		if (ms->split_commands[i][0] == '$' && ms->split_commands[i][1] == '?')
//			handle_exit_code(ms, i);
//		i++;
//	}
//}