SRCS		=	src/cub3d.c \
				src/inputs/inputs.c \
				src/inputs/moves.c \
				src/inputs/mouse_cursor.c \
				src/inputs/mouse.c \
				src/inputs/scroll_hook.c \
				src/graphics/display.c \
				src/graphics/animations.c \
				src/graphics/sprites.c \
				src/loading/texture_loader.c \
				src/loading/other_loader.c \
				src/parsing/map_manager.c \
				src/parsing/map_parse.c \
				src/parsing/map_texture.c \
				src/parsing/options_initializer.c \
				src/raycast/digital_differential_analysis.c \
                src/raycast/drawing.c \
                src/raycast/struct_drawing.c \
                src/raycast/raycast_utils.c \
				src/sound/sound_loader.c \
				src/sound/sound.c \
				src/sound/sound_accessor.c \
				src/struct/struct_slot.c \
				src/player_interaction/player_listener.c \
				src/player_interaction/heal.c \
				src/player_interaction/build.c \
				src/player_interaction/energy.c \
				src/player_interaction/inventory.c \
				src/player_interaction/inventory_manager.c \
				src/player_interaction/crafting.c \
				src/player_interaction/portal.c \
				src/player_interaction/teleportation.c \
				src/world/world_accessor.c \
				src/world/world_loader.c \
				src/world/world_utils.c \
				src/world/chunk_utils.c \
				src/world/world_dynamic_generator.c \
				src/world/biome/biome_loader.c \
				src/world/biome/biome_accessor.c \
               	src/world/biome/biome_utils.c \
				src/block/block_accessor.c \
				src/block/block_loader.c \
				src/block/block_utils.c \
				src/item/item_accessor.c \
				src/item/item_loader.c \
				src/item/item.c \
				src/utils/map_utils.c \
				src/utils/msg_utils.c \
				src/utils/std_func_utils.c \
				src/utils/file_utils.c \
				src/utils/move_utils.c \
				src/utils/mlx_texture_utils.c \
				src/utils/player_utils.c \
				src/utils/get_next_line/get_next_line.c \
				src/utils/get_next_line/get_next_line_utils.c \
				src/utils/inventory_utils.c \
				src/utils/inventory_utils_bis.c \
				src/utils/ft_split.c


OBJS		=	$(SRCS:.c=.o)

NAME		=	cub3d
TOTAL_FILES =	$(words $(SRCS))
COUNT		=	1

FLAGS		=	-Ofast -g3 #-fsanitize=address
LDFLAGS		+=	-L./src/sound/bass
LDLIBS		+=	-lbass

BASS_CFLAGS	=	-I./src/sound/bass
BASS_LDFLAGS	=	-L./src/sound/bass
BASS_LDLIBS	=	-lbass

MLX42		=	"../MLX42/build/libmlx42.a" -I include -lglfw -lm -ldl -framework Cocoa -framework OpenGL -framework IOKit -L "/Users/$$USER/.brew/opt/glfw/lib"

CFLAGS		+=	-I include -I ../MLX42/include $(BASS_CFLAGS)

RM			=	rm -rf

%.o: %.c
	@echo "\033[0;33m[$(shell echo $$(($(COUNT)*100/$(TOTAL_FILES))))%] Compiling [$<]... ($(COUNT)/$(TOTAL_FILES) files)\033[0m"
	@gcc $(FLAGS) $(CFLAGS) -Ibass -c $< -o $@
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

all:		$(NAME)

$(NAME):	$(OBJS)
	@echo "\033[32mFinishing...\033[0m"
	@gcc $(FLAGS) $(OBJS) $(LIBFT) $(MLX42) $(BASS_LDFLAGS) $(BASS_LDLIBS) -o $(NAME)
	@install_name_tool -change @loader_path/libbass.dylib ./src/sound/bass/libbass.dylib $(NAME)
	@echo "\033[32m-- Done --\033[0m"

clean:
			@echo "\033[32mCleaning objs files...\033[0m"
			@$(RM) $(OBJS)

fclean:		clean
			@echo "\033[32mCleaning executables...\033[0m"
			@$(RM) $(NAME)

re:			fclean all

bonus:		$(NAME)

.PHONY:		all clean fclean re
