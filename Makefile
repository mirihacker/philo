# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:47:36 by smiranda          #+#    #+#              #
#    Updated: 2024/10/08 17:06:17 by smiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC_DIR = ./src/
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

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

NEW_SRCS = $(addprefix $(SRC_DIR), $(SRCS))

OBJS = ${NEW_SRCS:%.c=%.o}


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
