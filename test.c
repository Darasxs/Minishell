#include "minishell.h"

void execute_piped_command(minishell_t *line, char **commands, int i, int *input_fd);
void handle_cd_command(minishell_t *line, char **commands, int i, int j, int *input_fd, int *fd);
void execute_child_process(minishell_t *line, char **commands, int i, int input_fd, int *fd);
void handle_parent_process(char **commands, int i, int *input_fd, int *fd);
void wait_for_children(void);

void minishell(minishell_t *line)
{
    size_t i;
    char **commands;
    int input_fd;

    i = 0;
    input_fd = STDIN_FILENO;
    printing_prompt(line);
    if (line->input)
    {
        add_history(line->input);
        commands = ft_split(line->input, '|');
        while (commands[i])
        {
            execute_piped_command(line, commands, i, &input_fd);
            i++;
        }
        wait_for_children();
        free_split(commands);
    }
    cleanup(line);
}

void execute_piped_command(minishell_t *line, char **commands, int i, int *input_fd)
{
    int fd[2];
    size_t j = 0;

    line->split_commands = ft_split(commands[i], ' ');
    while (commands[j])
        j++;
    if (commands[i + 1] && pipe(fd) == -1)
        ft_error("Error occurred while creating a pipe.\n", NULL, line);
    
    if (line->split_commands[0] && ft_strncmp(line->split_commands[0], "cd", 3) == 0)
        handle_cd_command(line, commands, i, j, input_fd, fd);
    else
    {
        pid_t pid = fork();
        if (pid < 0)
            ft_error("Error occurred while forking.\n", NULL, line);
        else if (pid == 0)
            execute_child_process(line, commands, i, *input_fd, fd);
        else
            handle_parent_process(commands, i, input_fd, fd);
    }
    free_split(line->split_commands);
}

void handle_cd_command(minishell_t *line, char **commands, int i, int j, int *input_fd, int *fd)
{
    if (j == 1 || i == j - 1)
        cd_builtin(line);
    if (commands[i + 1])
    {
        close(fd[1]);
        *input_fd = fd[0];
    }
}

void execute_child_process(minishell_t *line, char **commands, int i, int input_fd, int *fd)
{
    if (i > 0)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (commands[i + 1])
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    close(fd[0]);
    if (check_builtin(line))
        exit(0);
    else
        execute_command(line);
    exit(0);
}

void handle_parent_process(char **commands, int i, int *input_fd, int *fd)
{
    if (commands[i + 1])
    {
        close(fd[1]);
        if (*input_fd != STDIN_FILENO)
            close(*input_fd);
        *input_fd = fd[0];
    }
    else
        close(fd[0]);
}

void wait_for_children(void)
{
    int status;
    while (waitpid(-1, &status, 0) > 0)
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            exit(1);
}