SRCS		=	src/cub3d.c \
				src/inputs/inputs.c \
				src/inputs/moves.c \
				src/graphics/display.c \
				src/graphics/raycast.c \
				src/parsing/map_manager.c \
				src/parsing/map_parse.c \
				src/parsing/map_texture.c \
				src/utils/map_utils.c \
				src/utils/msg_utils.c \
				src/utils/std_func_utils.c \
				src/utils/struct_utils.c \
				src/utils/get_next_line/get_next_line.c \
				src/utils/get_next_line/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	cub3d

FLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT		=	libft/libft.a

MLX42		=	"../MLX42/libmlx42.a" -I include -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib"

CFLAGS		=	-I include -I ../MLX42/include

MLX42		=	../MLX42/libmlx42.a -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"

CFLAGS		=	-I ../MLX42/include

RM			=	rm -rf

.c.o:
			gcc $(FLAGS) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C Libft
			gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME)
clean:
			$(MAKE) -C Libft clean
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) -C Libft fclean
			$(RM) $(NAME)

re:			fclean all
			$(MAKE) -C Libft re

bonus:		$(NAME)

.PHONY:		all clean fclean re
