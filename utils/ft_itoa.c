/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:12:56 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/31 18:21:20 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_itoa(int n)
{
	char			*str;
	long			nbr;
	unsigned int	length;

	nbr = n;
	length = ft_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	str[length] = '\0';
	while (nbr != 0)
	{
		str[--length] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}

unsigned int	ft_size(int number)
{
	unsigned int	i;

	i = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		i++;
		number = -number;
	}
	while (number != 0)
	{
		number = number / 10;
		i++;
	}
	return (i);
}
