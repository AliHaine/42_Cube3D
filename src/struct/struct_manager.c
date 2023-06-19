#include "../../includes/includes.h"

static void test_create_animation(t_core *core)
{
	core->animations[0].is_playing = false;
	core->animations[0].speed = -0.01;
	core->animations[0].animation = SWORD_NETHER_ATTACK;
	core->animations[0].image = core->imgs.sword_nether;
	//core->animations[1] = 0;
}

void	test_create_item(t_core *core)
{
	core->items[0].name = SWORD_NETHER;
	core->items[0].image = core->imgs.sword_nether[0];
	core->items[0].icon = 0;
	core->items[0].animation = &core->animations[0];

	core->items[0].damage = 0;
	core->items[0].strength = 0;
	core->items[0].durability = 0;
	core->items[0].scope = 0;
}


void	struct_setup(t_core *core)
{
	setup_slot_struct(&core->player);
	test_create_animation(core);
	test_create_item(core);
}