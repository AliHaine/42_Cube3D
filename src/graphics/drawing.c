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

static uint32_t	get_color_from_wall_texture(mlx_texture_t *wall_texture, const float r_xy[2], float x)
{
	uint32_t	color;
	int			value;

	//printf("rx = %f ry = %f step = %f\n", r_xy[0], r_xy[1], x);
	value = ((((int)r_xy[1]) % 64) + ((int)x * (int)wall_texture->width)) * 4;
	color = get_rgb_color(wall_texture->pixels[value],wall_texture->pixels[value + 1]
						  ,wall_texture->pixels[value + 2],wall_texture->pixels[value + 3]);
	return color;
}

static int	wall_drawing(t_core *core, t_dda *dda, int i, float wall_height)
{
	uint32_t color;
	int lineH = ((SCREEN_HEIGHT + wall_height) / 2);
	int test = (64 * SCREEN_HEIGHT) / dda->dist_hv[0];
	float step = 64.0f / (float)test;
	float xstep = 0.0f;
	if (lineH > SCREEN_HEIGHT)
		xstep = (test - SCREEN_HEIGHT) / 2.0;
	xstep *= step;
    while (i < lineH && i < SCREEN_HEIGHT)
	{
		/*if (xstep > 64)
			printf("%f\n", xstep);*/
		if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
			color = get_color_from_wall_texture(core->imgs.wall_texture[0], dda->r_xy, xstep);
        else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
            color = get_rgb_color(255, 0, 255, 255);
        else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
            color = get_rgb_color(0, 255, 0, 255);
        else
            color = get_rgb_color(255, 255, 0, 255);
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, color);
		xstep += step;
	}
	return (i);
}

void	columns_drawing(t_core *core, t_dda *dda)
{
	float			wall_height;
	int				i;

	if (dda->dist_hv[0] == 10000)
		wall_height = (SCREEN_HEIGHT * 64) / dda->dist_hv[1];
	else
		wall_height = (SCREEN_HEIGHT * 64) / dda->dist_hv[0];
	i = 0;
	while (i < (SCREEN_HEIGHT - wall_height) / 2 && i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.top_color);
	while (i < (SCREEN_HEIGHT + wall_height) / 2 && i < SCREEN_HEIGHT) {
		i += wall_drawing(core, dda, i, wall_height);
	}
	while (i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.bot_color);
}