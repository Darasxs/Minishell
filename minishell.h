/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/24 16:46:24 by dpaluszk         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_list
{
	char			*new_env;
	struct s_list	*next;
}					t_list;

typedef struct s_minishell
{
	char			**split_env;
	char			**env_copy;
	char			*prompt;
	char			*input;
	char			*path;
	char			*env;
	char			*full_path;
	char			*exit_code;
	int				exit_status;
	int				input_pos;
	int				input_len;
	int				single_q;
	int				double_q;
	int				token_count;
	bool			first_iteration;
	t_list			*lst;
	t_token			*token;
	t_token			*head;
	char			**split_commands;
	char			**split_pipes;
}					t_ms;

//	utils:
char				**ft_split(char *s, char c);
size_t				ft_strlen(char *str);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
void				ft_bzero(void *s, size_t n);
char				*ft_strrchr(char *s, char c);
char				*ft_substr(char *s, size_t start, size_t len);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnstr(char *haystack, char *needle, size_t size);
char				*ft_itoa(int n);
unsigned int		ft_size(int number);
char				*ft_strdup(char *s1);
char				*ft_strchr(char *s, int c);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_atoi(char *str);

//	builtins:
void				cd_home(t_ms *ms);
void				cd_oldpwd(t_ms *ms);
void				cd_builtin(t_ms *ms);
void				echo_builtin(t_ms *ms, t_token *token);
void				echo_newline(t_ms *ms, t_token *token, size_t i);
void				echo_env(t_ms *ms);
void				print_echo_env(t_ms *ms, size_t *k, size_t *l);
void				echo_single_q(t_ms *ms);
void				env_builtin(t_ms *ms);
void				check_exit_args(t_ms *ms);
void				exit_builtin(t_ms *ms);
int					check_for_int(char *str);
void				export_builtin(t_ms *ms);
void				export_new_env(t_ms *ms, t_list **lst);
void				add_new_env(t_ms *ms, t_list **lst);
void				pwd_builtin(t_ms *ms);
void				unset_builtin(t_ms *ms);

//	execution:
void				execute_builtin(t_ms *ms);
bool				check_builtin(t_ms *ms);
bool				check_cd_and_unset(t_ms *ms);
char				*find_path(char *path, t_ms *ms);
void				execute_command(t_ms *ms);
void				increment_shlvl(t_ms *ms);
void				execute_program_name(t_ms *ms);

//	minishell_helper:
int					count_split_size(t_token *token);
void				remove_quotes(t_ms *ms, int split);
t_token				*create_split_commands(t_ms *ms, t_token *token);
void				create_split_pipes(t_ms *ms, t_token *token);
int					count_pipes(t_token *token);
t_token				*join_pipes(t_ms *ms, t_token *token, int i);
void				free_split(char **split);
void				free_struct(t_ms *ms);
void				ft_error(char *str, t_ms *ms);
void				wrong_command(char *info, t_ms *ms);
void				cleanup(t_ms *ms);
void				free_list(t_ms *ms, t_token *token);
t_list				*list_init(t_ms *ms);
char				**envp_init(char **envp);
t_ms				*minishell_init(char **envp);
void				handle_builtins(t_ms *ms, int i, int *input_fd, int *fd);
void				handle_cd_and_unset(t_ms *ms, int i, int *input_fd, int *fd);
void				handle_child_process(t_ms *ms, int i, int *input_fd,
						int *fd);
void				handle_parent_process(t_ms *ms, int i, int *input_fd,
						int *fd);
void				execute_pipe_commands(t_ms *ms, int *input_fd, int i);
void				minishell(t_ms *ms);
void				prompt_helper(char **cwd, char **user_name, t_ms *ms);
void				prompt(t_ms *ms);
void				replace_exit_status(t_ms *ms, char *exit_status_str,
						size_t *j, size_t *k);
void				check_for_sign(t_ms *ms, size_t i, size_t *j, size_t *k);
void				handle_exit_code(t_ms *ms, size_t i);
void				check_exit_code(t_ms *ms);

//	parsing:
t_token				*token_init(t_ms *ms);
bool				is_space(t_ms *ms);
t_token				*parsing(t_ms *ms);
bool				syntax_check(t_ms *ms, t_token *token);
int					get_token(t_ms *ms, t_token *token);
int					get_word_token(t_ms *ms, t_token *token);

//	redirections:
void				handle_single_output(t_ms *ms, size_t i);
void				handle_double_output(t_ms *ms, size_t i);
void				handle_single_input(t_ms *ms, size_t i);
void				handle_double_input(t_ms *ms, size_t i);
void				handle_redirections(t_ms *ms);
bool				check_if_redirections(t_ms *ms);

//	signals:
void				handle_sigint(int signum, siginfo_t *info, void *context);
void				ignore_signals(int signum, siginfo_t *info, void *context);
int					setup_sigint(void);
int					setup_sigint_ignore(void);
int					setup_sigquit(void);
int					setup_sigquit_ignore(void);
void				setup_termios(void);

#endif
