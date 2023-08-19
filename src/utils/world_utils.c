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

int	get_chunk_from_pos(int x, int y, int m_height, int m_width)
{
	int cell;
	int	line;

	cell = -1;
	line = -1;
	while (line++ < 3)
	{
		if (y < (m_height * (line + 1)))
		{
			while (cell++ < 3)
				if (x < (m_width * (cell + 1))) {
					if (cell + (line * 3) == 9) {
						printf("error %d %d\n", cell, line);
						return (cell + line);
					}
					//printf("cell %d line %d\n", cell, line);
					return (cell + (line * 3));
				}
		}
	}
	return (0);
}

bool    is_player_chunk_change(t_player *player, t_map *map)
{
	if (player->player_cell_xy[0] >= map->width && player->player_cell_xy[0] <= ((map->width * 2) - 1)
		&& player->player_cell_xy[1] >= map->height && player->player_cell_xy[1] <= ((map->height * 2) - 1))
        return (false);
    return (true);
}

void	set_side_from_int(int chunk_incrementation[2], int num)
{
	printf("%d num\n", num);
	if (num == 3 || num == 5)
	{
		chunk_incrementation[0] = 0;
		chunk_incrementation[1] = 3;
		if (num == 3)
			chunk_incrementation[0] = 2;
	}
	else
	{
		chunk_incrementation[0] = 0;
		chunk_incrementation[1] = 1;
		if (num == 1)
			chunk_incrementation[0] = 6;
	}
}

void	chunk_generator(t_map *map, int chunk)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < map->height) {
		while (x < map->width) {
			map->world[chunk][y][x++] = (char)get_rand_num(2) + '0';
		}
		x = 0;
		y++;
	}
}

void	world_place_map(t_map *map, const int chunk_incrementation[2])
{
	int i;
	int	incrementation;
	int chunk;

	i = -1;
	chunk = chunk_incrementation[0];
	if (chunk_incrementation[1] == 1)
		incrementation = 3;
	else
		incrementation = 1;
	while (i++ < 2)
		copy_tab(map->world[(chunk + i) - incrementation], map->world[chunk + i], map->height, map->width);
	i = -1;
	chunk -= incrementation;
	while (i++ < 2) {
		copy_tab(map->world[(chunk + i) - incrementation], map->world[chunk + i], map->height, map->width);
	}
}

static void	side_generator(t_map *map, const int chunk_incrementation[2])
{
	int i;
	int chunk;

	chunk = 0;
	i = -1;
	while (i++ < 2)
	{
		chunk_generator(map, chunk + i);
	}

}

bool    world_dynamic_generator(t_map *map, t_player *player)
{
	int chunk_incrementation[2];

	set_side_from_int(chunk_incrementation, get_chunk_from_pos(player->player_cell_xy[0], player->player_cell_xy[1], map->height, map->width));
	world_place_map(map, chunk_incrementation);
	side_generator(map, chunk_incrementation);
	print_entire_world(map);
	player->player_pos_xy[1] = player->player_pos_xy[1] * 2;
	return (0);
}

int	get_active_world(t_map maps[2])
{
	int	i;

	i = 2;
	while (i-- >= 0)
		if (maps[i].is_active)
			return (i);
	return (0);
}
