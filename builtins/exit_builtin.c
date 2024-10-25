/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:46:58 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/25 19:57:57 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_int(char *str)
{
	unsigned int	i;
	unsigned int	minus;

	i = 0;
	minus = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] == '-')
		{
			minus++;
			i++;
		}
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	if (minus > 1)
		return (1);
	return (0);
}

void	check_exit_args(t_ms *ms)
{
	if (check_for_int(ms->split_commands[1]))
	{
		ms->exit_status = 255;
		printf("exit\n");
		print_fd("minishell: exit: ", ms->split_commands[1], ": numeric argument required\n");
		exit(1);
	}
	else if (ms->split_commands[2])
	{
		ms->exit_status = 1;
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(1);
	}
	else
		ms->exit_status = ft_atoi(ms->split_commands[1]);
}

void	exit_builtin(t_ms *ms)
{
	if (!ms->split_commands[1])
		ms->split_commands[1] = ft_strdup("0");
	else
		check_exit_args(ms);
	printf("exit\n");
	exit(0);
}
