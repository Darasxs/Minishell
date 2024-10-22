/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/22 20:14:43 by dpaluszk         ###   ########.fr       */
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

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	// struct s_token *prev;
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

void				printing_prompt(t_ms *ms);
char				**ft_split(char *s, char c);
size_t				ft_strlen(char *str);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
void				ft_bzero(void *s, size_t n);
void				ft_error(char *str, t_ms *ms);
void				free_split(char **split);
void				free_struct(t_ms *ms);
void				execute_command(t_ms *ms);
bool				preparing_execution(t_ms *ms);
char				*find_path(char *path, t_ms *ms);
void				minishell(t_ms *ms);
void				cd_builtin(t_ms *ms);
bool				check_builtin(t_ms *ms);
void				env_builtin(t_ms *ms);
void				unset_builtin(t_ms *ms);
void				export_builtin(t_ms *ms);
void				prompt_helper(char **cwd, char **user_name, t_ms *ms);
char				*ft_strrchr(char *s, char c);
char				*ft_substr(char *s, size_t start, size_t len);
char				**envp_init(char **envp);
void				exit_builtin(t_ms *ms);
void				execute_builtin(t_ms *ms);
bool				check_cd(t_ms *ms);
bool				check_env(t_ms *ms);
void				handle_builtins(t_ms *ms, int i, int *input_fd, int *fd);
void				handle_child_process(t_ms *ms, int i, int *input_fd,
						int *fd);
void				handle_parent_process(t_ms *ms, int i, int *input_fd,
						int *fd);
void				execute_pipe_commands(t_ms *ms, int *input_fd, int i);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnstr(char *haystack, char *needle, size_t size);
char				*ft_itoa(int n);
unsigned int		ft_size(int number);
char				*ft_strdup(char *s1);
char				*ft_strchr(char *s, int c);
void				replace_exit_status(t_ms *ms, char *exit_status_str,
						size_t *j, size_t *k);
void				handle_exit_code(t_ms *ms, size_t i);
void				check_for_sign(t_ms *ms, size_t i, size_t *j, size_t *k);
void				add_new_env(t_ms *ms, t_list **lst);
void				export_new_env(t_ms *ms, t_list **lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_ms				*struct_init(char **envp);
void				check_exit_code(t_ms *ms);
void				handle_redirections(t_ms *ms);
bool				check_if_redirections(t_ms *ms);
void				echo_builtin(t_ms *ms, t_token *token);
void				echo_newline(t_ms *ms, t_token *token, size_t i);
void				wrong_command(char *info, t_ms *ms);
void				echo_env(t_ms *ms);
void				execute_program_name(t_ms *ms);
int					ft_atoi(char *str);
void				increment_shlvl(t_ms *ms);
void				handle_single_output(t_ms *ms, size_t i);
void				handle_double_output(t_ms *ms, size_t i);
void				handle_single_input(t_ms *ms, size_t i);
void				handle_double_input(t_ms *ms, size_t i);
t_token				*parsing(t_ms *ms);
t_token				*token_init(t_ms *ms);
void				get_token(t_ms *ms, t_token *token);
bool				is_space(t_ms *ms);
t_ms				*minishell_init(char **envp);
void				get_word_token(t_ms *ms, t_token *token);
void				count_quotes(t_ms *ms);
char				*free_helper(char **s1, char **s2, char c);
char				*ft_remainder(char *my_buffer);
char				*extract_line(char *my_buffer);
char				*read_new_line(int fd, char *my_buffer);
void				parsing_cleanup(t_ms *ms, t_token *token);
void				create_split_pipes(t_ms *ms, t_token *token);
int					count_pipes(t_token *token);
t_token				*join_pipes(t_ms *ms, t_token *token, int i);
t_token				*create_split_commands(t_ms *ms, t_token *token);
void				check_exit_args(t_ms *ms);
int					count_split_size(t_token *token);
bool				syntax_check(t_ms *ms, t_token *token);
void				cd_home(t_ms *ms);
void				cd_oldpwd(t_ms *ms);
void				print_echo_env(t_ms *ms, size_t *k, size_t *l);
void				handle_sigint(int signum, siginfo_t *info, void *context);
void				handle_sigint_ignore(int signum, siginfo_t *info,
						void *context);
void				handle_sigquit(int signum, siginfo_t *info, void *context);
void				setup_termios(void);
int					setup_sigint(void);
int					setup_sigint_ignore(void);
int					setup_sigquit(void);
void				handle_sigquit_ignore(int signum, siginfo_t *info,
						void *context);
int					setup_sigquit_ignore(void);

#endif