#include "../../includes/includes.h"


void    resize_hook(int height, int width, void *params)
{
    *((int*)params) = height;
    *((int*)params + 1) = width;
}

void	mouse(mlx_t *mlx, t_player *player, const int screen_size[2])
{
	int			x;
	int			y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (x > screen_size[0] / 2)
		move_rotate(player, 1);
	else if (x < screen_size[0] / 2)
		move_rotate(player, 0);
	mlx_set_mouse_pos(mlx, (screen_size[0] / 2), (screen_size[1] / 2));
}