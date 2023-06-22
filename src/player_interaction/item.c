#include "../../includes/includes.h"

void    give_item(t_slot *slot, t_item *item)
{
    slot->item = item;
    if (slot->slot_id > 1)
        slot->item->icon->instances->x += 60;
}