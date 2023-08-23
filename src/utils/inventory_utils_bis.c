#include "../../includes/includes.h"

void	reset_slot(t_core *core, t_slot *slot)
{
	if (slot->icon_instance != -1)
		slot->item->icon->instances[slot->icon_instance].enabled = false;
	if (slot->bar_icon_instance != -1)
		slot->item->icon->instances[slot->bar_icon_instance].enabled = false;
	slot->item = get_item(HAND);
	slot->items_number = 1;
	slot->items_number_img->instances[0].enabled = false;
	slot->items_number_img_bar->instances[0].enabled = false;
	slot->icon_instance = -1;
	slot->bar_icon_instance = -1;
	slot->bar_icon_instance = -1;
}

void	change_item_number(t_core *core, t_slot *src, short n)
{
	if (src->icon_instance == -1)
		return ;
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
