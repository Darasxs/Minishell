/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/09 20:11:06 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	empty_quotes(t_minishell *line, t_token *token)
{
	if (line->input[line->input_pos] == '\'')
		token->value = ft_strdup("\'\'");
	else
		token->value = ft_strdup("\"\"");
	line->input_pos++;
}

bool	is_space(t_minishell *line)
{
	if (line->input[line->input_pos] == ' ')
		return (true);
	else if (line->input[line->input_pos] == '\t')
		return (true);
	else if (line->input[line->input_pos] == '\n')
		return (true);
	else if (line->input[line->input_pos] == '\v')
		return (true);
	else if (line->input[line->input_pos] == '\f')
		return (true);
	else if (line->input[line->input_pos] == '\r')
		return (true);
	else
		return (false);
}

void	parsing(t_minishell *line)
{
	t_token	*token;
	t_token	*head;

	token = token_init(line);
	line->input_len = ft_strlen(line->input);
	head = token;
	while (line->input_len > line->input_pos)
	{
		if (is_space(line))
			line->input_pos++;
		get_token(line, token);
		line->input_pos++;
		token->next = token_init(line);
		token = token->next;
	}
	token->next = NULL;
	token = head;
	while (token->next)
	{
		printf("value: %s\n", token->value);
		if (token->next && ft_strncmp(token->value, "|", 1) == 0 && ft_strncmp(token->next->value, "|", 1) == 0)
			ft_error("minishell: syntax error near unexpected token `||'", line);
		else if (ft_strncmp(token->value, ">", 1) == 0 || ft_strncmp(token->value, "<", 1) == 0)
			printf("unexpected token\n");
		token = token->next;
	}
	token = head;
	// i teraz trzeba zrobic funkcje ktora wyowala komendy
	exit(0);
}

//funkcja do exit_statusu(nie wiem czy jej potrzebujemy):

//#include "../minishell.h"

//void	replace_exit_status(t_minishell *line, char *exit_status_str, size_t *j,
//		size_t *k)
//{
//	ft_strlcpy(line->exit_code + *k, exit_status_str, ft_strlen(exit_status_str)
//		+ 1);
//	*k += ft_strlen(exit_status_str);
//	*j += 2;
//}

//void	append_dollar_sign(t_minishell *line, size_t *j, size_t *k)
//{
//	ft_strlcat(line->exit_code + *k, "$", 2);
//	(*k)++;
//	(*j)++;
//}

//void	append_question_mark(t_minishell *line, size_t *j, size_t *k)
//{
//	ft_strlcat(line->exit_code + *k, "?", 2);
//	(*k)++;
//	(*j)++;
//}

//void	check_for_sign(t_minishell *line, size_t i, size_t *j,
//		size_t *k)
//{
//	if (line->split_commands[i][*j] == '$')
//		append_dollar_sign(line, j, k);
//	else if (line->split_commands[i][*j] == '?')
//		append_question_mark(line, j, k);
//}

//void	handle_exit_code(t_minishell *line, size_t i)
//{
//	size_t	j;
//	size_t	k;
//	char	*exit_status_str;

//	j = 0;
//	k = 0;
//	exit_status_str = ft_itoa(line->exit_status);
//	line->exit_code = malloc(ft_strlen(line->split_commands[i])
//			+ ft_strlen(exit_status_str) + 1);
//	if (!line->exit_code)
//		ft_error("Error while allocating memory\n", line);
//	while (line->split_commands[i][j])
//	{
//		if (line->split_commands[i][j] == '$' && line->split_commands[i][j
//			+ 1] == '?')
//			replace_exit_status(line, exit_status_str, &j, &k);
//		else
//			check_for_sign(line, i, &j, &k);
//	}
//	line->exit_code[k] = '\0';
//	free(line->split_commands[i]);
//	line->split_commands[i] = line->exit_code;
//	free(exit_status_str);
//}

//void	check_exit_code(t_minishell *line)
//{
//	size_t	i;

//	i = 0;
//	while (line->split_commands[i])
//	{
//		if (line->split_commands[i][0] == '$' && line->split_commands[i][1] == '?')
//			handle_exit_code(line, i);
//		i++;
//	}
//}