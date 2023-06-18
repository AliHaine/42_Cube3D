#include "../../includes/includes.h"

void	take_energy(t_player *player, short value)
{
	if (player->energy - value <= 0)
		player->energy = 0;
	else
		player->energy -= value;
}

void	add_energy(t_player *player, short value)
{
	if (player->energy + value > 100)
		player->energy = 100;
	else
		player->energy += value;
}