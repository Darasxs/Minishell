/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/24 11:46:55 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(minishell_t *line)
{
	size_t	i;
	char	*exit_status_str;

	i = 0;
	while(line->split_commands[i]) // to dziala ale tylo jesli $? sa oddzielone spacja, echo $?$?$? juz nie zadziala
	{
		if(ft_strncmp(line->split_commands[i], "$?", 3) == 0)
		{
			exit_status_str = ft_itoa(line->exit_status);
			if(!exit_status_str)
				break ;
			free(line->split_commands[i]);
			line->split_commands[i] = exit_status_str;
		}
		i++;
	}
}
