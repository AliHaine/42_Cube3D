
#include "../../includes/includes.h"

static void	inventory_engine(void *params)
{
	t_core	*core;

	core = (t_core *)params;
}

static void	init_item(t_core *core, t_slot *slot)
{
	if (slot->slot_id >= 0 && slot->slot_id <= 9)
	{
		mlx_image_to_window(core->mlx, slot->item->icon, 405 + (55 * (slot->slot_id - 1)), 495);
		slot->item->icon->instances[1].enabled = false;
	}
}

static void	display_item(t_core *core, t_slot *slot)
{
	if (slot->item->icon)
	{
		if (slot->slot_id >= 0 && slot->slot_id <= 9)
			slot->item->icon->instances[1].enabled = true;
		else
			slot->item->icon->instances[0].enabled = true;
	}
}

static void	erase_items(t_core *core)
{
	t_slot	*act;

	act = core->player.slot;
	while (act->prev)
		act = act->prev;
	while (act->next)
	{
		if (act->slot_id >= 0 && act->slot_id <= 9)
			act->item->icon->instances[1].enabled = false;
		else
			act->item->icon->instances[0].enabled = false;
		act = act->next;
	}
}

static void	open_inv(t_core *core)
{
	t_slot		*act;
	static bool	is_init = false;

	if (!core->player.slot)
		return ;
	act = core->player.slot;
	while (act->prev)
		act = act->prev;
	while (act->next)
	{
		if (is_init == false && act->item)
			init_item(core, act);
		if (act->item)
			display_item(core, act);
		act = act->next;
	}
	is_init = true;
}

void	inventory(t_core *core)
{
	if (core->player.is_in_inventory == false)
	{
		if (core->imgs.inventory_gui->width != core->screen_size[0]
			|| core->imgs.inventory_gui->height != core->screen_size[1])
			mlx_resize_image(core->imgs.inventory_gui, core->screen_size[0],
				core->screen_size[1]);
		core->imgs.inventory_gui->enabled = true;
		core->player.is_in_inventory = true;
		mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.enemy));
		open_inv(core);
		mlx_loop_hook(core->mlx, &inventory_engine, core);
	}
	else
	{
		erase_items(core);
		mlx_close_hook(core->mlx, &inventory_engine, core);
		mlx_set_mouse_pos(core->mlx, core->screen_size[0] / 2,
			core->screen_size[1] / 2);
		core->imgs.inventory_gui->enabled = false;
		core->player.is_in_inventory = false;
		mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.trans));
	}
}
