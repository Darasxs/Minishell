/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/12 15:08:56 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_beginning(void)
{
	printf("\nWelcome to minishell!\n\n");
}

int	main(void)
{
	minishell_t	*line;

	line = malloc(sizeof(minishell_t));
	if (!line)
		return (1);
	//signal(SIGINT, SIG_IGN);
	print_beginning();
	while (1)
		minishell(line);
	free(line);
	return (0);
}

//things that are not working:
//man (WARNING: terminal is not fully functional -  (press RETURN))
//clear
//exit
//pipes
//>>

//tgetent(NULL, getenv("TERM"));
//lflag -lncurses