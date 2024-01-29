/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_and_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:00:13 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 15:00:16 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

static bool	pass_conditions(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd, int fog_strength)
{
	if (fog_strength > 1)
	{
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++,
			(0 << 24) | (0 << 16) | (0 << 8) | 255);
		return (false);
	}
	return (true);
}

void	ceil_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd, t_player *player)
{
	const float	d = (((SCREEN_HEIGHT / 2.f) * 64.f) / (1 + (SCREEN_HEIGHT / 2.f) - tcd->iterator)
			/ cosf(dda->current_angle - player->playerangle));
	const float	fog_strength = d / FOG_DISTANCE;
	t_world		*world;
	int			value;
	uint32_t	color;

	world = get_world_active();
	if (!pass_conditions(imgs, dda, tcd, fog_strength))
		return ;
	value = (((int)(player->player_pos_xy[0] + dda->cos
					* d) % 64)
			+ ((int)(player->player_pos_xy[1] + dda->sin
					* d) % 64) * 64) * 4;
	if (value < 0)
		value = -value;
	color = get_rgb_color(world->ceil->pixels[value],
			world->ceil->pixels[value + 1],
			world->ceil->pixels[value + 2],
			world->ceil->pixels[value + 3]);
	color = apply_fog(color, fog_strength);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, color);
}

void	floor_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd, t_player *player)
{
	const float	d = (((SCREEN_HEIGHT / 2.f) * 64.f) / (tcd->iterator - (SCREEN_HEIGHT / 2.f) + 1.f)
			/ cosf(dda->current_angle - player->playerangle));
	const float	fog_strength = d / FOG_DISTANCE;
	t_world		*world;
	int			value;
	uint32_t	color;

	world = get_world_active();
	if (!pass_conditions(imgs, dda, tcd, fog_strength))
		return ;
	value = (((int)(player->player_pos_xy[0] + dda->cos
					* d) % 64)
			+ ((int)(player->player_pos_xy[1] + dda->sin
					* d) % 64) * 64) * 4;
	if (value < 0)
		value = -value;
	color = get_rgb_color(world->floor->pixels[value],
			world->floor->pixels[value + 1],
			world->floor->pixels[value + 2],
			world->floor->pixels[value + 3]);
	color = apply_fog(color, fog_strength);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, color);
}

void	skybox_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd, t_world *world)
{
	int					skybox_tex_x;
	int					skybox_tex_y;
	int					value;
	uint32_t			color;
	static const float	vertical_offset = -89.f * SCREEN_HEIGHT;

	skybox_tex_x = (int)((fmodf(dda->current_angle + (PI * 2), (PI * 2)))
			/ (PI * 2) * (float)world->ceil->width) % (int)world->ceil->width;
	skybox_tex_y = (int)((tcd->iterator - vertical_offset)
			* ((float)world->ceil->height / (float)world->ceil->width));
	if (skybox_tex_y <= 0)
		skybox_tex_y = 0;
	else
		skybox_tex_y %= (int)world->ceil->height;
	value = (skybox_tex_x + skybox_tex_y * (int)world->ceil->width) * 4;
	color = get_rgb_color(world->ceil->pixels[value],
			world->ceil->pixels[value + 1],
			world->ceil->pixels[value + 2],
			world->ceil->pixels[value + 3]);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, color);
}
