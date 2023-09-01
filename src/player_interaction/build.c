#include "../../includes/includes.h"

void	set_char_at_forward(char c, t_player *player, t_world *world)
{
	int	chunk;

	chunk = get_chunk_from_pos(player->player_cell_xy[0],
			(player->player_cell_xy[1]));
	world->world[chunk][(int)((player->player_pos_xy[1]
				+ (sinf(player->playerangle) * player->move_speed))
			/ 64) % world->height][(int)((player->player_pos_xy[0]
				+ (cosf(player->playerangle) * player->move_speed)) / 64)
		% world->width] = c;
}
