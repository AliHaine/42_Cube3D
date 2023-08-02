#include "../../includes/includes.h"

static bool	diamond_sword(t_core *core, t_slot *craft_table[10])
{
	if (craft_table[0]->item->name != HAND
		|| craft_table[1]->item->name != STICK
		|| craft_table[2]->item->name != HAND
		|| craft_table[3]->item->name != HAND
		|| craft_table[4]->item->name != DIAMOND
		|| craft_table[5]->item->name != HAND
		|| craft_table[6]->item->name != HAND
		|| craft_table[7]->item->name != DIAMOND
		|| craft_table[8]->item->name != HAND)
		return (false);
	if (craft_table[9]->item->name == HAND)
	{
		give_item(core, &core->items[SWORD_DIAMOND], 46, 1);
		display_item(core, get_slot(core, 46));
	}
	return (true);
}

static bool	lighter(t_core *core, t_slot *craft_table[10])
{
	if (craft_table[0]->item->name != HAND
		|| craft_table[1]->item->name != HAND
		|| craft_table[2]->item->name != FLINT
		|| craft_table[3]->item->name != HAND
		|| craft_table[4]->item->name != IRON
		|| craft_table[5]->item->name != HAND
		|| craft_table[6]->item->name != HAND
		|| craft_table[7]->item->name != HAND
		|| craft_table[8]->item->name != HAND)
		return (false);
	if (craft_table[9]->item->name == HAND)
	{
		give_item(core, &core->items[LIGHTER], 46, 1);
		display_item(core, get_slot(core, 46));
	}
	return (true);
}

void	crafting_engine(t_core *core)
{
	t_slot	*craft_table[10];

	craft_table[9] = get_slot(core, 46);
	craft_table[0] = get_slot(core, 37);
	craft_table[1] = get_slot(core, 38);
	craft_table[2] = get_slot(core, 39);
	craft_table[3] = get_slot(core, 40);
	craft_table[4] = get_slot(core, 41);
	craft_table[5] = get_slot(core, 42);
	craft_table[6] = get_slot(core, 43);
	craft_table[7] = get_slot(core, 44);
	craft_table[8] = get_slot(core, 45);
	if (diamond_sword(core, craft_table) == true)
		return ;
	if (lighter(core, craft_table) == true)
		return ;
	else if (craft_table[9]->item->name != HAND
		&& *core->player.holding_item == false)
		reset_slot(core, craft_table[9]);
}

void	craft(t_core *core)
{
	t_slot	*craft_table[10];
	short	i;

	craft_table[9] = get_slot(core, 46);
	if (craft_table[9]->item->name == HAND)
		return ;
	craft_table[0] = get_slot(core, 37);
	craft_table[1] = get_slot(core, 38);
	craft_table[2] = get_slot(core, 39);
	craft_table[3] = get_slot(core, 40);
	craft_table[4] = get_slot(core, 41);
	craft_table[5] = get_slot(core, 42);
	craft_table[6] = get_slot(core, 43);
	craft_table[7] = get_slot(core, 44);
	craft_table[8] = get_slot(core, 45);
	i = -1;
	while (++i < 9)
	{
		if (craft_table[i]->item->name != HAND
			&& craft_table[i]->items_number <= 1)
			reset_slot(core, craft_table[i]);
		else
			change_item_number(core, craft_table[i],
				(short)(craft_table[i]->items_number - 1));
	}
}
