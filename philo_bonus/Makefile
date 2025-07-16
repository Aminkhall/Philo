NAME 	=	philo_bonus
CC 		=	cc

HEADER 	=	philo_bonus.h

CFLAGS 	= 	-Wall -Wextra -Werror #-fsanitize=thread

SRC 	=	functions.c \
			inti_data.c \
			parsing.c \
			philo_bonus.c \
			process.c \
			utils.c \
			


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