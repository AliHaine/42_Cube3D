/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_dynamic_generator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:40:18 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/27 14:40:20 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/concepts/world.h"

static void	world_place_map(t_world *world, int chunk_num)
{
	int	i;
	int	incrementation;
	int	chunk;
	int	mul;

	i = -1;
	mul = 1;
	chunk = 0;
	if (chunk_num == 1)
	{
		chunk = 6;
		incrementation = -3;
	}
	else if (chunk_num == 7)
		incrementation = 3;
	else if (chunk_num == 3)
	{
		mul = 3;
		chunk = 2;
		incrementation = -1;
	}
	else
	{
		mul = 3;
		incrementation = 1;
	}
	while (i++ < 2)
		copy_tab(world->world[(chunk + i * mul) + incrementation], world->world[chunk + i * mul], world->height, world->width);
	i = -1;
	chunk += incrementation;
	while (i++ < 2)
		copy_tab(world->world[(chunk + i * mul) + incrementation], world->world[chunk + i * mul], world->height, world->width);
}

static void	side_generator(t_world *world, int chunk_num)
{
	int	i;
	int	chunk;
	int	incrementation;

	i = -1;
	chunk = 0;
	if (chunk_num == 3 || chunk_num == 5)
	{
		incrementation = 3;
		if (chunk_num == 5)
			chunk = 2;
	}
	else
	{
		incrementation = 1;
		if (chunk_num == 7)
			chunk = 6;
	}
	while (i++ < 2)
		chunk_generator(world, chunk + (incrementation * i));
}

static void	replace_player_on_world(t_player *player, int num)
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

static int	get_chunk_from_corner(int iterator, int chunk_num)
{
	if (iterator == 1)
	{
		if (chunk_num == 0 || chunk_num == 2)
			return (1);
		else
			return (7);
	}
	else
	{
		if (chunk_num == 0 || chunk_num == 6)
			return (3);
		else if (chunk_num == 2 || chunk_num == 8)
			return (5);
	}
	return (chunk_num);
}

bool	world_dynamic_generator(t_player *player)
{
	int		start_chunk;
	int		chunk;
	t_world	*world;
	int		iterator;

	world = get_world_active();
	start_chunk = get_chunk_from_pos(player->player_cell_xy[0], player->player_cell_xy[1]);
	iterator = 1;
	if (is_chunk_on_corner(start_chunk))
		iterator = 2;
	while (iterator-- > 0)
	{
		chunk = get_chunk_from_corner(iterator, start_chunk);
		world_place_map(world, chunk);
		side_generator(world, chunk);
		replace_player_on_world(player, chunk);
	}
	return (0);
}
