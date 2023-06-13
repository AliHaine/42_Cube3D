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
	int			direction;

	direction = wall_direction(core, ray);
	texture_xy[0] = get_offset(direction, ray);
	wall_height = (SCREEN_HEIGHT * 64) / ray.ray_dist;
	py = 0;
	while (py < (SCREEN_HEIGHT - wall_height) / 2 && py < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, r, py++, core->consts.top_color);
	while (py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
				* TEXTURE_SIZE) / wall_height / 2;
		color = get_color(core->imgs.wall_texture[direction],
				ray.ray_dist / FOG_DISTANCE, texture_xy);
		mlx_put_pixel(core->imgs.img_3d, r, py++, color);
	}
	while (py < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, r, py++, core->consts.bot_color);
}

static int	is_obstacle(t_core *core, t_ray *ray)
{
	char	c;

	if (ray->ray_x < 0 || ray->ray_y < 0)
		return (-1);
	c = core->consts.map[(int)ray->ray_y / 64]
	[(int)ray->ray_x / 64];
	if (c == '1')
		return (1);
	else if (c == 'D' && ray->have_checkpoint == false)
	{
		ray->have_checkpoint = true;
		ray->checkpoint_x = ray->ray_x;
		ray->checkpoint_y = ray->ray_y;
		ray->obstacle = c;
	}
	return (0);
}

static void	init_ray_variables(t_core *core, t_ray *ray, float *cosi, float *sinu, int r)
{

	ray->have_checkpoint = false;
	ray->ray_x = core->player.playerpos[0];
	ray->ray_y = core->player.playerpos[1];
	ray->ray_angle = ray->start_angle + (r * core->consts.dist_between_ray);
	*cosi = cosf(ray->ray_angle);
	*sinu = sinf(ray->ray_angle);
}

void	raycast(t_core *core)
{
	int		r;
	t_ray	ray;
	float	thales[2];
	int		act;

	r = -1;
	ray.start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (++r < RAY_NUMBER)
	{
		init_ray_variables(core, &ray, &thales[0], &thales[1], r);
		while (1)
		{
			act = is_obstacle(core, &ray);
			if (act == -1 || act == 1)
				break ;
			ray.ray_x += thales[0];
			ray.ray_y += thales[1];
			mlx_put_pixel(core->imgs.img_map, (ray.ray_x / MINIMAP_SIZE),
				(ray.ray_y / MINIMAP_SIZE), core->consts.ray_color);
		}
		ray.ray_dist = calc_ray_dist(core, ray.ray_x, ray.ray_y, ray.ray_angle);
		draw_columns(core, ray, r);
		if (ray.have_checkpoint == true)
			draw_obstacle(core, ray, r);
	}
}
