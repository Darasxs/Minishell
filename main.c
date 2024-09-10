/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/10 16:38:48 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_beginning(void)
{
	printf("┎┈┈┈┈┈┈┈୨♡୧┈┈┈┈┈┈┈┒\n");
	printf("   dawid jasper    \n");
	printf("<3       i       <3\n");
	printf("     mikrocypek    \n");
	printf("┖┈┈┈┈┈┈┈୨♡୧┈┈┈┈┈┈┈┚\n");
}

int	main(void)
{
	minishell_t	*line;

	line = malloc(sizeof(minishell_t));
	if (!line)
		return (1);
	print_beginning();
	while (1)
	{
		printing_prompt(line); // prints only the location we are in (prints prompt)
		input_check(line); // checks the input of the user (whats behind after)
		free(line->input);
		free(line->prompt);
	}
	free(line);
	return (0);
}

//int	main(void)
//{
//	char	*reading_line;
//	char	*prompt;
//	char	**argv;
//	pid_t	pid;

//	while (1)
//	{
//		prompt = initializing_prompt();
//		reading_line = readline(prompt);
//		if (reading_line)
//		{
//			argv = ft_split(reading_line, ' ');
//			printf("%s\n", reading_line);
//			pid = fork();
//			if(pid == 0)
//			{
//				// tu trzeba zaimplementowac execve, i uzyc funkcji ktora wyszukuje PATH (sciezke) funkcji
//			}
//			else if(pid < 0)
//			{
//				while (*argv)
//				{
//					free(&argv);
//					argv++;
//				}
//				free(reading_line);
//				perror("Error occured while forking.\n");
//			}
//			else if (pid > 0)
//				wait(NULL);
//			while (*argv)
//			{
//				free(&argv);
//				argv++;
//			}
//			free(reading_line);

//		free(prompt);
//		}
//	}
//	return (0);
//}