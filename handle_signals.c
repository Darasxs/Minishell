/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:54:08 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/21 12:18:28 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	printf("\n");
	rl_on_new_line();       // indicating that we are on the new line
	rl_replace_line("", 0); // clearing the current input line
	rl_redisplay();         // refreshing the display to show the cleared line
}
void	handle_sigquit(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
// read the termios manual !!!!!!!!!!!!!!!!!!!!!!!!!!!

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

	setup_termios();
	sigemptyset(&sigint.sa_mask);
	sigint.sa_sigaction = &handle_sigint;
	sigint.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
	{
		printf("sigaction error\n"); // nie wiem czy tu moze cos trzeba uwolnic?
		return (-1);
	}
	return (0);
}

int	setup_sigquit(void)
{
	struct sigaction sigquit;

	setup_termios();
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_sigaction = &handle_sigquit;
	sigquit.sa_flags = SA_SIGINFO;
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
	{
		printf("sigquit error\n");
		return (-1);
	}
	return (0);
}
