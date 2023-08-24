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
	t_world *world;

	core = (t_core *) params;
	world = get_world_active();
	//check with death_listener if player is death and draw death screen
	if  (energy_listener(&core->player, world->difficulty))
		draw_energy_bar(core->imgs.engbar, core->player.energy);
	if (core->player.is_moving) {
		if (core->player.is_running) {
			play_sound_alt(core->sounds.player_walk, false, false, &core->options);
			play_sound_alt(core->sounds.player_run, true, false, &core->options);
		}
		else
			play_sound_alt(core->sounds.player_walk, true, false, &core->options);
	}
	else {
		play_sound_alt(core->sounds.player_run, false, false, &core->options);
		play_sound_alt(core->sounds.player_walk, false, false, &core->options);
	}
	portal_listener(&core->player, world, &core->sounds);
}
