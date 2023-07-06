
#include "../../includes/includes.h"

static int	detect_pointed_slot(int x, int y)
{
	static float	calc1 = 475.f / 9.f;
	static float	calc2 = 400.f / (475.f / 9.f);

	if (x < 400 || x > 875)
		return (-1);
	else if (y >= 490 && y <= 535)
		return ((int)ceilf(((float)x / calc1) - calc2));
	else if (y >= 425 && y <= 470)
		return ((int)ceilf(((float)x / calc1) - calc2) + 9);
	else if (y >= 370 && y <= 415)
		return ((int)ceilf(((float)x / calc1) - calc2) + 18);
	else if (y >= 320 && y <= 360)
		return ((int)ceilf(((float)x / calc1) - calc2) + 27);
	return (-1);
}

t_slot	*get_slot(t_core *core, int s)
{
	t_slot	*act;

	act = core->player.slot;
	while (act->prev && act->slot_id != s)
		act = act->prev;
	while (act->next && act->slot_id != s)
		act = act->next;
	return (act);
}

static void	reverse_attributes(t_slot *first, t_slot *second)
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

static void	set_on_void_slot(t_core *core, t_slot *slot, int s)
{
	if (s >= 0 && s < 10)
		slot->item->icon->instances[slot->icon_instance].y = 495;
	else if (s >= 10 && s < 20)
		slot->item->icon->instances[slot->icon_instance].y = 430;
	else if (s >= 20 && s < 30)
		slot->item->icon->instances[slot->icon_instance].y = 375;
	else if (s >= 30 && s < 40)
		slot->item->icon->instances[slot->icon_instance].y = 325;
	slot->item->icon->instances[slot->icon_instance].x
		= 405 + (54 * ((s - 1) % 9));
	slot->items_number_img->instances[0].x
		= slot->item->icon->instances[slot->icon_instance].x + 23;
	slot->items_number_img->instances[0].y
		= slot->item->icon->instances[slot->icon_instance].y + 25;
	if (slot->item->icon->instances
		[slot->bar_icon_instance].enabled == true)
		slot->item->icon->instances
		[slot->bar_icon_instance].enabled = false;
	reverse_attributes(slot, get_slot(core, s));
}

static void	apply_slot(t_core *core, t_slot *slot, bool *holding, int s)
{
	slot->items_number_img->instances[0].z = 8;
	if (s == -1 || !slot || slot->slot_id == get_slot(core, s)->slot_id)
	{
		display_item(core, slot);
		slot->bar_mutex = false;
		*holding = false;
	}
	else if (slot->item->name != HAND && get_slot(core, s)->item->name != HAND)
	{
		reverse_attributes(slot, get_slot(core, s));
		slot->items_number_img->instances[0].z = 10;
		display_item(core, get_slot(core, s));
		get_slot(core, s)->bar_mutex = false;
		slot->items_number_img_bar->instances[0].enabled = false;
		slot->item->icon->instances[slot->bar_icon_instance].enabled = false;
		slot->bar_mutex = true;
		*holding = true;
	}
	else if (slot->item->name != HAND && get_slot(core, s)->item->name == HAND)
	{
		slot->bar_mutex = false;
		set_on_void_slot(core, slot, s);
		*holding  = false;
	}
}

static void	follow_cursor(t_core *core, t_slot *s)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(core->mlx, &x, &y);
	s->item->icon->instances[s->icon_instance].x = x - 15;
	s->item->icon->instances[s->icon_instance].y = y - 15;
	s->items_number_img->instances[0].x = x + 8;
	s->items_number_img->instances[0].y = y + 10;
}

void	copy_slot(t_slot *src, t_slot *dst)
{

}

void	give_one_to(t_slot *src, t_slot *dst)
{

}

static void	select_action(t_core *core, t_slot **s, bool *holding)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(core->mlx, &x, &y);
	if (*holding == false)
	{
		*s = get_slot(core, detect_pointed_slot(x, y));
		if (!s[0] || s[0]->item->name == HAND)
			return ;
		*holding = true;
		s[0]->bar_mutex = true;
		s[0]->items_number_img_bar->instances[0].enabled = false;
		s[0]->items_number_img->instances[0].z = 10;
		s[0]->item->icon->instances[s[0]->bar_icon_instance].enabled = false;
	}
	else if (*holding == true)
		apply_slot(core, *s, holding, detect_pointed_slot(x, y));
}

void	inventory_hook(void *params)
{
	t_core			*core;
	static t_slot	*s = 0;
	static bool		holding = false;

	core = (t_core *)params;
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
}
