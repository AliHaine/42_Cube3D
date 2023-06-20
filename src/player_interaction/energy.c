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

bool	player_have_energy(short value)
{
	if (value <= 0)
		return (false);
	return (true);
}

bool	player_have_enough_energy(t_player *player, short value)
{
	if (player->energy < value)
		return (false);
	return (true);
}