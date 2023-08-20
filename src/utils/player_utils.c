#include "../../includes/includes.h"

void	set_player(int x, int y, t_player *player, t_map *map, float angle)
{
	player->player_pos_xy[0] = ((x + map->width) * 64) + 32;
	player->player_pos_xy[1] = ((y + map->height) * 64) + 32;
	player->player_cell_xy[0] = x;
	player->player_cell_xy[0] = y;
	player->player_coords_xy[0] = (y  * 64) + 32;
	player->player_coords_xy[1] = (x  * 64) + 32;
	player->playerangle = angle;
}