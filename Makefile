SRCS		=	src/cub3d.c \
				src/inputs/inputs.c \
				src/inputs/moves.c \
				src/inputs/mouse.c \
				src/graphics/display.c \
				src/graphics/raycast.c \
				src/graphics/textures.c \
				src/graphics/wall_direction.c \
				src/graphics/obstacle_direction.c \
				src/parsing/map_manager.c \
				src/parsing/map_parse.c \
				src/parsing/map_texture.c \
				src/utils/map_utils.c \
				src/utils/msg_utils.c \
				src/utils/std_func_utils.c \
				src/utils/struct_utils.c \
				src/utils/file_utils.c \
				src/utils/raycast_utils.c \
				src/utils/mlx_texture_utils.c \
				src/utils/get_next_line/get_next_line.c \
				src/utils/get_next_line/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	cub3d

FLAGS		=	-g3 -fsanitize=address

MLX42		=	"../MLX42/build/libmlx42.a" -I include -lglfw -lm -ldl -L "/Users/$$USER/.brew/opt/glfw/lib"

CFLAGS		=	-I include -I ../MLX42/include

CFLAGS		=	-I ../MLX42/include

RM			=	rm -rf

.c.o:
			gcc $(FLAGS) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX42) -o $(NAME)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(NAME)

.PHONY:		all clean fclean re
