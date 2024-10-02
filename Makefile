# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:15:39 by paprzyby          #+#    #+#              #
#    Updated: 2024/10/02 16:58:19 by dpaluszk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOUR_GREEN	=	\033[0;32m
COLOUR_END		=	\033[0m

NAME		=	minishell

SOURCE		=	minishell.c utils/ft_split.c utils/ft_strlcat.c \
				utils/ft_strlcpy.c utils/ft_strlen.c utils/ft_strncmp.c \
				exit_minishell.c main.c builtins/cd_builtin.c \
				execution/check_builtin.c builtins/env_builtin.c \
				builtins/unset_builtin.c builtins/export_builtin.c \
				builtins/exit_builtin.c execution/prepare_for_execution.c \
				utils/ft_strjoin.c utils/ft_strnstr.c utils/ft_strrchr.c \
				utils/ft_substr.c utils/ft_itoa.c utils/ft_strdup.c parsing/parsing.c \
				utils/ft_strchr.c parsing/replace_exit_status.c utils/ft_lstadd_back.c \
				init/copy_env.c init/struct_init.c execution/execute_command.c \
				execution/execute_builtin.c parsing/quotes.c builtins/echo_builtin.c \
				utils/ft_atoi.c redirections.c

OBJECTS		=	$(SOURCE:.c=.o)

CC			=	gcc

RM			=	rm -f

FLAGS		=	-Wall -Wextra -Werror -g

LFLAGS		=	-lreadline

$(NAME):	$(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(LFLAGS) -o $(NAME)
	@echo "$(COLOUR_GREEN)$(NAME) built successfully!$(COLOUR_END)"

%.o:			%.c minishell.h
				$(CC) $(FLAGS) -c $< -o $@

all:			$(NAME)

clean:
	$(RM) -rf $(OBJECTS)
	@echo "$(COLOUR_GREEN)objects removed successfully..$(COLOUR_END)"

fclean:	clean
	$(RM) $(NAME) $(OBJECTS)
	@echo "$(COLOUR_GREEN)$(NAME) cleaned successfully..$(COLOUR_END)"

re:				fclean all

.PHONY:			all clean fclean re
