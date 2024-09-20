/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:34 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/20 18:28:33 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, size_t start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(len + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (s[start] != '\0' && len > i)
		str[i++] = s[start++];
	str [i] = '\0';
	return (str);
}

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

void	unset_builtin(minishell_t *line)
{
	size_t		i;
	char		*env_variable;
	char		*equal_pos;
	size_t		len;
	size_t		j;

	i = 0;
	while (line->env_copy[i])
	{
		equal_pos = ft_strrchr(line->env_copy[i], '=');
		if (equal_pos != NULL)
		{
			len = equal_pos - line->env_copy[i];
			env_variable = ft_substr(line->env_copy[i], 0, len);
			if (ft_strncmp(env_variable, line->split_commands[1], len) == 0)
			{
				free(line->env_copy[i]);
				line->env_copy[i] = NULL;
				j = i;
				while (line->env_copy[j])
				{
					line->env_copy[j] = line->env_copy[j + 1];
					j++;
				}
				line->env_copy[j] = NULL;
				return;
			}
			free(env_variable);
		}
		i++;
	}
}
