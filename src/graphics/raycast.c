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

void	raycast(t_core *core)
{
	int		ray;
	float	start_angle;
	float	ray_x;
	float	ray_y;
	float	ray_angle;

	ray = 0;
	start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (ray < RAY_NUMBER)
	{
		ray_x = core->player.playerpos[0];
		ray_y = core->player.playerpos[1];
		ray_angle = start_angle + (ray * core->consts.dist_between_ray);
		while (ray_x >= 0 && ray_x < SCREEN_WIDTH && ray_y >= 0
			&& ray_y < SCREEN_HEIGHT
			&& core->consts.map[(int)ray_y / 64][(int)ray_x / 64] == '0')
		{
			ray_x += cosf(ray_angle);
			ray_y += sinf(ray_angle);
			mlx_put_pixel(core->consts.img_map, ray_x, ray_y,
				core->consts.ray_color);
		}
//		printf("ray distance = %f\n", ((ray_x - core->playerpos[0]) * (ray_x - core->playerpos[0])) +
//			((ray_y - core->playerpos[1]) * (ray_y - core->playerpos[1])));
		printf("ray collision points = x:%f y:%f\n", ray_x, ray_y);
		ray++;
	}
}
