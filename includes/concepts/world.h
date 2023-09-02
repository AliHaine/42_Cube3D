/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:40:50 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/22 20:40:53 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../includes.h"
# include "biome.h"

typedef struct	s_sounds t_sounds;

typedef enum {
	WORLD_DEFAULT,
	WORLD_NETHER,
	WORLD_END,
	WORLD_BACKROOM,
	WORLD_NUMBER,
}	World;

typedef struct s_world
{
	World			world_name;
	char			***world;
	t_biome			**biome;
	t_sounds 		*ambiant_sound;
	int				height;
	int				width;
	uint32_t		bt_color[2];
	mlx_image_t		*ceil;
	mlx_image_t		*floor;
	Difficulty		difficulty;
	bool			skybox;
	bool			is_active;
}	t_world;

//loader
void	world_loader(t_core *core);
bool	world_creator(World world, t_biome **biomes, t_sounds *ambient_sound, int height, int width, const uint32_t bt_color[2], mlx_image_t *ceil, mlx_image_t *floor, Difficulty difficulty, bool is_active, bool skybox);
void	chunk_generator(t_world *world, int chunk);

//accessor
t_world	*get_world(int num);
t_world	*get_world_active(void);
t_world *get_world_from_portal(char c);
void	set_world(t_world world, int num);
void set_world_biomes(World world, t_biome **biomes);

//utils
bool    is_player_chunk_change(t_player *player, t_world *world);
int		get_chunk_from_pos(int x, int y);
bool	is_chunk_on_corner(int chunk_num);
bool    world_dynamic_generator(t_player *player);
void	change_active_world(t_world	*new_world);

//biome
void	biome_loader(void);

#endif
