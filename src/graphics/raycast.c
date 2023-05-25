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
#include "../../includes/defines.h"
#include "../../includes/structs.h"



static uint32_t	apply_fog(uint32_t color, float distance, float max_distance)
{
	float		fog_strength;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	fog_strength = distance / max_distance;
	if (fog_strength > 1.0)
		fog_strength = 1.0;
	r = ((color >> 24) & 0xFF) * (1.0 - fog_strength);
	g = ((color >> 16) & 0xFF) * (1.0 - fog_strength);
	b = ((color >> 8) & 0xFF) * (1.0 - fog_strength);
	a = (color & 0xFF);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void	draw_columns(t_core *core, t_ray ray, int r)
{
	float		wall_height;
	float		py;
	uint32_t	color;

	wall_height = (SCREEN_HEIGHT * 64) / ray.ray_distance;
	py = (SCREEN_HEIGHT - wall_height) / 2;
	if (py < 0)
		py = 0;
	while (py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		color = apply_fog(((150 << 24) + (150 << 16) + (150 << 8) + 255), ray.ray_distance, FOG_DISTANCE);
		mlx_put_pixel(core->consts.img_3d, r, py, color);
		py++;
	}
}

float	calc_ray_distance(t_core *core, t_ray ray)
{
	float	ray_distance;

	ray_distance = sqrtf(((ray.ray_x - core->player.playerpos[0]) * (
					ray.ray_x - core->player.playerpos[0]) + ((ray.ray_y
						- core->player.playerpos[1]) * (ray.ray_y
						- core->player.playerpos[1]))));
	ray_distance *= cos(ray.ray_angle - core->player.playerangle);
	return (ray_distance);
}

void	raycast(t_core *core)
{
	int		r;
	t_ray	ray;
	float	thales[2];
	r = -1;
	ray.start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (++r < RAY_NUMBER)
	{
		ray.ray_x = core->player.playerpos[0];
		ray.ray_y = core->player.playerpos[1];
		ray.ray_angle = ray.start_angle + (r * core->consts.dist_between_ray);
		thales[0] = cosf(ray.ray_angle);
		thales[1] = sin(ray.ray_angle);
		while (ray.ray_x >= 0 && ray.ray_x < SCREEN_WIDTH && ray.ray_y >= 0
			&& ray.ray_y < SCREEN_HEIGHT
			&& core->consts.map[(int)ray.ray_y / 64]
			[(int)ray.ray_x / 64] != '1')
		{
			ray.ray_x += thales[0];
			ray.ray_y += thales[1];
			if (r % 12 == 0)
				mlx_put_pixel(core->consts.img_map, (ray.ray_x / M_SIZE), (ray.ray_y / M_SIZE), core->consts.ray_color);
		}
		ray.ray_distance = calc_ray_distance(core, ray);
		draw_columns(core, ray, r);
	}
}
