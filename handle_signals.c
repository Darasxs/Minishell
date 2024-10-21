/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:54:08 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/21 12:13:03 by dpaluszk         ###   ########.fr       */
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

int	setup_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		printf("error with tcgetattr\n"); // uwolnic tu cos? hmmm
		return (-1);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		printf("error with tcsetattr\n"); // uwolnic?? hmm
		return (-1);
	}
	return (0);
}

int	setup_sigint(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	if (setup_termios() != 0)
	{
		printf("error while setting up termios\n");
		return (1);
	}
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