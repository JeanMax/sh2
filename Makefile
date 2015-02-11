#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2015/02/11 21:59:41 by mcanal           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	ft_minishell2
C_SRC =	main.c				error.c				handle_env.c		\
		prompt.c			exec.c				signal.c
C_BUI =	builtin.c			exit.c				env.c				\
		unsetenv.c			cd.c				setenv.c
C_RED =	redirection.c		space_error.c							\
		simple_right.c		simple_left.c							\
		double_right.c		double_left.c							\
		simple_pipe.c		
O_DIR =	obj
VPATH =	src:src/builtin:src/redirection
SRCC = 	$(C_SRC:%.c=src/%.c)		$(C_BUI:%.c=src/builtin/%.c)	\
		$(C_RED:%.c=src/redirection/%.c)
SRCO =	$(C_SRC:%.c=$(O_DIR)/%.o)	$(C_BUI:%.c=$(O_DIR)/%.o)		\
		$(C_RED:%.c=$(O_DIR)/%.o)	
LIB =	libft/libft.a
INC =	inc/header.h
CC =	gcc
RM =	rm -f
CFLAGS = -Wall -Werror -Wextra -I./inc/

.PHONY: all lib soft debug optimize clean fclean zclean re

all: 
	@make -C libft
	@$(MAKE) $(NAME)

$(NAME): $(SRCO) $(LIB) $(INC)
	$(CC) $(CFLAGS) $(SRCO) $(LIB) -o $@

$(O_DIR)/%.o: %.c
	@$(RM) $(NAME)
	$(CC) $(CFLAGS) -c $^ -o $@

soft:
	@$(RM) $(NAME)
	@$(CC) $(SRCC) $(LIB) -o $(NAME)
	@./$(NAME)

debug: re
	@$(CC) $(CFLAGS) -ggdb $(SRCO) $(LIB) -o $(NAME)
	@gdb $(NAME)

optimize: re
	@$(CC) $(CFLAGS) -O2 $(SRCO) $(LIB) -o $(NAME)

clean:
	@$(RM) $(SRCO)

fclean: clean
	@$(RM) $(NAME)

zclean: fclean
	@$(RM) $(LIB)

re: fclean all

