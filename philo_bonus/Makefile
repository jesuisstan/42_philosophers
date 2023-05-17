# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: St.Krivtsov <stan.krivtsov@gmail.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 17:33:58 by acaren            #+#    #+#              #
#    Updated: 2023/05/17 22:05:22 by St.Krivtsov      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	philo_bonus

SRCS			=	./src/philo_bonus.c		./src/phb_parse_arguments.c \
					./src/phb_printer.c		./src/phb_timer.c \
					./src/utils.c			./src/phb_threads.c \

OBJS			=	$(SRCS:.c=.o)

HEADERS			=	./inc

CC				=	gcc

RM				=	rm -rfv

CFLAGS			=	-Wall -Wextra -Werror -I$(HEADERS)

LIBS			=	-lpthread

all:			$(NAME)

$(OBJS):		$(HEADERS)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
				$(RM) $(OBJS)
				@echo "\033[36;1m\nCleaning succeed\n\033[0m"

fclean:			clean
				$(RM) $(NAME)
				@echo "\033[32;1m\nAll created files were deleted\n\033[0m"

re:				fclean $(NAME)
				@echo "\033[35;1m\nRemake done\n\033[0m"

.PHONY:			all clean fclean re
