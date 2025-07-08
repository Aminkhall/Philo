NAME 	=	philo
CC 		=	cc

HEADER 	=	philo.h

CFLAGS 	= 	-Wall -Wextra -Werror  #-fsanitize=thread

SRC 	=	philo.c \
			utils.c \
			parsing.c \
			functions.c \
			getters.c \
			init_data.c \
			setters.c \
			threads.c \
			


OBJ 	= 	${SRC:.c=.o}

all: ${NAME}


${NAME} : ${OBJ}
	 ${CC} ${OBJ} $(CFLAGS) -o ${NAME} 

%.o : %.c $(HEADER)
	 ${CC} $(CFLAGS) -c $< -o $@
	
clean :
	@rm -f ${OBJ}

re: fclean all

fclean : clean
	@rm -f ${NAME}
	
.PHONY: all clean fclean re