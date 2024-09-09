/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/09 16:22:46 by dpaluszk         ###   ########.fr       */
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

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while(i < len)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*initializing_prompt(void)
{
	char	*cwd;

	// funkcja getcwd alokuje pamiec dla cwd jesli przekazujemy NULL jako pierwszy argument
	// ale wlasnie nie wiem czy nie bedziemy musieli sami zaalokowac pamieci
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error with cwd.\n");
		exit(EXIT_FAILURE);
	}
	return (cwd);
}

int	main(int argc, char **argv)
{
	char *reading_line;
	char *pwd;
	char prompt[1024];
	(void)argc;
	(void)argv;

	pwd = initializing_prompt();

	while (1)
	{
		ft_bzero(prompt, sizeof(prompt));
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
	return (0);
}