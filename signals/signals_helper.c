/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:36:41 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/04 12:00:21 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	rl_on_new_line();
}
void	ignore_signals(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	rl_replace_line("", 0);
	rl_redisplay();
}
