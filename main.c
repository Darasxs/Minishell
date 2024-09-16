/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/16 08:13:18 by dpaluszk         ###   ########.fr       */
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
	//term_init(line);
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
//cd po wcisnieciu taba powinna byc opcja przejscia przez wszystkie opcje
