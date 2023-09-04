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

#include "../../../includes/concepts/portal.h"

//todo better write
static bool	is_player_under_portal(const int player_cell_xy[2], const t_world *world)
{
	if (!get_portal_from_char(world->world[4][player_cell_xy[1] % world->height][player_cell_xy[0] % world->width]))
		return (false);
	return (true);
}

//todo
void	portal_listener(t_player *player, t_world *world)
{
	if (!is_player_under_portal(player->player_cell_xy, world))
		return ;
	change_active_world(get_portal_from_char(world->world[4][player->player_cell_xy[1] % world->height][player->player_cell_xy[0] % world->width])->world_destination);
	teleport_player(player);
}

void	portal_open(t_player *player)
{
	set_char_at_forward(get_block(NETHERPORTAL)->block_char, player);
}

void	portal_close(t_player *player)
{
	set_char_at_forward(get_block(CRYING_OBSIDIAN)->block_char, player);
}
