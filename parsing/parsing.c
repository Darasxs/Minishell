/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/12 17:17:00 by paprzyby         ###   ########.fr       */
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
		else
		{
			get_token(ms, token);
			ms->input_pos++;
			if (token->value[0] != '|')
				ms->token_count++;
			token->next = token_init(ms);
			token = token->next;
		}
	}
	token = NULL;
	token = head;
	//tutaj funkcja ktora sprawdza czy sa np. 2 pipe obok siebie
	return (token);
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