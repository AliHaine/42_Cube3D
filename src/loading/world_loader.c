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

static bool world_malloc(int height, int width, char ***map)
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

bool world_creator(t_world *world, uint32_t anbiant_sound, int height, int width, const uint32_t bt_color[2], mlx_image_t *ceil, mlx_image_t *floor, Difficulty difficulty, bool is_active)
{
    int i;

    i = 0;
	world->biome = 0;
	world->abiant_sound = anbiant_sound;
	world->height = height;
	world->width = width;
	world->bt_color[0] = 0;
	world->bt_color[1] = 0;
	world->ceil = ceil;
	world->floor = floor;
	world->difficulty = difficulty;
	world->world = malloc(sizeof(char **) * 9);
	world->is_active = is_active;
	world_malloc(height, width, &world->chunk);
    while (i < 9)
	    world_malloc(height * 3, width * 3, &world->world[i++]);
    return (true);
}

static void world_generator(t_world *world) {
    int y;
	int x;

    y = 0;
	x = 0;
    while (y < world->height) {
		while (x < world->width) {
			world->chunk[y][x++] = get_rand_num(2) + '0';
		}
		x = 0;
		y++;
    }

	y = 0;
	x = 0;
	while (y < world->height) {
		while (x < world->width)
			printf("%c", world->chunk[y][x++]);
		printf("\n");
		x = 0;
		y++;
	}
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
	print_entire_world();
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
    biome.block = malloc(sizeof(t_block) * block_number + 1);
    biome.block_number = block_number;
    while (block_number-- > 0)
        biome.block[block_number] = va_arg(va_biome, t_block);
    va_end(va_biome);
    return (biome);
}


void	world_loader(t_core *core)
{
	core->biome[1] = biome_creator(6, *core->blocks[NETHERRACK], *core->blocks[NETHER_WART_BLOCK], *core->blocks[OBSIDIAN], *core->blocks[CRYING_OBSIDIAN], *core->blocks[CRACKED_DEEPSLAT_TILES], *core->blocks[DEEPSLATE_COAL_ORE]);
	world_copy_from_chunk(get_world(0));
	world_creator(get_world(1), core->sounds.ambiant, 32, 32, 0, core->imgs.skybox_nether, core->blocks[NETHERRACK]->image, HARD, false);
	get_world(1)->biome = world_get_biomes(1, &core->biome[1]);
    world_generator(get_world(1));
    world_copy_from_chunk(get_world(1));
}