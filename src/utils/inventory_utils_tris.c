/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_utils_tris.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:28:57 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 15:28:59 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	reverse_attributes(t_slot *first, t_slot *second)
{
	t_slot	save;

	save = *first;
	first->item = second->item;
	first->icon_instance = second->icon_instance;
	first->bar_icon_instance = second->bar_icon_instance;
	first->items_number_img = second->items_number_img;
	first->items_number = second->items_number;
	first->items_number_img_bar = second->items_number_img_bar;
	first->bar_mutex = second->bar_mutex;
	second->item = save.item;
	second->icon_instance = save.icon_instance;
	second->bar_icon_instance = save.bar_icon_instance;
	second->items_number_img = save.items_number_img;
	second->items_number = save.items_number;
	second->items_number_img_bar = save.items_number_img_bar;
	second->bar_mutex = save.bar_mutex;
	if (second->slot_id > 9)
		second->items_number_img_bar->instances[0].enabled = false;
}

void	follow_cursor(t_core *core, t_slot *s)
{
	int			x;
	int			y;
	const float	resizex = 1280.f / (float)core->screen_size[0];
	const float	resizey = 720.f / (float)core->screen_size[1];

	mlx_get_mouse_pos(core->mlx, &x, &y);
	x = (int)((float)x * resizex);
	y = (int)((float)y * resizey);
	s->item->icon->instances[s->icon_instance].x
		= (int32_t)((float)x - (15 * resizex));
	s->item->icon->instances[s->icon_instance].y
		= (int32_t)((float)y - (15 * resizey));
	s->items_number_img->instances[0].x = (int32_t)((float)x
			+ (8 * ((float)core->screen_size[0] / 1280.f)));
	s->items_number_img->instances[0].y = (int32_t)((float)y
			+ (10 * ((float)core->screen_size[1] / 720.f)));
}

void	set_on_void_slot(t_core *core, t_slot *slot, int s)
{
	set_pos_by_id(slot, s);
	if (slot->item->icon->instances
		[slot->bar_icon_instance].enabled == true)
		slot->item->icon->instances
		[slot->bar_icon_instance].enabled = false;
	slot->items_number_img->instances[0].z = 12;
	slot->item->icon->instances[slot->icon_instance].z = 11;
	reverse_attributes(slot, get_slot(core, s));
}
