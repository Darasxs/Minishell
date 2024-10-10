/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:45:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/10 18:09:18 by paprzyby         ###   ########.fr       */
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

typedef struct s_token
{
	char 			*value;
	struct s_token	*next;
	//struct s_token *prev;
}					t_token;

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
	int				input_fd;
	int				output_fd;
	int				input_pos;
	int				input_len;
	int				single_q;
	int				double_q;
	int				token_count;
	bool			pipe;
	bool			first_iteration;
	t_list			*lst;
	t_token			*token;
}					t_minishell;

void				printing_prompt(t_minishell *ms);
char				**ft_split(char *s, char c);
size_t				ft_strlen(char *str);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlcat(char *dest, char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
void				ft_error(char *str, t_minishell *ms);
void				free_split(char **split);
void				free_struct(t_minishell *ms);
void				execute_command(t_minishell *ms, t_token *token);
bool				preparing_execution(t_minishell *ms);
char				*find_path(char *path, t_minishell *ms);
void				minishell(t_minishell *ms, t_token *token);
void				cd_builtin(t_minishell *ms, t_token *token);
bool				check_builtin(t_minishell *ms, t_token *token);
void				env_builtin(t_minishell *ms);
void				unset_builtin(t_minishell *ms);
void				export_builtin(t_minishell *ms);
void				prompt_helper(char **cwd, char **user_name,
						t_minishell *ms);
char				*ft_strrchr(char *s, char c);
char				*ft_substr(char *s, size_t start, size_t len);
char				**envp_init(char **envp);
void				exit_builtin(t_minishell *ms);
void				execute_builtin(t_minishell *ms, t_token *token);
bool				check_cd(t_minishell *ms);
bool				check_env(t_minishell *ms);
void				handle_builtins(t_minishell *ms, t_token *token, int *input_fd, int *fd);
void				handle_child_process(t_minishell *ms, t_token *token, int *input_fd, int *fd);
void				handle_parent_process(t_token *token, int *input_fd, int *fd);
void				execute_pipe_commands(t_minishell *ms, t_token *token, int *input_fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnstr(char *haystack, char *needle, size_t size);
char				*ft_itoa(int n);
unsigned int		ft_size(int number);
char				*ft_strdup(char *s1);
char				*ft_strchr(char *s, int c);
void				replace_exit_status(t_minishell *ms,
						char *exit_status_str, size_t *j, size_t *k);
void				append_dollar_sign(t_minishell *ms, size_t *j, size_t *k);
void				append_question_mark(t_minishell *ms, size_t *j,
						size_t *k);
void				handle_exit_code(t_minishell *ms, size_t i);
void				check_for_sign(t_minishell *ms, size_t i, size_t *j,
						size_t *k);
void				add_new_env(t_minishell *ms, t_list **lst);
void				update_env_copy(t_minishell *ms, t_list *tmp);
void				export_new_env(t_minishell *ms, t_list **lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_minishell			*struct_init(char **envp);
void				check_exit_code(t_minishell *ms);
void				check_redirections(t_minishell *ms);
void				echo_builtin(t_minishell *ms);
void				print_echo(t_minishell *ms, size_t i);
void				wrong_command(char *info, t_minishell *ms);
void				echo_env(t_minishell *ms);
void				execute_program_name(t_minishell *ms, t_token *token);
int					ft_atoi(char *str);
void				increment_shlvl(t_minishell *ms);
void				handle_single_output(t_minishell *ms, size_t i);
void				handle_double_output(t_minishell *ms, size_t i);
void				handle_single_input(t_minishell *ms, size_t i);
void				handle_double_input(t_minishell *ms, size_t i);
t_token				*parsing(t_minishell *ms);
t_token				*token_init(t_minishell *ms);
void				get_token(t_minishell *ms, t_token *token);
bool				is_space(t_minishell *ms);
void				empty_quotes(t_minishell *ms, t_token *token);
t_minishell			*minishell_init(char **envp);
void				get_word_token(t_minishell *ms, t_token *token);
void				count_quotes(t_minishell *ms);
void				create_split_commands(t_minishell *ms, t_token *token);

#endif
