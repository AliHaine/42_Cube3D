#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

static short wall_calc(float angle)
{
	if (angle >= (M_PI / 4) && angle < ((3 * M_PI) / 4))
		return (0);
	else if (angle >= ((3 * M_PI) / 4) && angle < ((5 * M_PI) / 4))
		return (1);
	else if (angle >= ((5 * M_PI) / 4) && angle < ((7 * M_PI) / 4))
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

char	wall_direction(t_ray ray)
{
	if (wall_calc(ray.ray_angle) == 0)
		return (get_direction_x((int)ray.ray_x, 5));
	else if (wall_calc(ray.ray_angle) == 1)
		return (get_direction_y((int)ray.ray_y, 18));
	else if (wall_calc(ray.ray_angle) == 2)
		return (get_direction_x((int)ray.ray_x, 0));
	else
		return (get_direction_y((int)ray.ray_y, 0));
}
