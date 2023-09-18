
#include "../../includes/includes.h"

bool	lighter_check(t_slot *craft_table[10])
{
	int		ij[2];
	int		requiredItemsCount[2];

	requiredItemsCount[0] = 0;
	requiredItemsCount[1] = 0;
	ij[0] = -1;
	while (++ij[0] < 3)
	{
		ij[1] = -1;
		while (++ij[1] < 3)
		{
			if (craft_table[ij[0] * 3 + ij[1]]->item->name == FLINT)
				requiredItemsCount[0]++;
			else if (craft_table[ij[0] * 3 + ij[1]]->item->name == IRON)
				requiredItemsCount[1]++;
			else if (craft_table[ij[0] * 3 + ij[1]]->item->name != HAND)
				return (false);
		}
	}
	if (requiredItemsCount[0] == 1 && requiredItemsCount[1] == 1)
		return (true);
	return (false);
}
