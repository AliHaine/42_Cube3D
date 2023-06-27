SRCS		=	ft_isalpha.c \
				ft_isdigit.c \
				ft_lstclear.c \
			 	ft_memcpy.c \
			 	ft_lstmap.c

NAME		=	libft.a

OBJS		=	${SRCS:.c=.o}

FLAGS		=	-Wall -Wextra -Werror

GCC			=	gcc

RM			=	rm -f

all:		${NAME}

.c.o:
			@${GCC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@ar rc ${NAME} ${OBJS}

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
