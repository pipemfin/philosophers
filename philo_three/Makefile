NAME		= philo_three

HEADER		= philo_three.h

SRCS		= clear_functions.c additional_functions.c philo_three.c initializating.c forks.c control.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)

			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re