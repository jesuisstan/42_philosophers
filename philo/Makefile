# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaren <acaren@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 17:33:58 by acaren            #+#    #+#              #
#    Updated: 2021/08/24 17:39:41 by acaren           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	philo

SRCS			=	./src/philosophers.c	./src/ph_parse_arguments.c \
					./src/ph_printer.c		./src/ph_timer.c \
					./src/utils.c \

OBJS			=	$(SRCS:.c=.o)

HEADERS			=	./inc/philosophers.h

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
