
#include "../../includes/includes.h"

static int	detect_pointed_slot(t_core *core, int x, int y)
{
	float	resizex;
	float	resizey;

	resizex = (float)core->screen_size[0] / 1280.f;
	resizey = (float)core->screen_size[1] / 720.f;
	if (x < (int)(400 * resizex) || x > (int)(875 * resizex))
		return (-1);
	else if (y >= (int)(490 * resizey) && y <= (int)(535 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 1));
	else if (y >= (int)(425 * resizey) && y <= (int)(470 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 10));
	else if (y >= (int)(370 * resizey) && y <= (int)(415 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 19));
	else if (y >= (int)(320 * resizey) && y <= (int)(360 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 28));
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
	if (s >= 1 && s <= 9)
		slot->item->icon->instances[slot->icon_instance].y = 495;
	else if (s >= 10 && s <= 18)
		slot->item->icon->instances[slot->icon_instance].y = 430;
	else if (s >= 19 && s <= 27)
		slot->item->icon->instances[slot->icon_instance].y = 375;
	else if (s >= 28 && s <= 36)
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

void	change_item_number(t_core *core, t_slot *src, short n)
{
	mlx_delete_image(core->mlx, src->items_number_img);
	mlx_delete_image(core->mlx, src->items_number_img_bar);
	src->items_number = n;
	src->items_number_img = mlx_put_string
			(core->mlx, ft_itoa(src->items_number),
			 src->item->icon->instances[src->icon_instance].x + 23,
			 src->item->icon->instances[src->icon_instance].y + 25);
	src->items_number_img_bar = mlx_put_string
			(core->mlx, ft_itoa(src->items_number),
			 src->item->icon->instances[src->bar_icon_instance].x + 23,
			 src->item->icon->instances[src->bar_icon_instance].y + 25);
	if (src->slot_id > 9)
		src->items_number_img_bar->instances[0].enabled = false;
}

void	stack_item(t_core *core, t_slot *src, t_slot *dst, bool *holding)
{
	const int	n = src->items_number + dst->items_number;

	if (src->items_number + dst->items_number > 64)
	{
		change_item_number(core, dst, 64);
		display_item(core, dst);
		change_item_number(core, src, n % 64);
		display_item(core, src);
		*holding = true;
		src->bar_mutex = true;
		return ;
	}
	src->item->icon->instances[src->icon_instance].enabled = false;
	src->item->icon->instances[src->bar_icon_instance].enabled = false;
	change_item_number(core, dst, n);
	src->item = &core->items[HAND];
	src->items_number = 1;
	src->items_number_img->instances[0].enabled = false;
	src->items_number_img_bar->instances[0].enabled = false;
	src->icon_instance = -1;
	src->bar_icon_instance = -1;
	src->bar_icon_instance = -1;
	display_item(core, src);
}

static void	apply_slot(t_core *core, t_slot *slot, bool *holding, int s)
{
	slot->items_number_img->instances[0].z = 9;
	slot->bar_mutex = false;
	*holding = false;
	if (s == -1 || !slot || slot->slot_id == get_slot(core, s)->slot_id)
		display_item(core, slot);
	else if (slot->item->name != HAND && get_slot(core, s)->item->name == HAND)
		set_on_void_slot(core, slot, s);
	else if (slot->item->name == get_slot(core, s)->item->name)
		stack_item(core, slot, get_slot(core, s), holding);
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
}

static void	follow_cursor(t_core *core, t_slot *s)
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

void	give_one_to(t_core *core, t_slot *src, t_slot *dst)
{
	if (dst->slot_id == 37)
		return ;
	if (src->item->name == dst->item->name
		&& src->items_number > 1 && dst->items_number < 64)
	{
		change_item_number(core, src, src->items_number - 1);
		src->items_number_img->instances[0].z = 10;
		change_item_number(core, dst, dst->items_number + 1);
		dst->items_number_img->instances[0].z = 8;
	}
	else if (dst->item->name == HAND && src->items_number > 1)
	{
		change_item_number(core, src, src->items_number - 1);
		give_item(core, &core->items[src->item->name], dst->slot_id, 1);
		display_item(core, dst);
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
		*s = get_slot(core, detect_pointed_slot(core, x, y));
		if (!s[0] || s[0]->item->name == HAND)
			return ;
		*holding = true;
		s[0]->bar_mutex = true;
		s[0]->items_number_img_bar->instances[0].enabled = false;
		s[0]->items_number_img->instances[0].z = 10;
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
