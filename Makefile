# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiranda <smiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 13:47:36 by smiranda          #+#    #+#              #
#    Updated: 2024/10/08 14:08:40 by smiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = dinner.c\
		getters_setters.c\
		init.c\
		main.c\
		monitor.c\
		parsing.c\
		safe_functions.c\
		synchro_utils.c\
		utils.c\
		write.c\

OBJS = ${SRCS: .c=.o}
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
