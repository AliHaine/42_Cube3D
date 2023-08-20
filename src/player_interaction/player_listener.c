/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:08:55 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/20 01:08:59 by ayagmur          ###   ########.fr       */
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
	t_core *core;

	core = (t_core *) params;
	//check with death_listener if player is death and draw death screen
	if  (energy_listener(&core->player, core->maps[0].difficulty))
		draw_energy_bar(core->imgs.engbar, core->player.energy);
	if (core->player.is_moving) {
		if (core->player.is_running) {
			play_sound_alt(core->sounds.player_walk, false, false);
			play_sound_alt(core->sounds.player_run, true, false);
		}
		else
			play_sound_alt(core->sounds.player_walk, true, false);
	}
	else {
		play_sound_alt(core->sounds.player_run, false, false);
		play_sound_alt(core->sounds.player_walk, false, false);
	}
	portal_listener(&core->player, core->maps, &core->sounds);
}
