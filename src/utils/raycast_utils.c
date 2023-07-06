
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

static void	add_checkpoint(t_ray *ray, char c)
{
	int				i;
	t_checkpoint	*new;

	if (ray->checkpoint_number == 0)
		new = (t_checkpoint *)malloc(sizeof(t_checkpoint));
	else
		new = (t_checkpoint *)malloc(sizeof(t_checkpoint)
				* (ray->checkpoint_number + 1));
	i = 0;
	while (i < ray->checkpoint_number)
	{
		//printf("n:%d\n", ray->checkpoint_number);
		new[i].checkpoint_x = ray->checkpoints[i].checkpoint_x;
		new[i].checkpoint_y = ray->checkpoints[i].checkpoint_y;
		new[i].obstacle = ray->checkpoints[i].obstacle;
		i++;
	}
	new[i].checkpoint_x = ray->ray_x;
	new[i].checkpoint_y = ray->ray_y;
	new[i].obstacle = c;
	if (ray->checkpoints)
		free(ray->checkpoints);
	ray->checkpoints = new;
	ray->checkpoint_number++;
}

static int	is_already_detected(int x, int y, t_ray *ray)
{
	int	i;

	i = -1;
	while (++i < ray->checkpoint_number)
	{
		if (x == (int)(ray->checkpoints[i].checkpoint_x / 64)
			&& y == (int)(ray->checkpoints[i].checkpoint_y / 64))
			return (1);
	}
	return (0);
}

int	is_obstacle(t_core *core, t_ray *ray)
{
	char	c;
	int		ix;
	int		iy;

	ix = (int)ray->ray_x / 64;
	iy = (int)ray->ray_y / 64;
	if (ix < 0 || iy < 0 || ix > core->consts.map_width
		|| iy > core->consts.map_height)
		return (-1);
	c = core->consts.map[iy][ix];
	if ((c == 'Z' || c == 'D') && !is_already_detected(ix, iy, ray))
		add_checkpoint(ray, c);
	if (c == '1')
		return (1);
	return (0);
}



void	fisheyes_fixor(t_dda *dda, float player_angle)
{
	float fix_angle;
	float two_pi;

	fix_angle = player_angle - dda->current_angle;
	two_pi = 2 * PI;
	if (fix_angle < 0)
		fix_angle += two_pi;
	if (fix_angle > two_pi)
		fix_angle -= two_pi;
	dda->dist_hv[0] = dda->dist_hv[0] * cos(fix_angle);
}