
#include "../../includes/includes.h"

void	display_item(t_core *core, t_slot *slot)
{
	if (slot && slot->item && slot->item->icon && slot->item->name != HAND)
	{
        if (slot->slot_id >= 0 && slot->slot_id < 10)
		    slot->item->icon->instances[slot->icon_instance].y = 495;
        else if (slot->slot_id >= 10 && slot->slot_id < 20)
            slot->item->icon->instances[slot->icon_instance].y = 430;
        else if (slot->slot_id >= 20 && slot->slot_id < 30)
            slot->item->icon->instances[slot->icon_instance].y = 375;
        else if (slot->slot_id >= 30 && slot->slot_id < 40)
            slot->item->icon->instances[slot->icon_instance].y = 325;
		slot->item->icon->instances[slot->icon_instance].x
				= 405 + (54 * ((slot->slot_id - 1) % 9));
		slot->item->icon->instances[slot->icon_instance].enabled = true;
		if (slot->items_number > 0)
		{
			slot->items_number_img->instances[0].x = slot->item->icon->instances[slot->icon_instance].x + 23;
			slot->items_number_img->instances[0].y = slot->item->icon->instances[slot->icon_instance].y + 25;
			slot->items_number_img->instances[0].enabled = true;
			slot->items_number_img->instances[0].z = 8;
		}
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
		if (act->bar_icon_instance != -1)
        {
            act->item->icon->instances[act->icon_instance].enabled = false;
            act->items_number_img->instances[0].enabled = false;
        }
		act = act->next;
	}
}

static void	open_inv(t_core *core)
{
	t_slot		*act;
	static bool	is_init = false;

	act = core->player.slot;
	while (act->prev)
		act = act->prev;
	while (act->next)
	{
		if (act->icon_instance != -1)
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
		core->imgs.inventory_gui->instances->z = 7;
		core->player.is_in_inventory = true;
		mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.cursor));
		open_inv(core);
	}
	else
	{
		erase_items(core);
		mlx_set_mouse_pos(core->mlx, core->screen_size[0] / 2,
			core->screen_size[1] / 2);
		core->imgs.inventory_gui->enabled = false;
		core->player.is_in_inventory = false;
		mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.trans));
	}
}
