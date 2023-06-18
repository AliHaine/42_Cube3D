#include "../../includes/includes.h"

static void	energy_listener(t_player *player)
{
	if (is_player_running(player))
		take_energy(player, 1);
	else
		add_energy(player, 1);
}

void	player_listener(void *params)
{
	t_core *core;

	core = (t_core *) params;
	//check if player is death and draw death screen
	energy_listener(&core->player);
}
