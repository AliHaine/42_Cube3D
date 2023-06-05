#include "../../includes/includes.h"

bool	mouse(mlx_t *mlx, t_player *player)
{
	static int	mouse_posx = 999999;
	int			x;
	int			y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (mouse_posx == 999999)
		mouse_posx = x;
	if (x != mouse_posx && x >= 0) {
		if (x > mouse_posx)
			move_rotate(player, 1);
		else
			move_rotate(player, 0);
		mouse_posx = x;
	}
	return (true);
}