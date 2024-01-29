SRC		=	src/cub3d.c \
				src/inputs/inputs.c \
				src/inputs/moves.c \
				src/inputs/mouse_cursor.c \
				src/inputs/mouse.c \
				src/inputs/scroll_hook.c \
				src/graphics/display.c \
				src/graphics/animations.c \
				src/graphics/texture_loader.c \
				src/graphics/raycast/digital_differential_analysis.c \
                src/graphics/raycast/drawing.c \
                src/graphics/raycast/ceil_and_floor.c \
                src/graphics/raycast/struct_drawing.c \
                src/graphics/raycast/raycast_utils.c \
                src/graphics/sprite/sprites.c \
                src/graphics/sprite/sprites_manager.c \
                src/graphics/sprite/sprites_utils.c \
                src/graphics/sprite/sprites_utils_bis.c \
                src/graphics/sprite/move_multiple_sprites.c \
				src/parsing/map_manager.c \
				src/parsing/map_parse.c \
				src/parsing/map_texture.c \
				src/parsing/options_initializer.c \
				src/sound/sound_loader.c \
				src/sound/sound.c \
				src/sound/sound_accessor.c \
				src/player_interaction/player_listener.c \
				src/player_interaction/heal.c \
				src/player_interaction/build.c \
				src/player_interaction/energy.c \
				src/player_interaction/inventory.c \
				src/player_interaction/inventory_manager.c \
				src/player_interaction/crafting.c \
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
				src/block/portal/portal_accessor.c \
				src/block/portal/portal_loader.c \
				src/block/portal/portal.c \
				src/utils/map_utils.c \
				src/utils/msg_utils.c \
				src/utils/std_func_utils.c \
				src/utils/std_func_utils_bis.c \
				src/utils/std_func_utils_tris.c \
				src/utils/file_utils.c \
				src/utils/move_utils.c \
				src/utils/mlx_texture_utils.c \
				src/utils/player_utils.c \
				src/utils/get_next_line/get_next_line.c \
				src/utils/get_next_line/get_next_line_utils.c \
				src/utils/inventory_utils.c \
				src/utils/inventory_utils_bis.c \
				src/utils/inventory_utils_tris.c \
				src/utils/ft_split.c \
				src/utils/crafting_utils.c \
				src/utils/struct_slot.c

UNAME := $(shell uname)

PATH_MLX = ./libs/MLX42

OBJS_DEFAULT	= ${SRC:.c=.o}

CFLAGS = -Ofast

ifeq ($(UNAME), Darwin)
FLAGS = -L./libs/bass -lbass "./libs/MLX42/build/libmlx42.a" -lglfw -framework OpenGL -framework AppKit
LINUX = false
MACH_EXTRA = install_name_tool -change @loader_path/libbass.dylib ./libs/bass/libbass.dylib $(NAME)
else
FLAGS = -Ibass -L./libs/bass -lbass "./libs/MLX42/build/libmlx42.a" -ldl -lglfw -pthread -lm -Wl,-rpath=./libs/bass/,-rpath=./libs/MLX42/
LINUX = true
endif

NAME = cub3D
CC = gcc
RM = rm -rf

all: ${NAME}

.c.o:
			${CC} ${CFLAGS} -Imlx -Ibass -c $< -o ${<:.c=.o} -D LINUX=${LINUX}

$(NAME): $(OBJS_DEFAULT)
			cmake -B libs/MLX42/build -S libs/MLX42
			cmake --build libs/MLX42/build -j4
			${CC} $(CFLAGS) -o $(NAME) $(OBJS_DEFAULT) $(OBJS_BONUS) $(FLAGS)
			${MACH_EXTRA}

clean:
			${RM} ${OBJS_DEFAULT}

fclean: clean
			${RM} ./libs/MLX42/build
			${RM} ${NAME}

re: fclean all

.PHONY:		all clean fclean re



