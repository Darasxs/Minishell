/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:54:08 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/23 16:47:21 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		printf("error with tcgetattr\n"); // uwolnic tu cos? hmmm
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		printf("error with tcsetattr\n"); // uwolnic?? hmm
		return ;
	}
}

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
