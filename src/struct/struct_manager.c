#include "../../includes/includes.h"

void	struct_setup(t_core *core)
{
	setup_slot_struct(&core->player, &core->items[HAND]);
}