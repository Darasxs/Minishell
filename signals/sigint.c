/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:04:10 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/23 18:04:45 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_sigint(void)
{
	struct sigaction	sigint;

	sigemptyset(&sigint.sa_mask);
	sigint.sa_sigaction = &handle_sigint;
	sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
	{
		printf("sigaction error\n");
		return (-1);
	}
	return (0);
}

int	setup_sigint_ignore(void)
{
	struct sigaction	sigint;

	sigemptyset(&sigint.sa_mask);
	sigint.sa_sigaction = &ignore_signals;
	sigint.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
	{
		printf("sigaction error\n");
		return (-1);
	}
	return (0);
}
