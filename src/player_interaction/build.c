#include "../../includes/includes.h"

void	set_char_at_forward(char c, t_player *player, t_map *map)
{
	map->world[get_chunk_from_pos(player->player_cell_xy[0], player->player_cell_xy[1],
    map->height, map->width)][(int)((player->player_pos_xy[1] + (sinf(player->playerangle)
	* player->move_speed)) / 64) % map->height][(int)((player->player_pos_xy[0] +
	(cosf(player->playerangle) * player->move_speed)) / 64) % map->width] = c;
}