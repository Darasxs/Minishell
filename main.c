/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/16 18:07:40 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	if (ac != 1)
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		return (1);
	}
	ms = minishell_init(envp);
	while (1)
	{
		printing_prompt(ms);
		if (ms->input[0] != '\0')
		{
			add_history(ms->input);
			ms->token = parsing(ms);
			create_split_pipes(ms, ms->token);
			//check_exit_code(ms);
			minishell(ms);
			parsing_cleanup(ms, ms->token);
		}
	}
	free_struct(ms);
	return (0);
}
