#include "../../includes/includes.h"

void	set_player(int x, int y, t_player *player, float angle)
{
	t_world *world;

	world = get_world_active();
	player->player_pos_xy[0] = ((x + world->width) * 64) + 32;
	player->player_pos_xy[1] = ((y + world->height) * 64) + 32;
	player->player_cell_xy[0] = x;
	player->player_cell_xy[0] = y;
	player->player_coords_xy[0] = (y  * 64) + 32;
	player->player_coords_xy[1] = (x  * 64) + 32;
	player->playerangle = angle;
}