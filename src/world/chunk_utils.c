/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:23:37 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/22 22:23:39 by ayagmur          ###   ########.fr       */
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
	world = get_world_active();
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

//todo si tes deja dans les back
void	chunk_generator(t_world *world, int chunk)
{
	int y;
	int x;
	t_biome *biome;

	y = 0;
	x = 0;
	biome = get_random_biome(world->biome);
	while (y < world->height) {
		while (x < world->width) {
			world->world[chunk][y][x] = '0';
			if (!get_rand_num(4, 1))
			{
				if (!get_rand_num(10000, 1))
				{
					printf("b portal generated at chunk %d x %d y %d\n", chunk, x, y);
					world->world[chunk][y][x] = '(';
				}
				else if (biome != NULL)
					world->world[chunk][y][x] = get_random_block_from_biome(biome).block_char;
				else
					world->world[chunk][y][x] = '1';
			}
			x++;
		}
		x = 0;
		y++;
	}
}

bool	is_chunk_on_corner(int chunk_num)
{
	if (chunk_num == 0 || chunk_num == 2
		|| chunk_num == 6 || chunk_num == 8)
		return (true);
	return (false);
}
