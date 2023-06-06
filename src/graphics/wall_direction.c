#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

char	wall_direction(t_ray ray)
{
	if (ray.ray_angle >= (M_PI / 4) && ray.ray_angle < ((3 * M_PI) / 4))
	{
		if ((int)ray.ray_x % 64 >= 63)
			return ('W');
		else if ((int)ray.ray_x % 64 <= 0)
			return ('E');
		else
			return ('S');
	}
	else if (ray.ray_angle >= ((3 * M_PI) / 4) && ray.ray_angle < ((5 * M_PI) / 4))
	{
		if ((int)ray.ray_y % 64 >= 63)
			return ('N');
		else if ((int)ray.ray_y % 64 <= 0)
			return ('S');
		else
			return ('W');
	}
	else if (ray.ray_angle >= ((5 * M_PI) / 4) && ray.ray_angle < ((7 * M_PI) / 4))
	{
		if ((int)ray.ray_x % 64 >= 63)
			return ('W');
		else if ((int)ray.ray_x % 64 <= 0)
			return ('E');
		else
			return ('N');
	}
	else
	{
		if ((int)ray.ray_y % 64 >= 63)
			return ('N');
		else if ((int)ray.ray_y % 64 <= 0)
			return ('S');
		else
			return ('E');
	}
}
