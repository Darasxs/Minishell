/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:33:06 by dpaluszk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/14 11:34:21 by paprzyby         ###   ########.fr       */
=======
/*   Updated: 2024/09/16 08:14:17 by dpaluszk         ###   ########.fr       */
>>>>>>> 8b689271f4955af3f4f028a6e5c67be4ede0c07e
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_builtin_commands(minishell_t *line)
{
	if (!line->split_commands[0])
		return (false);
	if (ft_strncmp(line->split_commands[0], "cd", ft_strlen(line->split_commands[0]) + 3) == 0)
	{
		cd(line);
		return (true);
	}
	if (ft_strncmp(line->split_commands[0], "exit", ft_strlen(line->split_commands[0]) + 6) == 0)
		return (true);
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
	return (false);
}
