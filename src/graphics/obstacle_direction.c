#include "../../includes/includes.h"

static int	wall_calc(t_const *consts, float angle)
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

static int	get_direction_x(float x, int i)
{
	int	res;

	res = (int)(x) % 64;
	if (res >= 63)
	{
		return (3);
	}
	else if (res <= 0)
		return (1);
	else
		return (0 + i);
}

static int	get_direction_y(float y, int i)
{
	int res;

	res = (int)(y) % 64;
	if (res >= 63)
		return (0);
	else if (res <= 0)
		return (2);
	else
		return (1 + i);
}

int	obstacle_direction(t_core *core, t_checkpoint check, t_ray ray)
{
	int	res;

	res = wall_calc(&core->consts, ray.ray_angle);
	if (res == 0)
		return (get_direction_x(check.checkpoint_x, 2));
	else if (res == 1)
		return (get_direction_y(check.checkpoint_y, 2));
	else if (res == 2)
		return (get_direction_x(check.checkpoint_x, 0));
	else
		return (get_direction_y(check.checkpoint_y, 0));
}

int	get_obstacle_offset(int direction, t_checkpoint check)
{
	if (direction == 1)
		return ((int)check.checkpoint_y % 64);
	else if (direction == 3)
		return (63 - (int)check.checkpoint_y % 64);
	else if (direction == 0)
		return ((int)check.checkpoint_x % 64);
	else if (direction == 2)
		return (63 - (int)check.checkpoint_x % 64);
	return (0);
}
