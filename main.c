/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/04 16:48:34 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;

	if (ac != 1)
		return (printf("minishell: %s: No such file or directory\n", av[1]), 1);
	ms = minishell_init(envp);
	setup_termios();
	if (setup_sigint() != 0 || setup_sigquit_ignore() != 0)
		return (free_struct(ms), 1);
	while (1)
	{
		if (!isatty_helper(ms) || !ms->input)
			break ;
		else if (ms->input[0] != '\0' && ms->input[0] != ' ')
		{
			add_history(ms->input);
			ms->token = parsing(ms);
			if (ms->token && pipes_check(ms, ms->token))
				minishell(ms);
			cleanup(ms);
		}
	}
	// free here
	return (ms->exit_status);
}
