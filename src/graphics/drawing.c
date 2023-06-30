/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:18:01 by ayagmur           #+#    #+#             */
/*   Updated: 2023/06/30 23:18:03 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	wall_drawing(t_core *core, t_dda *dda, int i, float wall_height)
{
	while (i < (SCREEN_HEIGHT + wall_height) / 2 && i < SCREEN_HEIGHT)
	{
		/*texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
						 * TEXTURE_SIZE) / wall_height / 2;*/
		//color = get_color(core->imgs.wall_texture[ray.wall_direction],
		//ray.ray_dist / FOG_DISTANCE, texture_xy);
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, get_rgb_color(0, 255,0));
	}
	return (i);
}

void	columns_drawing(t_core *core, t_dda *dda)
{
	float			wall_height;
	int				i;
	uint32_t		color;
	int				texture_xy[2];

	//texture_xy[0] = get_
	// offset(ray.wall_direction, ray);
	if (dda->dist_hv[0] == 10000)
		wall_height = (SCREEN_HEIGHT * 64) / dda->dist_hv[1];
	else
		wall_height = (SCREEN_HEIGHT * 64) / dda->dist_hv[0];
	i = 0;
	while (i < (SCREEN_HEIGHT - wall_height) / 2 && i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.top_color);
	while (i < (SCREEN_HEIGHT + wall_height) / 2 && i < SCREEN_HEIGHT)
		i += wall_drawing(core, dda, i, wall_height);
	while (i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.bot_color);
}