/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:25:25 by ngalzand          #+#    #+#             */
/*   Updated: 2023/09/01 11:25:29 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	stack_item(t_core *core, t_slot *src, t_slot *dst, bool *holding)
{
	const int	n = src->items_number + dst->items_number;

	if (src->items_number + dst->items_number > 64)
	{
		change_item_number(core, dst, 64);
		display_item(dst);
		change_item_number(core, src, n % 64);
		display_item(src);
		*holding = true;
		src->bar_mutex = true;
		src->items_number_img->instances[0].z = 14;
		src->item->icon->instances[src->icon_instance].z = 13;
		return ;
	}
	change_item_number(core, dst, n);
	dst->items_number_img->instances[0].z = 12;
	reset_slot(core, src);
	display_item(src);
}

static void	apply_slot(t_core *core, t_slot *slot, bool *holding, int s)
{
	slot->items_number_img->instances[0].z = 12;
	slot->bar_mutex = false;
	*holding = false;
	if (s == -1 || !slot || slot->slot_id == get_slot(core, s)->slot_id
		|| get_slot(core, s)->slot_id == 46)
		display_item(slot);
	else if (slot->item->name != HAND && get_slot(core, s)->item->name == HAND)
		set_on_void_slot(core, slot, s);
	else if (slot->item->name == get_slot(core, s)->item->name)
		stack_item(core, slot, get_slot(core, s), holding);
	else if (slot->item->name != HAND && get_slot(core, s)->item->name != HAND)
	{
		reverse_attributes(slot, get_slot(core, s));
		display_item(get_slot(core, s));
		get_slot(core, s)->bar_mutex = false;
		slot->items_number_img_bar->instances[0].enabled = false;
		slot->item->icon->instances[slot->bar_icon_instance].enabled = false;
		slot->bar_mutex = true;
		slot->items_number_img->instances[0].z = 14;
		slot->item->icon->instances[slot->icon_instance].z = 13;
		*holding = true;
	}
}

void	give_one_to(t_core *core, t_slot *src, t_slot *dst)
{
	if (dst->slot_id == 47)
		return ;
	if (src->item->name == dst->item->name
		&& src->items_number > 1 && dst->items_number < 64)
	{
		change_item_number(core, src, src->items_number - 1);
		src->items_number_img->instances[0].z = 14;
		change_item_number(core, dst, dst->items_number + 1);
		dst->items_number_img->instances[0].z = 12;
	}
	else if (dst->item->name == HAND && src->items_number > 1
		&& dst->slot_id != 46)
	{
		change_item_number(core, src, src->items_number - 1);
		give_item(core, get_item(src->item->name), dst->slot_id, 1);
		display_item(dst);
	}
}

static void	select_action(t_core *core, t_slot **s, bool *holding)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(core->mlx, &x, &y);
	if (mlx_is_mouse_down(core->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		if (s[0] && s[0]->item && s[0]->item->name != HAND)
			give_one_to(core, *s, get_slot(core, detect_pointed_slot(core, x, y)));
	}
	else if (*holding == false)
	{
		if (detect_pointed_slot(core, x, y) == 46)
			craft(core);
		*s = get_slot(core, detect_pointed_slot(core, x, y));
		if (!s[0] || s[0]->item->name == HAND)
			return ;
		*holding = true;
		s[0]->bar_mutex = true;
		s[0]->items_number_img_bar->instances[0].enabled = false;
		s[0]->item->icon->instances[s[0]->icon_instance].z = 13;
		s[0]->items_number_img->instances[0].z = 14;
		s[0]->item->icon->instances[s[0]->bar_icon_instance].enabled = false;
	}
	else if (*holding == true)
		apply_slot(core, *s, holding, detect_pointed_slot(core, x, y));
}

void	inventory_hook(void *params)
{
	t_core			*core;
	static t_slot	*s = 0;
	static bool		holding = false;

	core = (t_core *)params;
	core->player.holding_item = &holding;
	if (!core->player.is_in_inventory)
	{
		holding = false;
		if (s && s->slot_id <= 9 && s->item->name != HAND)
		{
			s->items_number_img_bar->instances[0].enabled = true;
			s->item->icon->instances[s->bar_icon_instance].enabled = true;
		}
		return ;
	}
	if (mlx_is_mouse_down(core->mlx, MLX_MOUSE_BUTTON_LEFT)
		|| mlx_is_mouse_down(core->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		select_action(core, &s, &holding);
		usleep(100000);
	}
	if (s != 0 && holding == true && s->item->name != HAND)
		follow_cursor(core, s);
	crafting_engine(core);
}
