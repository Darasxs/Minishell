/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/31 18:15:20 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;
	char	*line;

	if (ac != 1)
		return (printf("minishell: %s: No such file or directory\n", av[1]), 1);
	ms = minishell_init(envp);
	setup_termios();
	if (setup_sigint() != 0 || setup_sigquit_ignore() != 0)
		return (free_struct(ms), 1);
	while (1)
	{
		if (isatty(fileno(stdin)))
			prompt(ms);
		else
		{
			line = get_next_line(fileno(stdin));
			if (!line)
				break ;
			ms->input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!ms->input)
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
