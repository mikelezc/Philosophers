# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 18:59:24 by mlezcano          #+#    #+#              #
#    Updated: 2024/02/25 21:19:24 by mlezcano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		=	/bin/bash

#compiler

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -f
ECHO		= echo -e
FSANITIZE	= -fsanitize=address -g3

#output
NAME		= philo

#directories
SRC_DIR		= src/
OBJ_DIR		= obj/

#include
INC			= inc
HEADER		= -I inc

#colors
DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

#src directories
PHILO_DIR	=	philo/

#src files
PHILO_FILES	=	philo errors

SRC_FILES	=	$(addprefix $(PHILO_DIR), $(PHILO_FILES))

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

COMMON 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(COM_FILES)))
COBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(COM_FILES)))

OBJF		=	.cache_exists

start:
			@$(ECHO) -n "$(GREEN)[Dependencies]:\t$(DEF_COLOR)"
			@$(ECHO) -n "$(GREEN)[$(DEF_COLOR)"
			@make all

all:		$(NAME)

$(NAME):	$(OBJ) $(COBJ) $(OBJF)
			@$(ECHO) -n "$(GREEN)]$(DEF_COLOR)"
			@$(ECHO) -n "$(GREEN) => OK! $(DEF_COLOR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJF)
			@$(ECHO) -n "$(DEF_COLOR)=$(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(PHILO_DIR)
			@touch $(OBJF)

clean:
			@$(RM) -r $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@$(ECHO) -n "$(RED)[philo]:\tobject files$(DEF_COLOR)$(YELLOW)  => Clean! 🚽$(DEF_COLOR)\n"
			@$(RM) $(OBJF)

fclean:		clean
			@$(RM) $(NAME)
			@rm -rf *.dSYM
			@find . -name ".DS_Store" -delete
			@$(ECHO) -n "$(RED)[philo]:\texec. files$(DEF_COLOR)$(YELLOW)  => Clean! 🚽$(DEF_COLOR)\n"


re:			fclean all
			@$(ECHO) -n "$(GREEN)Cleaned and rebuilt everything for [philo]! 🙌🙌🙌$(DEF_COLOR)\n"

.PHONY:		all clean fclean re