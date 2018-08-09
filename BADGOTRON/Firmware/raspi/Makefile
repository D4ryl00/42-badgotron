# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amordret <amordret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/30 15:31:03 by amordret          #+#    #+#              #
#    Updated: 2018/05/30 16:21:14 by amordret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = raspi

SRCPATH = ./srcs/

OBJPATH = ./obj/

IPATH = ./includes/

SRC = main.c\
libft.c\
error.c\
time.c\
misctools.c\
respond.c\
uart.c\
name.c\

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:%.c=$(OBJPATH)%.o)

all : $(NAME)

$(OBJ): $(OBJPATH)%.o: $(SRCPATH)%.c ./includes/raspi.h
	clang $(FLAGS) -o $@ -c $< -I$(IPATH)

$(NAME): $(OBJ)
	clang $(FLAGS) -o $(NAME) $(OBJ)

clean: 
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
