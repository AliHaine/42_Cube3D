#include "../../includes/includes.h"

char	get_backward_char(t_player *player, char **map)
{
	return (map[(int)((player->player_pos_yx[1]
				- (sinf(player->playerangle) * player->move_speed)) / 64)]
				[(int)((player->player_pos_yx[0] - (cosf(player->playerangle)
													* player->move_speed)) / 64)]);
}

char	get_forward_char(t_player *player, char **map)
{
	return (map[(int)((player->player_pos_yx[1] + (sinf(player->playerangle)
												   * player->move_speed)) / 64)][(int)((player->player_pos_yx[0] +
																						(cosf(player->playerangle) * player->move_speed)) / 64)]);
}

char	get_right_char(t_player *player, char **map)
{
	return (map[(int)((player->player_pos_yx[1]
				- (sinf(player->playerangle - PI / 2)
					* player->move_speed)) / 64)]
				[(int)((player->player_pos_yx[0] - (cosf(player->playerangle
														 - PI / 2) * player->move_speed)) / 64)]);
}

char	get_left_char(t_player *player, char **map)
{
	return (map[(int)(player->player_pos_yx[1]
			+ (sinf(player->playerangle - PI / 2) * player->move_speed)) / 64]
			[(int)((player->player_pos_yx[0] + (cosf(player->playerangle - PI / 2)
												* player->move_speed)) / 64)]);
}

bool	is_player_running(t_player *player)
{
	if (player->move_speed > MOVE_SPEED)
		return (true);
	return (false);
}
