#ifndef WORLD_H
# define WORLD_H

#include "../includes.h"

typedef struct s_world
{
	char			***world;
	char			**chunk;
	t_biome			**biome;
	uint32_t		abiant_sound;
	int				height;
	int				width;
	uint32_t		bt_color[2];
	mlx_image_t 	*ceil;
	mlx_image_t 	*floor;
	Difficulty		difficulty;
	bool			is_active;
}	t_world;

t_world			g_worlds[2];

//loader
void	world_loader(t_core *core);
bool	world_creator(t_world *world, uint32_t anbiant_sound, int height, int width, const uint32_t bt_color[2], mlx_image_t *ceil, mlx_image_t *floor, Difficulty difficulty, bool is_active);
void	chunk_generator(t_world *map, int chunk);

//accessor
t_world	*get_world(int num);
void	set_world(t_world map, int num);

//utils
t_world	*get_active_world(void);
bool    is_player_chunk_change(t_player *player, t_world *world);
int		get_chunk_from_pos(int x, int y);
bool    world_dynamic_generator(t_player *player);
void	print_entire_world(void);

#endif
