# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fadzejli <fadzejli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/09 13:56:55 by fadzejli          #+#    #+#              #
#    Updated: 2025/11/16 18:01:57 by fadzejli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -Wall -Wextra -Werror -g -pthread
SRCS = srcs/main.c srcs/utils.c srcs/mutex_setters.c\
	srcs/utils2.c srcs/init.c srcs/routine.c srcs/monitor.c
OBJS = $(SRCS:.c=.o)
INC = philo.h

all : $(NAME)

%.o : %.c
	$(CC) -I. -c $< -o $@

$(NAME) : $(OBJS) $(INC)
	$(CC) $(OBJS) -o $@

clean :
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
