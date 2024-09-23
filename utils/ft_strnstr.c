/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:40:46 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/23 13:40:52 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0 && (haystack == 0 && size == 0))
		return (NULL);
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < size)
	{
		j = 0;
		while ((haystack[i + j] == needle[j])
			&& (needle[j] != '\0') && (i + j < size))
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
