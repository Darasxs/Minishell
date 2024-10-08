/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:29:55 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/08 17:30:05 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_init(t_minishell *line)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("Error while allocating the memory\n", line);
	token->value = NULL;
	return (token);
}
