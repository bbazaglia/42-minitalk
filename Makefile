# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 15:11:18 by bbazagli          #+#    #+#              #
#    Updated: 2024/01/25 13:12:30 by bbazagli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wextra -Wall -Werror
INCLUDE = -I ./include -I ./LIBFT/include
LIBFT = ./LIBFT/libft.a

SRC_C = mandatory/client.c
SRC_S = mandatory/server.c
BONUS_SRC_C = bonus/client_bonus.c
BONUS_SRC_S = bonus/server_bonus.c

OBJ = obj

SRCOBJ_C = $(SRC_C:%.c=${OBJ}/%.o)
SRCOBJ_S = $(SRC_S:%.c=${OBJ}/%.o)
SRCOBJ_BONUS_C = $(BONUS_SRC_C:%.c=${OBJ}/%.o)
SRCOBJ_BONUS_S = $(BONUS_SRC_S:%.c=${OBJ}/%.o)

all: libft client server

client: $(SRCOBJ_C)
	@$(CC) $^ $(LIBFT) -o client

server: $(SRCOBJ_S)
	@$(CC) $^ $(LIBFT) -o server

bonus: libft client_bonus server_bonus

client_bonus: $(SRCOBJ_BONUS_C)
	@$(CC) $^ $(LIBFT) -o client_bonus

server_bonus: $(SRCOBJ_BONUS_S)
	@$(CC) $^ $(LIBFT) -o server_bonus

${OBJ}/%.o : %.c
	@mkdir -p $(dir $@)	
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) && printf "Compiling: $(notdir $<\n)"

libft:
	@make -C ./LIBFT 

clean:
	@make -C ./LIBFT clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C ./LIBFT fclean
	@rm -rf client server client_bonus server_bonus

re: fclean all

.PHONY: all, clean, fclean, re, libft, bonus