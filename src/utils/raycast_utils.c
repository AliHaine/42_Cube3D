
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

int	is_obstacle(t_core *core, t_ray *ray)
{
    char c;
    int ix;
    int iy;

    ix = (int) ray->ray_x / 64;
    iy = (int)ray->ray_y / 64;
    if (ix < 0 || iy < 0 || ix > core->consts.map_width
        || iy > core->consts.map_height)
        return (-1);
    c = core->consts.map[(int)ray->ray_y / 64]
    [(int) ray->ray_x / 64];
    if (c == '1')
        return (1);
    else if ((c == 'D' || c == 'Z') && ray->have_checkpoint == false) {
        ray->have_checkpoint = true;
        ray->checkpoint_x = ray->ray_x;
        ray->checkpoint_y = ray->ray_y;
        ray->obstacle = c;
    }
    return (0);
}
