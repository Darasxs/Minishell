/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/25 17:37:31 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct	lst_s
{
	char			*new_env;
	struct lst_s	*next;
	struct lst_s	*prev;
}				lst_t;

typedef struct minishell_s
{
	char		*prompt;
	char		*input;
	char		**split_commands;
	char		*env;
	char		**split_env;
	char		*path;
	char		**env_pointer;
	char		**split_pipe;
	char		**env_copy;
	int			exit_status;
	lst_t		*lst;
}				minishell_t;

void			printing_prompt(minishell_t *line);
char			**ft_split(char *s, char c);
size_t			ft_strlen(char *str);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t			ft_strlcat(char *dest, char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
void			ft_error(char *str, char *info, minishell_t *line);
void			print_beginning(void);
void			free_split(char **split);
void			cleanup(minishell_t *line);
void			execute_command(minishell_t *line);
bool			preparing_execution(minishell_t *line);
char			*find_path(char *path, minishell_t *line);
void			path_preparation(minishell_t *line);
void			minishell(minishell_t *line);
void			cd_builtin(minishell_t *line);
bool			check_builtin(minishell_t *line);
void			env_builtin(minishell_t *line);
void			unset_builtin(minishell_t *line);
void			export_builtin(minishell_t *line);
void			prompt_helper(char **cwd, char **user_name, minishell_t *line);
char			*ft_strrchr(char *s, char c);
char			*ft_substr(char *s, size_t start, size_t len);
char			**copy_envp(minishell_t *line);
void			exit_builtin(minishell_t *line);
void			new_env_value(minishell_t *line);
void			execute_builtin(minishell_t *line);
bool			check_cd(minishell_t *line);
bool			check_env(minishell_t *line);
void			update_oldpwd(minishell_t *line);
void			handle_builtins(minishell_t *line, size_t i, char **commands,
					int *input_fd, int *fd);
void			handle_child_process(minishell_t *line, size_t i, int *input_fd,
					int *fd, char **commands);
void			handle_parent_process(size_t i, int *input_fd, int *fd,
					char **commands);
void			execute_pipe_commands(minishell_t *line, char **commands,
					size_t i, int *input_fd);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strnstr(char *haystack, char *needle, size_t size);
char			*ft_itoa(int n);
unsigned int	ft_size(int number);
void			parsing(minishell_t *line);
char			*ft_strdup(char *s1);
char			*ft_strchr(char *s, int c);
void			replace_exit_status(char **exit_code, char *exit_status_str,
					size_t *j, size_t *k);
void			append_dollar_sign(char **exit_code, size_t *j, size_t *k);
void			append_question_mark(char **exit_code, size_t *j, size_t *k);
void			handle_exit_code(minishell_t *line, size_t i);
void			check_for_sign(minishell_t *line, char **exit_code, size_t i,
					size_t *j, size_t *k);
void			add_new_env(minishell_t *line, lst_t **lst);
void			update_env_copy(minishell_t *line, lst_t *tmp);
void			export_new_env(minishell_t *line, lst_t **lst);
void			ft_lstadd_back(lst_t **lst, lst_t *new);

#endif
