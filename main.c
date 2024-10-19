/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/19 19:59:36 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ms	*ms;

	if (ac != 1)
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		return (1);
	}
	ms = minishell_init(envp);
	if(setup_signals() != 0)
	{
		free_struct(ms);
		return 1;
	}
	while (1)
	{
		printing_prompt(ms);
		if (!ms->input)
			break ;
		else if (ms->input[0] != '\0')
		{
			add_history(ms->input);
			ms->token = parsing(ms);
			if (syntax_check(ms, ms->token))
				minishell(ms);
			parsing_cleanup(ms, ms->token);
		}
	}
	free_struct(ms);
	return (0);
}
