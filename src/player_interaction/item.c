#include "../../includes/includes.h"

void	give_item(t_core *core, t_item *item, int slot_id, int number)
{
	t_slot	*slot;

	if (slot_id > 36)
		return ;
	slot = core->player.slot;
	while (slot->slot_id != slot_id)
		slot = slot->next;
	slot->item = item;
	slot->bar_icon_instance = mlx_image_to_window(core->mlx, item->icon, SCREEN_WIDTH / 3.35, SCREEN_HEIGHT - 85);
	item->instance_number++;
	slot->item->icon->instances[slot->bar_icon_instance].enabled = false;
	slot->icon_instance = mlx_image_to_window(core->mlx, item->icon, 0, 0);
	item->instance_number++;
	slot->item->icon->instances[slot->icon_instance].enabled = false;
    slot->items_number = number;
    slot->items_number_img = mlx_put_string(core->mlx, ft_itoa(number), 0, 0);
    slot->items_number_img_bar = mlx_put_string(core->mlx, ft_itoa(number), 0, (SCREEN_HEIGHT - 85) + 25);
}
