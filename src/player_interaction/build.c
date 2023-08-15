#include "../../includes/includes.h"

void	set_char_at_forward(char c, t_player *player, char **map)
{
	map[(int)((player->player_pos_yx[1] + (sinf(player->playerangle)
										   * player->move_speed)) / 64)][(int)((player->player_pos_yx[0] +
																				(cosf(player->playerangle) * player->move_speed)) / 64)] = c;
}