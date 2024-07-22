# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 12:31:17 by adbouras          #+#    #+#              #
#    Updated: 2024/07/22 09:11:27 by adbouras         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN	= \033[1;92m
YLW	= \033[1;93m
RED	= \033[1;91m
RST	= \033[0;39m

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC =  main.c philo.c handlers.c actions.c clean.c routine.c setters.c getters.c utils.c checkers.c

OBJ_DIR = objects/

HDR = philo.h

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

NAME = philo

all: $(NAME)

$(OBJ_DIR)%.o:%.c $(HDR)
	@echo "$(YLW)[Creating Object $@]$(RST)"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(YLW)[Compiling ...]$(RST)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GRN)[Compiled]$(RST)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[Removed Objects]$(RST)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[Removed EXE]$(RST)"

re: fclean all
