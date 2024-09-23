/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/23 19:42:41 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_beginning(void)
{
	printf("\nWelcome to minishell!\n\n");
}

char **copy_envp(minishell_t *line)
{
	size_t i;
	char **copy;

	i = 0;
	while (line->env_pointer[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)
		return NULL;
	i = 0;
	while (line->env_pointer[i])
	{
		copy[i] = strdup(line->env_pointer[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			free(copy);
			return NULL;
		}
		i++;
	}
	copy[i] = NULL;
	return copy;
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = count * size;
	ptr = (unsigned char *)malloc(i * sizeof(unsigned char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	main(int ac, char **av, char **envp)
{
	minishell_t	*line;
	env_t		*struct_env;

	(void)ac;
	(void)av;
	line = malloc(sizeof(minishell_t));
	if (!line)
		return (1);
	struct_env = malloc(sizeof(env_t));
	if (!struct_env)
	{
		free(line);
		return (1);
	}
	struct_env->new_env = malloc(sizeof(char *) * 2);
	struct_env->new_env[0] = ft_calloc(1, 1);
	print_beginning();
	line->env_pointer = envp;
	line->env_copy = copy_envp(line);
	while (1)
		minishell(line);
	cleanup(line);
	free(line);
	return (0);
}
