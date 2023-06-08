#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

static int  wall_calc(t_const *consts, float angle)
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

static char	get_direction_x(int x, int i)
{
	if ((x % 64) >= 63)
		return ('W');
	else if ((x % 64) <= 0)
		return ('E');
	else
		return ('N' + i);
}

static char	get_direction_y(int y, int i)
{
	if ((y % 64) >= 63)
		return ('N');
	else if ((y % 64) <= 0)
		return ('S');
	else
		return ('E' + i);
}

char	wall_direction(t_core *core, t_ray ray)
{
    int res;

    res = wall_calc(&core->consts, ray.ray_angle);
	if (res == 0)
		return (get_direction_x((int)ray.ray_x, 5));
	else if (res == 1)
		return (get_direction_y((int)ray.ray_y, 18));
	else if (res == 2)
		return (get_direction_x((int)ray.ray_x, 0));
	else
		return (get_direction_y((int)ray.ray_y, 0));
}
