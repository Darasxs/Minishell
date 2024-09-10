/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/10 10:54:49 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*initializing_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error with cwd.\n");
		exit(EXIT_FAILURE);
	}
	return (cwd);
}

int	main(void)
{
	char	*reading_line;
	char	*pwd;
	char	*prompt;
	char	**argv;
	pid_t	pid;

	while (1)
	{
		pwd = initializing_prompt();
		prompt = malloc(ft_strlen(pwd) + 4);
		if (!prompt)
			return (free(pwd), 1);
		ft_strcpy(prompt, pwd);
		ft_strcat(prompt, " % ");
		reading_line = readline(prompt);
		if (reading_line)
		{
			argv = ft_split(reading_line, " "); // musimy uwolnic gdzies pamiec z tego splita, chyba na koncu petli
			printf("%s\n", reading_line);
			pid = fork();
			if(pid == 0) // 0 oznacza child process
			{
				// tu trzeba zaimplementowac execve, i uzyc funkcji ktora wyszukuje PATH (sciezke) funkcji
			}
			else if(pid < 0)
			{
				perror("Error occured while forking.\n");
				// nie wiem czy tu trzeba cos uwolnic itp.
			}
			else if (pid > 0) // parent process
				wait(NULL); 
			// tu mozna jeszcze uzyc funkcji waitpid, wait3, wait4, poczytaj o tym w manualu; nie wiem ktora najlepiej uzyc, 
			//wait(NULL) czeka na zakonczenie jakiegokolwiek child procesu

			free(reading_line);
		}
		free(pwd);
		free(prompt);
	}
	return (0);
}
