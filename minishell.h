/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/10 09:50:40 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/_types.h>
# include <sys/wait.h> // for waitpid()
# include <unistd.h>

typedef struct minishell_s
{
	/* data */
}		minishell_t;

size_t	ft_strlen(char *str);
char	*initializing_prompt(void);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strcpy(char *dst, const char *src);
char	**ft_split(char const *s, char c);

#endif
