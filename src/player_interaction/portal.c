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

static bool	is_player_under_portal(const int player_cell_xy[2], const t_world *world)
{
	if (world->world[4][player_cell_xy[1] % world->height][player_cell_xy[0] % world->width] == 'Z')
		return (true);
	return (false);
}

static void	change_player_world(t_world	*new_world)
{
	get_world_active()->is_active = false;
	new_world->is_active = true;
}

void	portal_listener(t_player *player, t_world *world,t_sounds *sounds)
{
	if (!is_player_under_portal(player->player_cell_xy, world))
		return ;
	change_player_world(get_world(NETHER));
	teleport_player(player);

}