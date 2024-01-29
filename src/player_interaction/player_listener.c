/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:08:55 by ayagmur           #+#    #+#             */
/*   Updated: 2024/01/29 12:41:07 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	energy_listener(t_player *player, Difficulty difficulty)
{
	if (is_player_running(player))
	{
		if (!player_have_energy(player->energy))
			player->move_speed = MOVE_SPEED;
		return (take_energy(player, 1 + difficulty));
	}
	else
		return (add_energy(player, 1));
}

void	player_listener(void *params)
{
	t_core	*core;
	t_world	*world;

	core = (t_core *) params;
    if (core->player.is_moving && !core->player.is_in_inventory)
        moving_handling_item(core);
	world = get_world_active();
	if (energy_listener(&core->player, world->difficulty))
		draw_energy_bar(core->imgs.engbar, core->player.energy);
	if (core->player.is_building)
		player_build(&core->player, core->options);
	if (core->player.is_moving)
	{
		if (core->player.is_running)
		{
			play_sound_alt(get_sound(PLAYER_WALK_SOUND), false, false);
			play_sound_alt(get_sound(PLAYER_RUN_SOUND), true, false);
		}
		else
			play_sound_alt(get_sound(PLAYER_WALK_SOUND), true, false);
	}
	else
	{
		play_sound_alt(get_sound(PLAYER_RUN_SOUND), false, false);
		play_sound_alt(get_sound(PLAYER_WALK_SOUND), false, false);
	}
	portal_listener(&core->player, world);
}
