/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/05 19:13:17 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;
	int		i;

	if (ac != 1)
		return (printf("minishell: %s: No such file or directory\n", av[1]), 1);
	ms = minishell_init(envp);
	setup_termios();
	if (setup_sigint() != 0 || setup_sigquit_ignore() != 0)
		return (exit_minishell(ms), 1);
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
	i = ms->exit_status;
	return (exit_minishell(ms), i);
}

//pawka @ minishell $ cat << siema | cat << 1 || cat << 2
//> siema
//> 2
//> 1
//zsh: segmentation fault  ./minishell