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

static void	get_color_from_wall_texture(mlx_texture_t *wall_texture, int r, t_wall_drawing *twd)
{
	int			value;

	if (r < 0) {
		printf("%d\n", r);
		return ;
	}
	value = ((r % 64) + ((int)twd->current_step * (int)wall_texture->width)) * 4;
	if (value >= 16384)
		return ;
	twd->color = get_rgb_color(wall_texture->pixels[value],wall_texture->pixels[value + 1]
						  ,wall_texture->pixels[value + 2],wall_texture->pixels[value + 3]);
}

static int	wall_drawing(t_core *core, t_dda *dda, int i, float wall_height)
{
	uint32_t color;
	t_wall_drawing twd;
	int save = i;

	setup_wall_struct(&twd, wall_height, dda->dist_hv[0]);
    while (i < twd.lineH)
	{
		if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
			get_color_from_wall_texture(core->imgs.wall_texture[0], (int)dda->r_xy[1], &twd);
        else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3) {
			//dda->r_xy[1] = 64 + dda->r_xy[1];
			if (save == i) {
				dda->r_xy[1] -= 65;
				printf("%f\n", dda->r_xy[1]);
			}
			//dda->r_xy[1] += 64;
			get_color_from_wall_texture(core->imgs.wall_texture[0], (int)dda->r_xy[1], &twd);
		}
        else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
            color = get_rgb_color(0, 255, 0, 255);
        else
            color = get_rgb_color(255, 255, 0, 255);
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, twd.color);
		twd.current_step += twd.step;
	}
	return (i);
}

void	columns_drawing(t_core *core, t_dda *dda)
{
	int				i;

	i = 0;
	while (i < (SCREEN_HEIGHT - dda->wall_height) / 2 && i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.top_color);
	while (i < (SCREEN_HEIGHT + dda->wall_height) / 2 && i < SCREEN_HEIGHT) {
		i += wall_drawing(core, dda, i, dda->wall_height);
	}
	while (i < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, dda->ray, i++, core->consts.bot_color);
}