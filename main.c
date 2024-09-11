/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/11 16:29:17 by dpaluszk         ###   ########.fr       */
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

char	*find_path(const char *path)
{
	char	*result;

	result = getenv(path);
	return (result);
}

void	execute_command(minishell_t *line)
{
	char	*path;

	path = find_path(line->split[0]);
	if (!path)
		ft_error("Command not found.\n");
	if (execve(path, line->split, NULL) == -1)
		ft_error("Execution failed.\n");
	// free(path); ???
}

int	main(void)
{
	minishell_t	*line;
	pid_t		pid;

	line = malloc(sizeof(minishell_t));
	if (!line)
		return (1);
	print_beginning();
	while (1)
	{
		printing_prompt(line);
		if (line->input)
		{
			pid = fork();
			if (pid == 0)
			{
				execute_command(line);
			}
			else if (pid < 0)
			{
				free_split(line->split);
				ft_error("Error occured while forking.\n");
			}
			else if (pid > 0)
				wait(NULL);
		}
		cleanup(line);
	}
	free(line);
	return (0);
}
