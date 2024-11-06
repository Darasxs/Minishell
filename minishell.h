/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/06 15:25:43 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_token
{
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_heredoc
{
	char				*filename;
	int					fd;
	int					pipe_index;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_minishell
{
	char				**split_env;
	char				**env_copy;
	char				*prompt;
	char				*input;
	char				*path;
	char				*env;
	char				*full_path;
	char				*exit_code;
	int					exit_status;
	int					input_pos;
	int					input_len;
	int					single_q;
	int					double_q;
	int					token_count;
	bool				first_iteration;
	t_token				*token;
	t_token				*head;
	char				**split_commands;
	char				**split_pipes;
	int					heredoc_file_descriptor;
	char				*temp_filename;
	char				*user_name;
	t_heredoc			*heredocs;
	bool				heredoc_found;
	int					status;
}						t_ms;

//	utils:
char					**ft_split(char *s, char c);
size_t					ft_strlen(char *str);
size_t					ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t					ft_strlcat(char *dest, char *src, size_t size);
int						ft_strncmp(const char *s1, const char *s2, size_t len);
char					*ft_strrchr(char *s, char c);
char					*ft_substr(char *s, size_t start, size_t len);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strnstr(char *haystack, char *needle, size_t size);
char					*ft_itoa(int n);
unsigned int			ft_size(int number);
char					*ft_strdup(char *s1);
char					*ft_strchr(char *s, int c);
int						ft_atoi(char *str);
char					*ft_strtrim(char *s1, char *set);
int						ft_check(char c, const char *set);
void					ft_putstr_fd(char *s, int fd);

// get_next_line:
char					*free_helper(char **s1, char **s2, char c);
char					*ft_remainder(char *my_buffer);
char					*extract_line(char *my_buffer);
char					*read_new_line(int fd, char *my_buffer);
char					*get_next_line(int fd);

//	builtins:
void					cd_home(t_ms *ms);
void					cd_builtin(t_ms *ms);
void					echo_builtin(t_ms *ms, t_token *token);
void					echo_newline(t_ms *ms, size_t i);
void					echo_env(t_ms *ms);
void					echo_single_q(t_ms *ms);
void					env_builtin(t_ms *ms);
void					check_exit_args(t_ms *ms);
void					exit_builtin(t_ms *ms);
int						check_for_int(char *str);
void					export_builtin(t_ms *ms);
void					pwd_builtin(t_ms *ms);
void					unset_builtin(t_ms *ms);
void					add_new_env(t_ms *ms, char *env);

//	execution:
void					execute_builtin(t_ms *ms);
bool					check_builtin(t_ms *ms);
bool					check_cd_and_unset(t_ms *ms);
char					*find_path(char *path, t_ms *ms);
void					execute_command(t_ms *ms);
void					execute_program_name(t_ms *ms);
char					*ft_getenv(char *env, t_ms *ms);
void					execution_error(t_ms *ms, bool flag);

//	minishell_helper:
int						count_split_size(t_token *token);
void					remove_quotes(t_ms *ms, int split);
t_token					*create_split_commands(t_ms *ms, t_token *token);
void					create_split_pipes(t_ms *ms, t_token *token);
int						count_pipes(t_token *token);
t_token					*join_pipes(t_ms *ms, t_token *token, int i);
void					free_split(char **split);
void					ft_error(char *str, t_ms *ms);
void					cleanup(t_ms *ms);
void					free_list(t_ms *ms, t_token *token);
char					**envp_init(char **envp);
t_ms					*minishell_init(char **envp);
void					handle_builtins(t_ms *ms, int i, int *input_fd,
							int *fd);
void					handle_cd_and_unset(t_ms *ms, int i, int *input_fd,
							int *fd);
void					handle_child_process(t_ms *ms, int i, int *input_fd,
							int *fd);
void					handle_parent_process(t_ms *ms, int i, int *input_fd,
							int *fd);
void					execute_pipe_commands(t_ms *ms, int *input_fd, int i);
void					minishell(t_ms *ms);
void					prompt_helper(char **cwd, char **user_name, t_ms *ms);
void					prompt(t_ms *ms);
void					replace_exit_status(t_ms *ms, char *exit_status_str,
							size_t *j, size_t *k);
void					check_for_sign(t_ms *ms, size_t i, size_t *j,
							size_t *k);
void					handle_exit_code(t_ms *ms, size_t i);
void					check_exit_code(t_ms *ms);
void					increment_shlvl(t_ms *ms);
void					update_shlvl(t_ms *ms, char *shlvl_str, size_t i);
bool					isatty_helper(t_ms *ms);
void					cleanup_heredocs(t_ms *ms);
void					heredoc_setup(t_ms *ms, int i);
bool					double_input_check(t_ms *ms);
void					exit_minishell(t_ms *ms);
bool					helper3(t_ms *ms, int i);

//	parsing:
t_token					*token_init(t_ms *ms);
bool					is_space(t_ms *ms);
t_token					*parsing(t_ms *ms);
bool					syntax_check(t_ms *ms);
int						get_token(t_ms *ms, t_token *token);
int						get_word_token(t_ms *ms, t_token *token);
bool					export_syntax_check(t_ms *ms);
bool					unset_syntax_check(t_ms *ms);
bool					pipes_check(t_ms *ms, t_token *token);
void					expand_env(t_ms *ms);
void					export_error(t_ms *ms, bool flag);
void					unset_error(t_ms *ms, bool flag);
void					syntax_error(t_ms *ms, bool flag);
bool					export_helper(t_ms *ms, int i);
bool					unset_helper(t_ms *ms, int i);

//	redirections:
void					handle_single_output(t_ms *ms, size_t i);
void					handle_double_output(t_ms *ms, size_t i);
void					handle_single_input(t_ms *ms, size_t i);
void					handle_double_input(t_ms *ms, size_t i, int pipe_index);
void					handle_redirections(t_ms *ms);
bool					check_if_redirections(t_ms *ms);
void					cleanup_heredocs(t_ms *ms);
bool					helper(t_ms *ms);
t_heredoc				*heredoc_init(int pipe_index);
t_heredoc				*heredoc_init_helper(t_heredoc *new_heredoc);
void					heredoc_while_loop(t_heredoc *new_heredoc,
							char *eof_delimiter);
void					handle_double_input(t_ms *ms, size_t command_index,
							int pipe_index);
void					double_input_helper(t_ms *ms, int i, int pipe_index);
bool					double_input_check(t_ms *ms);
void					cleanup_heredocs(t_ms *ms);
void					heredoc_setup(t_ms *ms, int i);

//	signals:
void					handle_sigint(int signum, siginfo_t *info,
							void *context);
void					ignore_signals(int signum, siginfo_t *info,
							void *context);
int						setup_sigint(void);
int						setup_sigint_ignore(void);
int						setup_sigquit(void);
int						setup_sigquit_ignore(void);
void					setup_termios(void);

#endif
