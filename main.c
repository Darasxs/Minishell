/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/23 17:23:58 by paprzyby         ###   ########.fr       */
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
		prompt(ms);
		if (!ms->input)
			break ;
		else if (ms->input[0] != '\0')
		{
			add_history(ms->input);
			ms->token = parsing(ms);
			if (ms->token && syntax_check(ms, ms->token))
				minishell(ms);
			cleanup(ms);
		}
	}
	return (free_struct(ms), 0);
}

//"e""c""h""o" "h""e"llo