/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/01 12:57:29 by paprzyby         ###   ########.fr       */
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

typedef struct s_list
{
	char			*new_env;
	struct s_list	*next;
}					t_list;

typedef struct s_minishell
{
	char			**split_commands;
	char			**split_env;
	char			**split_pipe;
	char			**env_copy;
	char			*prompt;
	char			*input;
	char			*path;
	char			*env;
	char			*full_path;
	char			*exit_code;
	int				exit_status;
	bool			apos_check;
	t_list			*lst;
}					t_minishell;

void				printing_prompt(t_minishell *line);
char				**ft_split(char *s, char c);
size_t				ft_strlen(char *str);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
void				ft_error(char *str, t_minishell *line);
void				free_split(char **split);
void				free_struct(t_minishell *line);
void				execute_command(t_minishell *line);
bool				preparing_execution(t_minishell *line);
char				*find_path(char *path, t_minishell *line);
void				path_preparation(t_minishell *line);
void				minishell(t_minishell *line);
void				cd_builtin(t_minishell *line);
bool				check_builtin(t_minishell *line);
void				env_builtin(t_minishell *line);
void				unset_builtin(t_minishell *line);
void				export_builtin(t_minishell *line);
void				prompt_helper(char **cwd, char **user_name,
						t_minishell *line);
char				*ft_strrchr(char *s, char c);
char				*ft_substr(char *s, size_t start, size_t len);
char				**copy_envp(char **envp);
void				exit_builtin(t_minishell *line);
void				new_env_value(t_minishell *line);
void				execute_builtin(t_minishell *line);
bool				check_cd(t_minishell *line);
bool				check_env(t_minishell *line);
void				update_oldpwd(t_minishell *line);
void				handle_builtins(t_minishell *line, size_t i,
						char **commands, int *input_fd, int *fd);
void				handle_child_process(t_minishell *line, size_t i,
						int *input_fd, int *fd, char **commands);
void				handle_parent_process(size_t i, int *input_fd, int *fd,
						char **commands);
void				execute_pipe_commands(t_minishell *line, char **commands,
						size_t i, int *input_fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnstr(char *haystack, char *needle, size_t size);
char				*ft_itoa(int n);
unsigned int		ft_size(int number);
void				parsing(t_minishell *line, char **commands);
char				*ft_strdup(char *s1);
char				*ft_strchr(char *s, int c);
void				replace_exit_status(t_minishell *line, char *exit_status_str,
						size_t *j, size_t *k);
void				append_dollar_sign(t_minishell *line, size_t *j, size_t *k);
void				append_question_mark(t_minishell *line, size_t *j,
						size_t *k);
void				handle_exit_code(t_minishell *line, size_t i);
void				check_for_sign(t_minishell *line, size_t i, size_t *j, size_t *k);
void				add_new_env(t_minishell *line, t_list **lst);
void				update_env_copy(t_minishell *line, t_list *tmp);
void				export_new_env(t_minishell *line, t_list **lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_minishell			*struct_init(char **envp);
void				check_exit_code(t_minishell *line);
void				check_quotes(t_minishell *line);
void				handle_quotes(t_minishell *line);
void				quotes_loop(void);
void				skip_quotes(t_minishell *line);
void				check_redirections(t_minishell *line);
void				echo_builtin(t_minishell *line);
void				print_echo(t_minishell *line, size_t i);
void				wrong_command(char *info, t_minishell *line);
void				echo_env(t_minishell *line);
void				execute_program_name(t_minishell *line);
int					ft_atoi(char *str);
void				increment_shlvl(t_minishell *line);

#endif
