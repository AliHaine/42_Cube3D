SRCS		=	src/cub3d.c \
				src/inputs/inputs.c \
				src/inputs/moves.c \
				src/inputs/mouse_cursor.c \
				src/inputs/mouse.c \
				src/inputs/scroll_hook.c \
				src/graphics/display.c \
				src/graphics/raycast.c \
				src/graphics/textures.c \
				src/graphics/wall_direction.c \
				src/graphics/obstacle_direction.c \
				src/graphics/animations.c \
				src/parsing/map_manager.c \
				src/parsing/map_parse.c \
				src/parsing/map_texture.c \
				src/sound/sound.c \
				src/player_interaction/player_listener.c \
				src/player_interaction/heal.c \
				src/player_interaction/build.c \
				src/player_interaction/energy.c \
				src/utils/map_utils.c \
				src/utils/msg_utils.c \
				src/utils/std_func_utils.c \
				src/utils/struct_utils.c \
				src/utils/file_utils.c \
				src/utils/raycast_utils.c \
				src/utils/move_utils.c \
				src/utils/mlx_texture_utils.c \
				src/utils/get_next_line/get_next_line.c \
				src/utils/get_next_line/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	cub3d

FLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS		+=	-L./src/sound/bass
LDLIBS		+=	-lbass

BASS_CFLAGS	=	-I./src/sound/bass
BASS_LDFLAGS	=	-L./src/sound/bass
BASS_LDLIBS	=	-lbass

MLX42		=	"../MLX42/build/libmlx42.a" -I include -lglfw -lm -ldl -framework Cocoa -framework OpenGL -framework IOKit -L "/Users/$$USER/.brew/opt/glfw/lib"

CFLAGS		+=	-I include -I ../MLX42/include $(BASS_CFLAGS)

RM			=	rm -rf

.c.o:
			gcc $(FLAGS) $(CFLAGS) -Ibass -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX42) $(BASS_LDFLAGS) $(BASS_LDLIBS) -o $(NAME)
	install_name_tool -change @loader_path/libbass.dylib ./src/sound/bass/libbass.dylib $(NAME)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(NAME)

.PHONY:		all clean fclean re
