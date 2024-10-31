/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:48:12 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/31 18:21:39 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	size_t	beginning;
	size_t	end;
	size_t	new;

	beginning = 0;
	end = ft_strlen(s1);
	new = 0;
	while (s1[beginning] != '\0' && ft_check(s1[beginning], set))
		beginning++;
	while (end > beginning && ft_check(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - beginning + 1));
	if (str == NULL)
		return (NULL);
	while (beginning < end)
		str[new++] = s1[beginning++];
	str[new] = '\0';
	return (str);
}

int	ft_check(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
