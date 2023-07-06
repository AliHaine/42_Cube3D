#include "../../includes/includes.h"

static t_slot	*add_new_noed(t_core *core, short val, t_slot *current, t_item *hand_item)
{
	current->prev = malloc(sizeof(t_slot));
	current->prev->icon_instance = -1;
	current->prev->bar_icon_instance = -1;
	current->prev->slot_id = val;
	current->prev->item = hand_item;
	current->items_number = 1;
	current->items_number_img = mlx_put_string(core->mlx, "1", 0, 0);
	current->items_number_img_bar = mlx_put_string(core->mlx, "1", 0, 0);
	current->items_number_img_bar->instances[0].y = (SCREEN_HEIGHT - 85) + 25;
	current->items_number_img->instances->enabled = false;
	current->items_number_img_bar->instances->enabled = false;
	current->items_number_img->instances[0].z = 7;
	current->bar_mutex = false;
	current->prev->next = current;
	return (current->prev);
}

static t_slot	*add_first_noed(t_core *core, t_item *hand_item)
{
	t_slot	*first;

	first = malloc(sizeof(t_slot));
	first->slot_id = 37;
	first->icon_instance = -1;
	first->bar_icon_instance = -1;
	first->item = hand_item;
	first->items_number = 1;
	first->items_number_img = mlx_put_string(core->mlx, "1", 0, 0);
	first->items_number_img_bar = mlx_put_string(core->mlx, "1", 0, 0);
	first->items_number_img_bar->instances[0].y = (SCREEN_HEIGHT - 85) + 25;
	first->items_number_img->instances->enabled = false;
	first->items_number_img_bar->instances->enabled = false;
	first->bar_mutex = false;
	first->items_number_img->instances[0].z = 7;
	first->next = 0;
	return (first);
}

void	setup_slot_struct(t_core *core, t_player *player, t_item *hand_item)
{
	int	i;

	i = 37;
	player->slot = add_first_noed(core, hand_item);
	while (i-- > 0)
		player->slot = add_new_noed(core, i, player->slot, hand_item);
	player->slot = player->slot->next;
    player->slot->prev = 0;
}

t_slot	*get_first_slot(t_slot *slot)
{
	t_slot	*copy;

	copy = slot;
	while (copy->slot_id != 1)
		copy = copy->prev;
	return (copy);
}
