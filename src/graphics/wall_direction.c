
#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

int	isWall(t_core *core, t_ray ray)
{
	if (ray.ray_x >= 0 && ray.ray_y >= 0
		&& core->consts.map[(int)ray.ray_y / 64]
		[(int)ray.ray_x / 64] != '1')
		return (0);
	return (1);
}

double	calculate_vertical_distance(t_core *core, t_ray ray)
{
	double	x;
	double	y;
	double	step_x;
	double	step_y;

	if (ray.ray_x > 0)
		x = ceil(core->player.playerpos[0] / 64) * 64;
	else
		x = floor(core->player.playerpos[0] / 64) * 64;
	step_x = 64 * (cosf(core->player.playerangle) > 0 ? 1 : -1);
	step_y = step_x * (sinf(core->player.playerangle) / cosf(core->player.playerangle));
	y = core->player.playerpos[1] + (x - core->player.playerpos[0]) * (sinf(core->player.playerangle) / (cosf(core->player.playerangle)));
	while (!isWall(core, ray))
	{
		x += step_x;
		y += step_y;
	}
	return sqrt(pow((x - core->player.playerpos[0]), 2) + pow((y - core->player.playerpos[1]), 2));
}

double	calculate_horizontal_distance(t_core *core, t_ray ray) {
	double	x;
	double	y;
	double	step_x;
	double	step_y;

	if (sinf(core->player.playerangle) > 0)
		y = ceil(core->player.playerpos[1] / 64) * 64;
	else
		y = floor(core->player.playerpos[1] / 64) * 64;
	step_y = 64 * (sinf(core->player.playerangle) > 0 ? 1 : -1);
	step_x = step_y * (cosf(core->player.playerangle) / sinf(core->player.playerangle));
	x = core->player.playerpos[0] + (y - core->player.playerpos[1]) * (cosf(core->player.playerangle) / sinf(core->player.playerangle));
	while (!isWall(core, ray)) {
		x += step_x;
		y += step_y;
	}
	return sqrt(pow((x - core->player.playerpos[0]), 2) + pow((y - core->player.playerpos[1]), 2));
}

char	wall_direction(t_core *core, t_ray ray)
{
	if (calculate_horizontal_distance(core, ray)
		> calculate_vertical_distance(core, ray))
	{
		if (ray.ray_angle > (PI / 2) && ray.ray_angle < ((3 * PI) / 2))
			return ('E');
		else
			return ('W');
	}
	else
	{
		if (ray.ray_angle > PI)
			return ('N');
		else
			return ('S');
	}

}
