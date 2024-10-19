/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:54:08 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/19 19:41:05 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	rl_on_new_line(); // indicating that we are on the new line
	rl_replace_line("", 0); // clearing the current input line
	rl_redisplay(); // refreshing the display to show the cleared line
}
void	handle_sigquit(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(0);
}

int	setup_signals(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigemptyset(&sigint.sa_mask);
	sigemptyset(&sigquit.sa_mask);
	sigint.sa_sigaction = &handle_sigint;
	sigint.sa_flags = SA_SIGINFO;
	sigquit.sa_sigaction = &handle_sigquit;
	sigquit.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
	{
		printf("sigaction error\n"); // nie wiem czy tu moze cos trzeba uwolnic?
		return (1);
	}
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
	{
		printf("sigquit error\n");
		return (1);
	}
	return (0);
}
