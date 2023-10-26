# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 17:38:36 by gabrrodr          #+#    #+#              #
#    Updated: 2023/10/25 17:44:30 by gabrrodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

NAME = minishell

SRC = 	src/main.c \
		src/init.c \
		src/frees.c \
		src/utils.c

OBJ_SRC = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: deps $(NAME)

deps:
	$(MAKE) -C ./libs/libft

$(NAME): $(OBJ_SRC) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) clean -C ./libs/libft
	@$(RM) $(OBJ_SRC)

fclean: clean
	@$(RM) $(LIBFT) $(NAME)
	
re: fclean all