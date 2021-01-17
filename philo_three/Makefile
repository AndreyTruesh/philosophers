# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abibi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/10 03:39:47 by abibi             #+#    #+#              #
#    Updated: 2021/01/17 17:57:07 by abibi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
FLAGS = -Wall -Wextra -Werror
SRCS = global_monitors.c init.c main.c philo.c report_status.c threads.c \
	   utils_1.c utils_2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME) -lpthread

%.o: %.c philo_three.h
	gcc $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, re, clean, fclean
