/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/10 16:33:56 by paprzyby         ###   ########.fr       */
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
	char	*prompt;
	char	*input;
	char	**argv;
}		minishell_t;

void	printing_prompt(minishell_t *line);
void	input_check(minishell_t *line);
char	**ft_split(char *s, char c);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2);
void	ft_error(char *str);
void	print_beginning(void);

#endif
