
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

static t_slot	*get_slot(t_core *core, int s)
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
	second->item = save.item;
	second->icon_instance = save.icon_instance;
	second->bar_icon_instance = save.bar_icon_instance;
}

static void	apply_slot(t_core *core, t_slot *slot, int s)
{
	if (slot->item->name != HAND && (s == -1
			|| get_slot(core, s)->item->name != HAND))
		display_item(core, slot);
	else if (slot->item->name != HAND && get_slot(core, s)->item->name == HAND)
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
		if (slot->item->icon->instances
			[slot->bar_icon_instance].enabled == true)
			slot->item->icon->instances
			[slot->bar_icon_instance].enabled = false;
		reverse_attributes(slot, get_slot(core, s));
	}
}

void	inventory_hook(void *params)
{
	int				x;
	int				y;
	t_core			*core;
	static t_slot	*s = 0;
	static bool		holding = false;

	core = (t_core *)params;
	mlx_get_mouse_pos(core->mlx, &x, &y);
	if (mlx_is_mouse_down(core->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (holding == false)
		{
			holding = true;
			s = get_slot(core, detect_pointed_slot(x, y));
		}
		if (s != 0 && holding == true && s->item->name != HAND)
		{
			mlx_get_mouse_pos(core->mlx, &x, &y);
			s->item->icon->instances[s->icon_instance].x = x - 15;
			s->item->icon->instances[s->icon_instance].y = y - 15;
		}
	}
	else
	{
		if (s != 0)
			apply_slot(core, s, detect_pointed_slot(x, y));
		holding = false;
		s = 0;
	}
}
