CC = cc
CFLAGS = -Wextra -Wall -Werror

SRC_C = client.c
SRC_S = server.c
BONUS_SRC_C = client_bonus.c
BONUS_SRC_S = server_bonus.c

OBJ = obj

SRCOBJ_C = $(SRC_C:%.c=${OBJ}/%.o)
SRCOBJ_S = $(SRC_S:%.c=${OBJ}/%.o)
SRCOBJ_BONUS_C = $(BONUS_SRC_C:%.c=${OBJ}/%.o)
SRCOBJ_BONUS_S = $(BONUS_SRC_S:%.c=${OBJ}/%.o)

all: client server

client: $(SRCOBJ_C)
	@$(CC) $^ -o client

server: $(SRCOBJ_S)
	@$(CC) $^ -o server

bonus: server_bonus client_bonus 

client_bonus: $(SRCOBJ_BONUS_C)
	@$(CC) $^ -o client_bonus

server_bonus: $(SRCOBJ_BONUS_S)
	@$(CC) $^ -o server_bonus

${OBJ}/%.o : %.c
	@mkdir -p $(OBJ)	
	@$(CC) $(CFLAGS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf client server client_bonus server_bonus

re: fclean all

.PHONY: all, clean, fclean, re
