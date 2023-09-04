/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:25:10 by ngalzand          #+#    #+#             */
/*   Updated: 2023/09/01 11:25:18 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	display_item(t_core *core, t_slot *slot)
{
	if (slot && slot->item && slot->item->icon && slot->item->name != HAND)
	{
		set_pos_by_id(slot, slot->slot_id);
		slot->item->icon->instances[slot->icon_instance].enabled = true;
		slot->items_number_img->instances[0].enabled = true;
		slot->item->icon->instances[slot->icon_instance].z = 11;
		slot->items_number_img->instances[0].z = 12;
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
		core->imgs.inventory_gui->enabled = true;
		core->imgs.inventory_gui->instances->z = 10;
		core->player.is_in_inventory = true;
		core->player.can_move = false;
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
		core->player.can_move = true;
		mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.trans));
	}
}
