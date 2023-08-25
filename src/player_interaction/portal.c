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

//todo better write
static bool	is_player_under_portal(const int player_cell_xy[2], const t_world *world)
{
	if (world->world[4][player_cell_xy[1] % world->height][player_cell_xy[0] % world->width] == 'Z'
		|| world->world[4][player_cell_xy[1] % world->height][player_cell_xy[0] % world->width] == '(')
		return (true);
	return (false);
}

//todo
void	portal_listener(t_player *player, t_world *world)
{
	if (!is_player_under_portal(player->player_cell_xy, world))
		return ;
	change_active_world(get_world_from_portal(world->world[4][player->player_cell_xy[1] % world->height][player->player_cell_xy[0] % world->width]));
	teleport_player(player);
}