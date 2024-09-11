/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:33:16 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/11 20:05:08 by dpaluszk         ###   ########.fr       */
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

char	*find_path(char *path)
{
	char	*env;
	char	*full_path;
	char	**split;
	int		i;

	env = getenv("PATH");
	if (!env)
		return (NULL);
	split = ft_split(env, ':');
	if (!split)
		free_split(split);
	i = 0;
	while (split[i])
	{
		full_path = malloc(ft_strlen(split[i]) + ft_strlen(path) + 2);
		if(!full_path)
			return(free(full_path), NULL);
		ft_strlcpy(full_path, path, ft_strlen(path) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 1);
		ft_strlcat(full_path, split[i], ft_strlen(full_path) + ft_strlen(split[i]) + 1);
		printf("%s\n", full_path);
		if(access(full_path, X_OK) == 0)
		{
			printf("%s\n", full_path);
			free_split(split);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_split(split);
	return(NULL);
}

void	execute_command(minishell_t *line)
{
	char	*path;

	path = find_path(line->split[0]);
	if (!path)
	{
		ft_error("Command not found.\n");
	}
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
