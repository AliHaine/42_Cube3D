/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:52:07 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 18:52:08 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	set_player(int x, int y, t_player *player, float angle)
{
	t_world	*world;

	world = get_world_active();
	player->player_pos_xy[0] = ((x + world->width) * 64) + 32;
	player->player_pos_xy[1] = ((y + world->height) * 64) + 32;
	player->player_cell_xy[0] = x + world->width;
	player->player_cell_xy[1] = y + world->height;
	player->playerangle = angle;
}

char	get_hit_char(t_player *player)
{
	int		x;
	int		y;
	t_world	*world;

	world = get_world_active();
	x = player->player_pos_xy[0] + cosf(player->playerangle) * 55;
	y = player->player_pos_xy[1] + sinf(player->playerangle) * 55;
	return (world->world[get_chunk_from_pos(x / 64, y / 64)][(y / 64) % world->height][(x / 64) % world->width]);
}
