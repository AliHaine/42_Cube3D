#include "../../includes/includes.h"

bool	is_player_death(int player_health)
{
	if (player_health < 0)
		return (true);
	return (false);
}

static bool	is_player_full_life(int player_health)
{
	if (player_health == 2)
		return (true);
	return (false);
}

bool    hit_player(t_player *player, t_imgs *imgs)
{
	if (is_player_death(player->health))
		return (true);
	player->health--;
	take_energy(player, 15);
	imgs->hearth[1]->instances[player->health + 1].enabled = false;
	return (false);
}

void	heal_player(t_player *player, t_imgs *imgs)
{
	if (is_player_full_life(player->health))
		return ;
	player->health++;
	imgs->hearth[1]->instances[player->health].enabled = true;
}