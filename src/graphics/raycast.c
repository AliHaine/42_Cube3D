/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:58 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:48:01 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	init_ray_variables(t_core *core, t_ray *ray)
{
	ray->checkpoint_number = 0;
	ray->checkpoints = 0;
	ray->ray_x = core->player.playerpos[0];
	ray->ray_y = core->player.playerpos[1];
	ray->cosinus = cosf(ray->ray_angle);
	ray->sinus = sinf(ray->ray_angle);
}

static void	do_ray(t_core *core, t_ray *ray, float start_angle, int r)
{
	int	act;

	ray->ray_angle = start_angle + (r * core->consts.dist_between_ray);
	init_ray_variables(core, ray);
	while (1)
	{
		act = is_obstacle(core, ray);
		if (act == -1 || act == 1)
			break ;
		ray->ray_x += ray->cosinus;
		ray->ray_y += ray->sinus;
		mlx_put_pixel(core->imgs.img_map, (ray->ray_x / MINIMAP_SIZE),
			(ray->ray_y / MINIMAP_SIZE), core->consts.ray_color);
	}
	ray->ray_dist = calc_ray_dist(core, ray->ray_x, ray->ray_y, ray->ray_angle);
}

static void	good_wall(t_ray *rays)
{
    int		i;
    float	dist;
    int		j;

    i = 0;
    while (++i < RAY_NUMBER)
    {
        if (rays[i].wall_direction == rays[i - 1].wall_direction)
            continue ;
        dist = rays[i].ray_dist * rays[i].ray_dist;
        j = (int)((1.0f / (sqrt(dist) / 70.0f) * 50.0f));
        if (j + i >= RAY_NUMBER - 1 || j + i < 0)
            j = 0;
        if (j + i < RAY_NUMBER)
		{
            if (rays[i - 1].wall_direction == rays[i + j].wall_direction)
                rays[i].wall_direction = rays[i - 1].wall_direction;
        }
    }
}

void	raycast(t_core *core)
{
	int		r;
	t_ray	*rays;
	float	start_angle;

	r = -1;
	rays = (t_ray *)malloc(sizeof(t_ray) * RAY_NUMBER + 1);
	start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (++r < RAY_NUMBER)
	{
		do_ray(core, &rays[r], start_angle, r);
		rays[r].wall_direction = wall_direction(core, rays[r]);
	}
	r = -1;
	while (++r < RAY_NUMBER)
	{
		good_wall(rays);
		draw_columns(core, rays[r], r);
		if (rays[r].checkpoint_number > 0)
			draw_obstacles(core, rays[r], r);
	}
	free(rays);
}
