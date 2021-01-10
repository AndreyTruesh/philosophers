# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abibi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/10 03:26:18 by abibi             #+#    #+#              #
#    Updated: 2021/01/10 16:11:06 by abibi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
FLAGS = -Wall -Wextra -Werror
SRCS = init.c main.c monitor.c report_status.c threads.c philo.c \
	   utils_1.c utils_2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME) -lpthread

%.o: %.c philo_one.h
	gcc $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
