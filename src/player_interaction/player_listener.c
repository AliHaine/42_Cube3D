#include "../../includes/includes.h"

static void	energy_listener(t_player *player)
{
	if (is_player_running(player))
	{
		take_energy(player, 3);
		if (!player_have_energy(player->energy))
			player->move_speed = MOVE_SPEED;
	}
	else
		add_energy(player, 1);
}

void	player_listener(void *params)
{
	t_core *core;

	core = (t_core *) params;
	//check with death_listener if player is death and draw death screen
	energy_listener(&core->player);
	if (core->player.is_moving)
		play_sound_alt(core->sounds.player_walk, true, false);
	else
		play_sound_alt(core->sounds.player_walk, false, false);
}
