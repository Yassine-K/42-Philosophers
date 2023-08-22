SRC = main.c linked_phil.c state.c

OBJ =  ${SRC:.c=.o}

NAME = philo

%.o: %.c
	@gcc -Wall -Wextra -Werror -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	@gcc -Wall -Wextra -Werror $^ -o $@

clean:
	@rm -rf ${OBJ}

fclean:
	@rm -rf ${OBJ} ${NAME}

re: fclean all

.PHONY: all clean fclean re
