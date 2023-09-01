#include "../../includes/includes.h"

void	set_player(int x, int y, t_player *player, float angle)
{
	t_world *world;

	world = get_world_active();
	player->player_pos_xy[0] = ((x + world->width) * 64) + 32;
	player->player_pos_xy[1] = ((y + world->height) * 64) + 32;
	player->player_cell_xy[0] = x + world->width;
	player->player_cell_xy[1] = y + world->height;
	player->playerangle = angle;
}

char	get_hit_char(t_player *player)
{
	int		x;
	int		y;
	t_world	*world;

	world = get_world_active();
	x = player->player_pos_xy[0] + cosf(player->playerangle) * player->move_speed;
	y = player->player_pos_xy[1] + sinf(player->playerangle) * player->move_speed;
	printf("%f %f\n", player->player_pos_xy[0], player->player_pos_xy[1]);
	printf("%d %d\n", x, y);
	return ('0');
}