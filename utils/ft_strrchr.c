/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:41:23 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/23 13:41:39 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr(char *s, char c)
{
	unsigned int	i;

	i = ft_strlen(s);
	if (!s)
		return (0);
	if (c == '\0')
		return (s + i);
	while (s[i] != c && i != 0)
		i--;
	if (s[i] == c)
		return (s + i);
	return (0);
}
