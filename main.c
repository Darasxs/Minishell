/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/17 16:09:55 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_beginning(void)
{
	printf("\nWelcome to minishell!\n\n");
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