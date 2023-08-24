#include "../../includes/includes.h"

void	teleport_player(t_player *player)
{
	int		x;
	int		y;
	t_world	*world;

	world = get_world_active();
	while (1)
	{
		x = get_rand_num(world->width - 1, 1);
		y = get_rand_num(world->height - 1, 1);
		if (world->world[4][y][x] == '0') {
			break;
		}
	}
	set_player(x, y, player, 0);
}
