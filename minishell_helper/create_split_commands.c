/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_split_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:28:03 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/16 15:33:52 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(t_minishell *ms, int i)
{
	int word_count = 0;
	char	**split;

	split = ft_split(ms->split_pipes[i], ' ');
	while (split[word_count])
		word_count++;
	return (word_count);
}

t_token	*create_split_commands(t_minishell *ms, t_token *token, int i)
{
	t_token	*head;
	int	start;
	int	end;
	int j;

	if (token->value && token->value[0] == '|')
		token = token->next;
	head = token;
	int word_count = count_words(ms, i);
	ms->split_commands = malloc(sizeof(char *) * (word_count + 1));
	if (!ms->split_commands)
		ft_error("Error while allocating the memory\n", ms);
	token = head;
	j = 0;
	start = 0;
	end = 0;
	while (j < word_count)
	{
		while ((token->value[start] == '\'' || token->value[start] == '\"' || token->value[start] == ' ') && token->value[start])
			start++;
		printf("%c\n", token->value[start]);
		end = start;
		while (token->value[end] != '\'' && token->value[end] != '\"' && token->value[end] != ' ' && token->value[end])
			end++;
		if (token->value[end] == '\'' || token->value[end] == '\"')
			end--;
		printf("%c\n", token->value[end]);
		ms->split_commands[j] = ft_substr(token->value, start, end - start + 1);
		if (token->next->value)
		{
			printf("check\n");
			start = 0;
			end = 0;
			token = token->next;
		}
		else
			start = end;
		printf("%s\n", ms->split_commands[j]);
		j++;
	}
	ms->split_commands[j] = NULL;
	return (token);
}

//int	count_words(t_minishell *ms, int i)
//{
//	int word_count = 0;
//	char	**split;

//	split = ft_split(ms->split_pipes[i], ' ');
//	while (split[word_count])
//		word_count++;
//	return (word_count);
//}

//t_token	*create_split_commands(t_minishell *ms, t_token *token, int i)
//{
//	t_token	*head;
//	int	start;
//	int	end;
//	int j;

//	if (token->value && token->value[0] == '|')
//		token = token->next;
//	head = token;
//	int word_count = count_words(ms, i);
//	ms->split_commands = malloc(sizeof(char *) * (word_count + 1));
//	if (!ms->split_commands)
//		ft_error("Error while allocating the memory\n", ms);
//	token = head;
//	j = 0;
//	start = 0;
//	end = 0;
//	while (j < word_count)
//	{
//		while ((token->value[start] == '\'' || token->value[start] == '\"' || token->value[start] == ' ') && token->value[start])
//			start++;
//		printf("%c\n", token->value[start]);
//		end = start;
//		while (token->value[end] != '\'' && token->value[end] != '\"' && token->value[end] != ' ' && token->value[end])
//			end++;
//		if (token->value[end] == '\'' || token->value[end] == '\"')
//			end--;
//		printf("%c\n", token->value[end]);
//		ms->split_commands[j] = ft_substr(token->value, start, end - start + 1);
//		if (token->next->value)
//		{
//			printf("check\n");
//			start = 0;
//			end = 0;
//			token = token->next;
//		}
//		else
//			start = end;
//		printf("%s\n", ms->split_commands[j]);
//		j++;
//	}
//	ms->split_commands[j] = NULL;
//	return (token);
//}