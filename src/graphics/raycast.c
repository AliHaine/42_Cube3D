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

static void	draw_obstacle(t_core *core, t_ray ray, int r)
{
	float			ray_distance;
	float			wall_height;
	mlx_texture_t	*texture;
	uint32_t		color;
	int				texture_xy[2];
	int				py;

	ray_distance = calc_ray_dist(core, ray.checkpoint_x, ray.checkpoint_y, ray.ray_angle);
	texture_xy[0] = get_obstacle_offset(obstacle_direction(core, ray), ray);
	wall_height = (SCREEN_HEIGHT * 64) / ray_distance;
	py = (SCREEN_HEIGHT - wall_height) / 2;
	if (ray.obstacle == 'D')
		texture = core->imgs.door_texture;
	while (py >= 0 && py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
				* TEXTURE_SIZE) / wall_height / 2;
		color = get_color(texture, ray_distance / FOG_DISTANCE, texture_xy);
		mlx_put_pixel(core->imgs.img_3d, r, py++, color);
	}
}

static void	draw_columns(t_core *core, t_ray ray, int r)
{
	float		wall_height;
	int			py;
	uint32_t	color;
	int			texture_xy[2];

	texture_xy[0] = get_offset(ray.wall_direction, ray);
	wall_height = (SCREEN_HEIGHT * 64) / ray.ray_dist;
	py = 0;
	while (py < (SCREEN_HEIGHT - wall_height) / 2 && py < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, r, py++, core->consts.top_color);
	while (py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
				* TEXTURE_SIZE) / wall_height / 2;
		color = get_color(core->imgs.wall_texture[ray.wall_direction],
				ray.ray_dist / FOG_DISTANCE, texture_xy);
		mlx_put_pixel(core->imgs.img_3d, r, py++, color);
	}
	while (py < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, r, py++, core->consts.bot_color);
}

static void	init_ray_variables(t_core *core, t_ray *ray, float *cosi, float *sinu, int r)
{
	ray->have_checkpoint = false;
	ray->ray_x = core->player.playerpos[0];
	ray->ray_y = core->player.playerpos[1];
	*cosi = cosf(ray->ray_angle);
	*sinu = sinf(ray->ray_angle);
}

static void    do_ray(t_core *core, t_ray *ray, float start_angle, int r)
{
    int     act;
    float   cosinus;
    float   sinus;

    ray->ray_angle = start_angle + (r * core->consts.dist_between_ray);
    init_ray_variables(core, ray, &cosinus, &sinus, r);
    while (1)
    {
        act = is_obstacle(core, ray);
        if (act == -1 || act == 1)
            break ;
        ray->ray_x += cosinus;
        ray->ray_y += sinus;
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
            continue;
        dist = rays[i].ray_dist * rays[i].ray_dist;
        j = (int)((1.0f / (sqrt(dist) / 70.0f)) * 50.0f);
        if (j + i >= RAY_NUMBER - 1 || j + i < 0)
            j = 0;
        if (j + i < RAY_NUMBER) {
            if (rays[i - 1].wall_direction == rays[i + j].wall_direction)
                rays[i].wall_direction = rays[i - 1].wall_direction;
        }
    }
}

void	raycast(t_core *core)
{
	int		r;
	t_ray	*rays = (t_ray *)malloc(sizeof(t_ray) * RAY_NUMBER + 1);
    float   start_angle;

	r = -1;
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
        if (rays[r].have_checkpoint == true)
            draw_obstacle(core, rays[r], r);
    }
    free(rays);
}
