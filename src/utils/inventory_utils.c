#include "../../includes/includes.h"

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

static int	detected_pointed_slot_bis(int x, int y,
										float resizex, float resizey)
{
	if (x >= (int)(465 * resizex) && x <= (int)(620 * resizex))
	{
		if (y >= (int)(225 * resizey) && y <= (int)(270 * resizey))
			return ((int)(((float)x - 465 * resizex) / (53.3f * resizex) + 37));
		else if (y >= (int)(170 * resizey) && y <= (int)(218 * resizey))
			return ((int)(((float)x - 465 * resizex) / (53.3f * resizex) + 40));
		else if (y >= (int)(115 * resizey) && y <= (int)(162 * resizey))
			return ((int)(((float)x - 465 * resizex) / (53.3f * resizex) + 43));
	}
	else if (x >= (int)(735 * resizex) && x <= (int)(805 * resizex)
		&& y >= (int)(160 * resizey) && y <= (int)(230 * resizey))
		return (46);
	return (-1);
}

int	detect_pointed_slot(t_core *core, int x, int y)
{
	const float	resizex = (float)core->screen_size[0] / 1280.f;
	const float	resizey = (float)core->screen_size[1] / 720.f;

	if (x < (int)(400 * resizex) || x > (int)(875 * resizex))
		return (-1);
	if (y >= (int)(490 * resizey) && y <= (int)(535 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 1));
	else if (y >= (int)(425 * resizey) && y <= (int)(470 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 10));
	else if (y >= (int)(370 * resizey) && y <= (int)(415 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 19));
	else if (y >= (int)(320 * resizey) && y <= (int)(360 * resizey))
		return ((int)(((float)x - 400 * resizex) / (53.3f * resizex) + 28));
	return (detected_pointed_slot_bis(x, y, resizex, resizey));
}

void static	set_pos_by_id_bis(t_slot *slot, int id)
{
	if (id >= 1 && id <= 36)
		slot->item->icon->instances[slot->icon_instance].x
			= 405 + (54 * ((id - 1) % 9));
	else if (id >= 37 && id <= 45)
		slot->item->icon->instances[slot->icon_instance].x
			= 470 + (54 * ((id - 1) % 3));
	else if (id == 46)
		slot->item->icon->instances[slot->icon_instance].x = 750;
	slot->items_number_img->instances[0].x
		= slot->item->icon->instances[slot->icon_instance].x + 23;
	slot->items_number_img->instances[0].y
		= slot->item->icon->instances[slot->icon_instance].y + 25;
}

void	set_pos_by_id(t_slot *slot, int id)
{
	if (id >= 1 && id <= 9)
		slot->item->icon->instances[slot->icon_instance].y = 495;
	else if (id >= 10 && id <= 18)
		slot->item->icon->instances[slot->icon_instance].y = 430;
	else if (id >= 19 && id <= 27)
		slot->item->icon->instances[slot->icon_instance].y = 375;
	else if (id >= 28 && id <= 36)
		slot->item->icon->instances[slot->icon_instance].y = 325;
	else if (id >= 37 && id <= 39)
		slot->item->icon->instances[slot->icon_instance].y = 230;
	else if (id >= 40 && id <= 42)
		slot->item->icon->instances[slot->icon_instance].y = 177;
	else if (id >= 43 && id <= 45)
		slot->item->icon->instances[slot->icon_instance].y = 123;
	else if (id == 46)
		slot->item->icon->instances[slot->icon_instance].y = 176;
	set_pos_by_id_bis(slot, id);
}
