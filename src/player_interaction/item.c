#include "../../includes/includes.h"

void	give_item(t_core *core, t_item *item, int slot_id, int number)
{
	t_slot	*slot;

	if (slot_id > 46)
		return ;
	slot = core->player.slot;
	while (slot->slot_id != slot_id)
		slot = slot->next;
	slot->item = item;
	slot->bar_icon_instance = mlx_image_to_window(core->mlx, item->icon, SCREEN_WIDTH / 3.35, SCREEN_HEIGHT - 85);
	slot->item->icon->instances[slot->bar_icon_instance].z = 10;
	item->instance_number++;
	slot->item->icon->instances[slot->bar_icon_instance].enabled = false;
	slot->icon_instance = mlx_image_to_window(core->mlx, item->icon, 0, 0);
	item->instance_number++;
	slot->item->icon->instances[slot->icon_instance].enabled = false;
    slot->items_number = number;
    slot->items_number_img = mlx_put_string(core->mlx, ft_itoa(number), 0, 0);
    slot->items_number_img_bar = mlx_put_string(core->mlx, ft_itoa(number), 0, (SCREEN_HEIGHT - 85) + 25);
	slot->items_number_img_bar->instances[0].z = 11;
	slot->items_number_img->instances[0].enabled = false;
	slot->items_number_img_bar->instances[0].enabled = false;
}
