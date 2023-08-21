/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:26:14 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/17 22:26:17 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	get_chunk_from_pos(int x, int y)
{
	int cell;
	int	line;
	t_world	*world;

	cell = -1;
	line = -1;
	world = get_active_world();
	if (y > (world->height * 3) || x > (world->width * 3))
		return (-1);
	while (line++ < 2)
	{
		if (y < (world->height * (line + 1)))
		{
			while (cell++ < 2)
				if (x < (world->width * (cell + 1))) {
					if (cell + (line * 3) == 9) {
						printf("error %d %d %d %d\n", x, y, cell, line);
						return (cell + line);
					}
					return (cell + (line * 3));
				}
		}
	}
	return (0);
}

bool    is_player_chunk_change(t_player *player, t_world *world)
{
	if (player->player_cell_xy[0] >= world->width && player->player_cell_xy[0] <= ((world->width * 2) - 1)
		&& player->player_cell_xy[1] >= world->height && player->player_cell_xy[1] <= ((world->height * 2) - 1))
        return (false);
    return (true);
}

void	set_side_from_int(int chunk_incrementation[2], int chunk_num)
{
	printf("%d num\n", chunk_num);
	if (chunk_num == 3 || chunk_num == 5)
	{
		chunk_incrementation[0] = 0;
		chunk_incrementation[1] = 3;
		if (chunk_num == 3)
			chunk_incrementation[0] = 2;
	}
	else
	{
		chunk_incrementation[0] = 0;
		chunk_incrementation[1] = 1;
		if (chunk_num == 1)
			chunk_incrementation[0] = 6;
	}
}

void	chunk_generator(t_world *map, int chunk)
{
	int y;
	int x;
    t_biome *biome;

	y = 0;
	x = 0;
    biome = get_random_biome(map->biome);
	while (y < map->height) {
		while (x < map->width) {
            map->world[chunk][y][x] = '0';
            if (get_rand_num(4) ==0)
            {
                if (biome != NULL)
                    map->world[chunk][y][x] = get_random_block_from_biome(biome).block_char;
                else
                    map->world[chunk][y][x] = '1';
            }
			x++;
		}
		x = 0;
		y++;
	}
}

void	world_place_map(t_world *world, int num)
{
	int i;
	int	incrementation;
	int chunk;
	int mul;

	i = -1;
	mul = 1;
	if (num == 1)
	{
		chunk = 6;
		incrementation = -3;
	}
	else if (num == 7)
	{
		chunk = 0;
		incrementation = 3;
	}
	else if (num == 3)
	{
		mul = 3;
		chunk = 2;
		incrementation = -1;
	}
	else
	{
		mul = 3;
		chunk = 0;
		incrementation = 1;
	}
	while (i++ < 2)
		copy_tab(world->world[(chunk + i * mul) + incrementation], world->world[chunk + i * mul], world->height, world->width);
	i = -1;
	chunk += incrementation;
	while (i++ < 2)
		copy_tab(world->world[(chunk + i * mul) + incrementation], world->world[chunk + i * mul], world->height, world->width);
}

static void	side_generator(t_world *world, int chunk_incrementation[2])
{
	int i;
	int	chunk;

	i = -1;
	if (chunk_incrementation[1] == 3)
	{
		chunk = 0;
		if (chunk_incrementation[0] == 0)
			chunk = 2;
	}
	else
	{
		chunk = 0;
		if (chunk_incrementation[0] == 0)
			chunk = 6;
	}
	while (i++ < 2)
	{
		chunk_generator(world, chunk + (chunk_incrementation[1] * i));
	}

}

static void	player_place_map(t_player *player, int num)
{
	if (num == 1)
		player->player_pos_xy[1] += player->player_pos_xy[1];
	else if (num == 3)
		player->player_pos_xy[0] += player->player_pos_xy[0];
	else if (num == 5)
		player->player_pos_xy[0] -= (player->player_pos_xy[0] / 2);
	else if (num == 7)
		player->player_pos_xy[1] -= (player->player_pos_xy[1] / 2);
}

bool    world_dynamic_generator(t_player *player)
{
	int	chunk;
	int chunk_incrementation[2];
	t_world	*world;

	world = get_active_world();
	chunk = get_chunk_from_pos(player->player_cell_xy[0], player->player_cell_xy[1]);
	set_side_from_int(chunk_incrementation, chunk);
	world_place_map(world, chunk);
	side_generator(world, chunk_incrementation);
	print_entire_world();
	player_place_map(player, chunk);
	return (0);
}

t_world	*get_active_world()
{
	int	i;

	i = 2;
	while (i-- >= 0)
		if (get_world(i)->is_active)
			return (get_world(i));
	return (0);
}
