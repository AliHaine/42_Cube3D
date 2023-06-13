
#include "../../includes/includes.h"

float	calc_ray_dist(t_core *core, float ray_x, float ray_y, float ray_angle)
{
	float	ray_distance;

	ray_distance = sqrtf(((ray_x - core->player.playerpos[0]) * (
					ray_x - core->player.playerpos[0]) + ((ray_y
						- core->player.playerpos[1]) * (ray_y
						- core->player.playerpos[1]))));
	ray_distance *= cos(ray_angle - core->player.playerangle);
	return (ray_distance);
}
