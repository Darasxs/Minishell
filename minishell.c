/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/09 20:49:11 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}

char	*initializing_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error with cwd.\n");
		exit(EXIT_FAILURE);
	}
	return (cwd);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main()
{
	char 	*reading_line;
	char 	*pwd;
	char 	*prompt;
	char	*username;

	while (1)
	{
		username = "paprzyby ";
		pwd = initializing_prompt();
		prompt = malloc(sizeof(char) * (ft_strlen(pwd) + ft_strlen(username) + 4));
		if (!prompt)
			return (free(pwd), 1);
		ft_strcat(prompt, username);
		ft_strcat(prompt, pwd);
		ft_strcat(prompt, " % ");
		reading_line = readline(prompt);
		if (reading_line)
		{
			printf("%s", reading_line);
			free(reading_line);
		}
	}
	free(pwd);
	free(prompt);
	return (0);
}

//int	main()
//{
//	char 	*reading_line;
//	char 	*pwd;
//	char 	*prompt;
//	char	*username;

//	while (1)
//	{
//		username = "paprzyby ";
//		pwd = initializing_prompt();
//		prompt = malloc(sizeof(char) * (ft_strlen(pwd) + ft_strlen(username) + 4));
//		if (!prompt)
//			return (free(pwd), 1);
//		ft_strcat(prompt, username);
//		ft_strcat(prompt, pwd);
//		ft_strcat(prompt, " % ");
//		reading_line = readline(prompt);
//		if (reading_line)
//		{
//			if (ft_strlen(prompt) != ft_strlen(reading_line))
//				printf("%s\n", prompt);
//			else
//				printf("%s", reading_line);
//			free(reading_line);
//		}
//	}
//	free(pwd);
//	free(prompt);
//	return (0);
//}