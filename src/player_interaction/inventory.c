
#include "../../includes/includes.h"

void	inventory(t_core *core)
{
	if (core->player.is_in_inventory == false)
	{
		if (core->imgs.inventory_gui->width != core->screen_size[0]
			|| core->imgs.inventory_gui->height != core->screen_size[1])
			mlx_resize_image(core->imgs.inventory_gui, core->screen_size[0],
				core->screen_size[1]);
		mlx_image_to_window(core->mlx, core->imgs.inventory_gui, 0, 0);
		core->player.is_in_inventory = true;
        mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.enemy));
	}
	else
	{
		mlx_delete_image(core->mlx, core->imgs.inventory_gui);
		core->player.is_in_inventory = false;
		core->imgs.inventory_gui = mlx_texture_to_image(core->mlx, core->imgs.inventory_gui_texture);
        mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.trans));
	}
}
