/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/18 22:37:08 by paprzyby         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	minishell_t	*line;

	(void)ac;
	(void)av;
	line = malloc(sizeof(minishell_t));
	if (!line)
		return (1);
	print_beginning();
	line->env_pointer = envp;
	line->env_copy = copy_envp(line);
	while (1)
		minishell(line);
	free(line);
	return (0);
}

//man output:	(WARNING: terminal is not fully functional -  (press RETURN))

//quotes
//pipes
//redirections
//exit command