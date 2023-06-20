#include "../../includes/includes.h"

static t_slot	*add_new_noed(short val, t_slot *current, t_item *hand_item)
{
	current->prev = malloc(sizeof(t_slot));
	current->prev->slot_id = val;
	current->prev->item = hand_item;
	current->prev->next = current;
	return (current->prev);
}

static t_slot	*add_first_noed(t_item *hand_item)
{
	t_slot *first;

	first = malloc(sizeof(t_slot));
	first->slot_id = 6;
	first->item = hand_item;
	first->next = 0;
	return (first);
}

void	setup_slot_struct(t_player *player, t_item *hand_item)
{
	int	i;

	i = 6;
	player->slot = add_first_noed(hand_item);
	while (i-- > 1)
	{
		player->slot = add_new_noed(i, player->slot, hand_item);
	}
	player->slot->prev = 0;
}

t_slot *get_first_slot(t_slot *slot)
{
	t_slot *copy;

	copy = slot;
	while (copy->slot_id != 1)
		copy = copy->prev;
	return (copy);
}
