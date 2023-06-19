#include "../../includes/includes.h"

static t_slot	*add_new_noed(short val, t_slot *current)
{
	current->prev = malloc(sizeof(t_slot));
	current->prev->slot_id = val;
	current->prev->item = 0;
	current->prev->next = current;
	return (current->prev);
}

static t_slot	*add_first_noed()
{
	t_slot *first;

	first = malloc(sizeof(t_slot));
	first->slot_id = 6;
	first->item = 0;
	first->next = 0;
	return (first);
}

void	setup_slot_struct(t_player *player)
{
	int	i;

	i = 6;
	player->slot = add_first_noed();
	while (i-- > 1)
	{
		player->slot = add_new_noed(i, player->slot);
	}
	player->slot->prev = 0;
}
