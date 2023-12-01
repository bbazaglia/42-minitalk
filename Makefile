CC = cc
CFLAGS = -Wextra -Wall -Werror

SRC_C = client.c
SRC_S = server.c
OBJ = obj

SRCOBJ_C = $(SRC_C:%.c=${OBJ}/%.o)
SRCOBJ_S = $(SRC_S:%.c=${OBJ}/%.o)

all: client server

client: $(SRCOBJ_C)
	@$(CC) $^ -o client

server: $(SRCOBJ_S)
	@$(CC) $^ -o server


${OBJ}/%.o : %.c
	@mkdir -p $(OBJ)	
	@$(CC) $(CFLAGS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf client server 

re: fclean all

.PHONY: all, clean, fclean, re
