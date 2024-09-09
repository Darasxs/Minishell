# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:15:39 by paprzyby          #+#    #+#              #
#    Updated: 2024/09/09 12:16:24 by paprzyby         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOUR_GREEN	=	\033[0;32m
COLOUR_END		=	\033[0m


NAME		=	minishell

SOURCE		=	minishell.c

OBJECTS		=	$(SOURCE:.c=.o)

CC			=	cc

RM			=	rm -f

FLAGS		=	-Wall -Wextra -Werror

$(NAME):	$(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
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
