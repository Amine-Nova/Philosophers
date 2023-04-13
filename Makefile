NAME = philo

LIBRARY = philo.h

SRCS =	philo.c \
		check_error.c \
		function.c \
		utils.c \
		main.c 

CC = gcc

CFLAGS = -Wall -Werror -Wextra

OBJ = ${SRCS:.c=.o}

all : $(NAME)

%.o : %.c 
	@$(CC) $(CFLAGS) -c $^ -o $@

$(NAME) : $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
