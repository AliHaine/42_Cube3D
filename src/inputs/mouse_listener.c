#include "../../includes/includes.h"

void	mouse_listener(void *params)
{
	t_core			*core;
	static double	time = -2;

	core = (t_core *)params;
	if (!mlx_is_mouse_down(core->mlx, MLX_MOUSE_BUTTON_LEFT))
		return ;
	if (time - mlx_get_time() >= -0.15)
		return ;
	time = mlx_get_time();
	player_build(&core->player, core->options);
}