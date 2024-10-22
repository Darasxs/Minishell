/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:54:08 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/22 20:47:59 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct sigaction	sigint;

void	handle_sigint(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	handle_sigint_ignore(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
}
void	handle_sigquit_ignore(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
}
void	handle_sigquit(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	printf("Quit: 3\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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
	sigemptyset(&sigint.sa_mask);
	sigint.sa_sigaction = &handle_sigint_ignore;
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

	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_sigaction = &handle_sigquit;
	sigquit.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
	{
		printf("sigquit error\n");
		return (-1);
	}
	return (0);
}
int	setup_sigquit_ignore(void)
{
	struct sigaction	sigquit;

	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_sigaction = &handle_sigquit;
	sigquit.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
	{
		printf("sigquit error\n");
		return (-1);
	}
	return (0);
}

// int	setup_sigquit(bool CHILD)
//{
//	struct sigaction	sigquit;

//	if (CHILD)
//	{
//		sigemptyset(&sigquit.sa_mask);
//		sigquit.sa_sigaction = &handle_sigquit;
//		sigquit.sa_flags = SA_SIGINFO | SA_RESTART;
//		if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
//		{
//			printf("sigquit error\n");
//			return (-1);
//		}
//	}
//	else
//	{
//		sigquit.sa_handler = SIG_IGN;
//		if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
//		{
//			printf("sigquit error\n");
//			return (-1);
//		}
//	}
//	return (0);
//}
