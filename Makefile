# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:47:36 by smiranda          #+#    #+#              #
#    Updated: 2024/10/08 16:23:18 by smiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = data_init.c\
		error_exit.c\
		getters_setters.c\
		main.c\
		monitor.c\
		parsing.c\
		routine_launch.c\
		safe_functions.c\
		solo_dinner.c\
		synchro.c\
		time_utils.c\
		write.c\

OBJS = ${SRCS:.c=.o}
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

%.o: %.c
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
