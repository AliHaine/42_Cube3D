/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crafting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:24:52 by ngalzand          #+#    #+#             */
/*   Updated: 2023/09/01 11:24:59 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	diamond_sword(t_core *core, t_slot *craft_table[10])
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (craft_table[i]->item->name == STICK
			&& craft_table[i + 3]->item->name == DIAMOND
			&& craft_table[i + 6]->item->name == DIAMOND)
		{
			if (craft_table[9]->item->name == HAND)
			{
				give_item(core, get_item(SWORD_DIAMOND), 46, 1);
				display_item(core, get_slot(core, 46));
			}
			return (true);
		}
	}
	return (false);
}

static bool	lighter(t_core *core, t_slot *craft_table[10])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (craft_table[i * 3 + j]->item->name == FLINT)
			{
				if (i - 1 >= 0 && j + 1 < 3 && craft_table
					[(i - 1) * 3 + (j + 1)]->item->name == IRON)
				{
					if (craft_table[9]->item->name == HAND)
					{
						give_item(core, get_item(LIGHTER), 46, 1);
						display_item(core, get_slot(core, 46));
					}
					return (true);
				}
			}
		}
	}
	return (false);
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
	if (lighter_check(craft_table) && lighter(core, craft_table))
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
