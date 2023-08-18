#include "../../includes/includes.h"

void	set_char_at_forward(char c, t_player *player, t_map *map)
{
	map->world[4][(int)((player->player_pos_xy[1] + (sinf(player->playerangle)
	* player->move_speed)) / 64) % map->height][(int)((player->player_pos_xy[0] +
	(cosf(player->playerangle) * player->move_speed)) / 64) % map->width] = c;
}