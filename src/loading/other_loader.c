#include "../../includes/includes.h"

void	mlx_hook_loader(t_core *core)
{
	mlx_loop_hook(core->mlx, &display, core);
	mlx_loop_hook(core->mlx, &inputs, core);
	mlx_loop_hook(core->mlx, &mouse_listener, core);
	mlx_loop_hook(core->mlx, &player_listener, core);
	mlx_key_hook(core->mlx, &inputs_hook, core);
	mlx_resize_hook(core->mlx, &resize_hook, core);
	mlx_mouse_hook(core->mlx, &mouse, core);
	mlx_scroll_hook(core->mlx, &scroll_hook, core);
	mlx_loop_hook(core->mlx, &inventory_hook, core);
	mlx_loop(core->mlx);
}
