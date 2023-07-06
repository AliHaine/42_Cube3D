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

static uint32_t	get_color_from_wall_texture(mlx_texture_t *wall_texture, const int texture_xy)
{
	//TODO
	return (0);
}

static int	wall_drawing(t_core *core, t_dda *dda, int i, float wall_height)
{
	uint32_t color;

	while (i < (SCREEN_HEIGHT + wall_height) / 2 && i < SCREEN_HEIGHT)
	{
		/*texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
						 * TEXTURE_SIZE) / wall_height / 2;*/
		if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
            color = get_rgb_color(255, 255, 255);
        else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
            color = get_rgb_color(255, 0, 255);
        else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
            color = get_rgb_color(0, 255, 0);
        else
            color = get_rgb_color(255, 255, 0);
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, color);
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
	while (i < (SCREEN_HEIGHT + wall_height) / 2 && i < SCREEN_HEIGHT)
		i += wall_drawing(core, dda, i, wall_height);
	while (i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.bot_color);
}