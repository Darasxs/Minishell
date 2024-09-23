/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/23 19:42:46 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env(minishell_t *line, env_t *struct_env)
{
	size_t	i;

	i = 0;
	if (!struct_env->new_env[0])
	{
		printf("check\n");
		struct_env->new_env = malloc(sizeof(char *) * 2);
		if (!struct_env->new_env)
			ft_error("Error while allocating the memory\n", NULL, line);
		struct_env->new_env[i] = malloc(sizeof(char) * (ft_strlen(line->split_commands[0]) + 1));
		if (!struct_env->new_env[i])
		{
			free(struct_env->new_env);
			return ;
		}
	}
	ft_strlcpy(struct_env->new_env[i], line->split_commands[0], ft_strlen(line->split_commands[0]) + 1);
	struct_env->new_env[1] = NULL;
}

void	export_new_env(minishell_t *line, env_t *struct_env)
{
	(void)line;
	(void)struct_env;
	printf("export new env\n");
}

void	export_builtin(minishell_t *line)
{
	size_t	i;

	if (!line->split_commands[1])
	{
		if (ft_strrchr(line->split_commands[0], '=') == 0)
		{
			if (ft_strncmp(line->split_commands[0], "export", 7) == 0)
			{
				i = 0;
				while (line->env_pointer[i])
				{
					printf("declare -x ");
					printf("%s\n", line->env_pointer[i]);
					i++;
				}
			}
			else
				ft_error("Command not found\n", NULL, line);
		}
		else
		{
			add_new_env(line, line->struct_env);
			printf("%s\n", line->struct_env->new_env[0]);
		}
	}
	else
		export_new_env(line, line->struct_env);
}
