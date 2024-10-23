/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:04:02 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/23 18:04:27 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_sigquit(void)
{
	struct sigaction	sigquit;

	sigquit.sa_sigaction = &ignore_signals;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &sigquit, NULL) < 0)
		return (1);
	if (sigaction(SIGQUIT, &sigquit, NULL) < 0)
		return (1);
	return (0);
}

int	setup_sigquit_ignore(void)
{
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
