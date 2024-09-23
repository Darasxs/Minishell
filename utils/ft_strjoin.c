/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:40:03 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/23 13:40:17 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	len1;
	size_t	len2;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len2)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
