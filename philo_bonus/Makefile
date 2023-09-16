SRC = main.c linked_phil_bonus.c state_bonus.c helpers_bonus.c

OBJ =  ${SRC:.c=.o}
WWW = -Wall -Wextra -Werror #-fsanitize=thread -g
NAME = philo_bonus

%.o: %.c
	@gcc ${WWW} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	@gcc ${WWW} -pthread $^ -o $@

clean:
	@rm -rf ${OBJ}

fclean:
	@rm -rf ${OBJ} ${NAME}

re: fclean all

.PHONY: all clean fclean re
