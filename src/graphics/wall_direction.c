#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

int  wall_calc(t_const *consts, float angle)
{
	if (angle >= consts->south_east && angle < consts->south_west)
		return (0);
	else if (angle >= consts->south_west && angle < consts->north_west)
		return (1);
	else if (angle >= consts->north_west && angle < consts->north_east)
		return (2);
	else
		return (3);
}

static short	get_direction_x(int x, short i)
{
	if ((x % 64) >= 63)
		return (3);
	else if ((x % 64) <= 0)
		return (1);
	else
		return (0 + i);
}

static short	get_direction_y(int y, short i)
{
	if ((y % 64) >= 63)
		return (0);
	else if ((y % 64) <= 0)
		return (2);
	else
		return (1 + i);
}

short	wall_direction(t_core *core, t_ray ray)
{
    int res;

    res = wall_calc(&core->consts, ray.ray_angle);
	if (res == 0)
		return (get_direction_x((int)ray.ray_x, 2));
	else if (res == 1)
		return (get_direction_y((int)ray.ray_y, 2));
	else if (res == 2)
		return (get_direction_x((int)ray.ray_x, 0));
	else
		return (get_direction_y((int)ray.ray_y, 0));
}
