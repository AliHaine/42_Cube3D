#include "../../includes/concepts/world.h"

t_world	*get_world(int num)
{
	return (&g_worlds[num]);
}

void set_world(t_world world, int num)
{
	g_worlds[num] = world;
}