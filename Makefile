# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atyurina <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 13:56:02 by atyurina          #+#    #+#              #
#    Updated: 2024/03/15 15:53:58 by atyurina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
SRC := philo.c utils.c set_arguments.c get_time.c forks.c free_memory.c \
		destroy.c init.c stdout.c monitoring.c routine.c

OBJ := $(SRC:.c=.o)
BOBJ := $(BONSRC:.c=.o)
#-fsanitize=thread -g3 -gdwarf-3

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3 -gdwarf-3 #-fsanitize=thread 
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

bonus: $(OBJ) $(BOBJ)
	ar -rcs $(NAME) $(OBJ) $(BOBJ)

.PHONY: all clean fclean re
