/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:33:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/13 16:41:47 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_builtin_commands(minishell_t *line)
{
	if (ft_strncmp(line->split_commands[0], "cd", ft_strlen(line->split_commands[0]) + 3) == 0)
	{
		cd(line);
		return (true);
	}

//	else if (ft_strncmp(line->split_commands[0], "export", ft_strlen(line->split_commands[0]) + 7) == 0)
//	{
//		export(line);
//		Return (True);
//	}

//	else if (ft_strncmp(line->split_commands[0], "unset", ft_strlen(line->split_commands[0]) + 6) == 0)
//	{
//		unest(line);
//		Return (True);
//	}

//	else if (ft_strncmp(line->split_commands[0], "env", ft_strlen(line->split_commands[0]) + 4) == 0)
//	{
//		env(line);
//		Return (True);
//	}

//	else if (ft_strncmp(line->split_commands[0], "exit", ft_strlen(line->split_commands[0]) + 5) == 0)
//	{
//		exit(line);
//		Return (True);
//	}
	return (false);
}