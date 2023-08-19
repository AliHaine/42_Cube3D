/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:09:06 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/20 01:09:08 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	is_player_under_portal(const int player_cell_xy[2], const t_map *world)
{
	if (world->world[4][player_cell_xy[1] % world->height][player_cell_xy[0] % world->width] == 'Z')
		return (true);
	return (false);
}

void	portal_listener(t_player *player, t_map maps[2], t_sounds *sounds)
{
	int	x;
	int	y;

	if (!is_player_under_portal(player->player_cell_xy, &maps[get_active_world(maps)]))
		return ;
	x = get_rand_num(maps[1].width - 1);
	y = get_rand_num(maps[1].height - 1);
	maps[0].is_active = false;
	maps[1].is_active = true;
	set_player(x, y, player, &maps[1], 0);

}