SRCS		=	main.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	cub3d

FLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

MLX42		=	"/Users/ngalzand/sgoinfre/ngalzand/MLX42/build/libmlx42.a" -I include -lglfw -L "/Users/ngalzand/.brew/opt/glfw/lib"

CFLAGS		=	-I include -I /Users/ngalzand/sgoinfre/ngalzand/MLX42/include

RM			=	rm -rf

.c.o:
			gcc $(FLAGS) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(FLAGS) $(OBJS) $(MLX42) -o $(NAME)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(NAME)

.PHONY:		all clean fclean re
