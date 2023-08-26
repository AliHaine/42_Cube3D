/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:35:56 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/02 12:35:57 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	world_malloc(int height, int width, char ***map)
{
	int	i;

	i = 0;
	(*map) = malloc(sizeof(char *) * (height + 1));
	if (!*map)
		return (false);
	(*map)[height] = 0;
	while (i < height)
	{
		(*map)[i] = malloc(sizeof(char) * width + 1);
		if (!(*map)[i])
			return (false);
		(*map)[i][width] = 0;
		i++;
	}
	return (true);
}

bool	world_creator(t_world *world, t_sounds *anbiant_sound, int height, int width, const uint32_t bt_color[2], mlx_image_t *ceil, mlx_image_t *floor, Difficulty difficulty, bool is_active, bool skybox)
{
	int	i;

	i = 0;
	world->biome = 0;
	world->ambiant_sound = anbiant_sound;
	world->height = height;
	world->width = width;
//	world->bt_color[0] = 0;
//	world->bt_color[1] = 0;
	world->ceil = ceil;
	world->floor = floor;
	world->difficulty = difficulty;
	world->world = malloc(sizeof(char **) * 9);
	world->is_active = is_active;
	world->skybox = skybox;
	world_malloc(height, width, &world->chunk);
    while (i < 9)
	    world_malloc(height * 3, width * 3, &world->world[i++]);
    return (true);
}

static void world_generator(t_world *world) {
	int	i;

	i = -1;
	while (i++ < 8)
		chunk_generator(world, i);
}

static void world_copy_from_chunk(t_world *world)
{
    int chunk_yx[2];
    int world_iterator;

    chunk_yx[0] = -1;
    chunk_yx[1] = -1;
    world_iterator = -1;
    while (world_iterator++ < 8)
    {
        while (chunk_yx[0]++ < world->height - 1)
        {
            while (chunk_yx[1]++ < world->width - 1) {
                world->world[world_iterator][chunk_yx[0]][chunk_yx[1]] = world->chunk[chunk_yx[0]][chunk_yx[1]];
            }
            chunk_yx[1] = -1;
        }
        chunk_yx[0] = -1;
    }
}

static t_biome **world_get_biomes(int biome_number, ...)
{
    t_biome **biomes;
    va_list va_biomes;

    va_start(va_biomes, biome_number);
    biomes = malloc(sizeof(t_biome *) * (biome_number + 1));
    biomes[biome_number] = 0;
    while (biome_number-- > 0)
        biomes[biome_number] = va_arg(va_biomes, t_biome *);
    va_end(va_biomes);
    return (biomes);
}

static t_biome biome_creator(int block_number, ...)
{
    t_biome biome;
    va_list va_biome;

    va_start(va_biome, block_number);
    biome.block = malloc(sizeof(t_block) * block_number);
    biome.block_number = block_number;
    while (block_number-- > 0)
		biome.block[block_number] = *get_block(va_arg(va_biome, Block));
    va_end(va_biome);
    return (biome);
}


void	world_loader(t_core *core)
{
	set_biome(biome_creator(6, NETHERRACK, NETHER_WART_BLOCK, OBSIDIAN, CRYING_OBSIDIAN, CRACKED_DEEPSLAT_TILES, DEEPSLATE_COAL_ORE), BIOME_DARK);
	set_biome(biome_creator(1, BACKROOM_YELLOW), BIOME_BACKROOM);

	world_copy_from_chunk(get_world(WORLD_DEFAULT));

	world_creator(get_world(WORLD_NETHER), get_sound(NETHER_AMBIANT_SOUND), 32, 32, 0, core->imgs.skybox_nether, get_block_image(NETHERRACK), HARD, false, true);
	set_world_biomes(WORLD_NETHER, world_get_biomes(1, get_biome(BIOME_DARK)));
    world_generator(get_world(WORLD_NETHER));

	world_creator(get_world(WORLD_BACKROOM), get_sound(BACKROOM_AMBIANT_SOUND), 32, 32, 0, core->imgs.backrooms_ceil, get_block_image(BACKROOM_FLOOR), HARD, false, false);
	set_world_biomes(WORLD_BACKROOM, world_get_biomes(1, get_biome(BIOME_BACKROOM)));
	world_generator(get_world(WORLD_BACKROOM));
}
