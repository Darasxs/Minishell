/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/21 19:34:58 by dpaluszk         ###   ########.fr       */
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

void update_oldpwd(minishell_t *line)
{
	size_t i;
	char *env_variable;
	char *new_oldpwd;

	i = 0;
	while (line->env_copy[i])
	{
		env_variable = ft_strnstr(line->env_copy[i], "OLDPWD=", 7);
		if (env_variable)
		{
			new_oldpwd = ft_strjoin("OLDPWD=", line->env);
			free(line->env_copy[i]);
			line->env_copy[i] = new_oldpwd;
			return;
		}
		i++;
	}
}

void	cd_builtin(minishell_t *line)
{
	if (!line->split_commands[1] || (line->split_commands[1][0] == '~' && line->split_commands[1][1] == '\0'))
	{
		update_oldpwd(line);
		line->env = getenv("HOME");
		if (!line->env)
			ft_error("cd: HOME not set", NULL, line);
		if (chdir(line->env) != 0)
			ft_error("Error while finding the HOME directory\n", NULL, line);
	}
	else if (line->split_commands[1][0] == '-' && line->split_commands[1][1] == '\0')
	{
		line->env = getenv("OLDPWD");
		if (!line->env)
			ft_error("cd: OLDPWD not set", NULL, line);
		if (chdir(line->env) != 0)
			ft_error("Error while finding the previous working directory\n", NULL, line);
		printf("%s\n", line->env);
	}
	else if (line->split_commands[1])
	{
		update_oldpwd(line);
		if (chdir(line->split_commands[1]) != 0)
			ft_error("cd: no such file or directory: ", line->split_commands[1], line);
	}
	else
		ft_error("Command not found\n", NULL, line);
}

//stat (cd ..)