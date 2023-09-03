/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:18:53 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/16 14:18:59 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	mouse_left_action_zero(t_player *player)
{
	player->is_building = false;
}

static void	mouse_left_action_one(t_player *player)
{
	if (!player_have_enough_energy(player, 20))
		return ;
	take_energy(player, 8 * get_world_active()->difficulty);
	player->slot->item->animation.is_playing = true;
	player->is_building = true;
}

static void	mouse_right_action(t_player *player)
{
	if (player->slot->item->name == LIGHTER && get_hit_char(player) == get_block(OBSIDIAN)->block_char)
		portal_open(player);
}

void	mouse(enum mouse_key key, enum action action, enum modifier_key mkey, void *param)
{
	t_core			*core;

	(void) mkey;
	core = (t_core *)param;
	if (core->player.is_in_inventory)
		return ;
	if (key == 0)
	{
		if (action == 0)
			mouse_left_action_zero(&core->player);
		else
			mouse_left_action_one(&core->player);
	}
	else
		mouse_right_action(&core->player);
}
