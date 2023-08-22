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

//todo here
static void	draw_pixel_to_img2(mlx_image_t *img, int e, int x, int y, uint32_t color)
{
	while (e-- >= 0)
		mlx_put_pixel(img, x++, y, color);
}

void	draw_energy_bar(mlx_image_t *engbar_texture, int energy)
{
	int			energy_conv;
	int			y;
	int			x;
    uint32_t	full_color;
    uint32_t	empty_color;

	x = 3;
	y = 1;
	energy_conv = energy * 4.3;
    full_color = get_rgb_color(192, 19, 186, 255);
    empty_color = get_rgb_color(100, 80, 190, 255);
    while (y++ != 10)
    {
        if (y == 9 || y == 2)
        {
            x++;
			energy_conv -= 2;
        }
		draw_pixel_to_img2(engbar_texture, energy_conv, x, y, full_color);
        if (energy < 100)
        {
            if (y == 9 || y == 2)
				energy_conv += 4;
			energy_conv -= 100 * 4.3;
			energy_conv = abs(energy_conv);
            x += energy * 4.3;
            draw_pixel_to_img2(engbar_texture, energy_conv, x, y, empty_color);
        }
        x = 3;
		energy_conv = energy * 4.3;
    }
}

static void wall_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd)
{
	if (tcd->fog_strength > 1)
		tcd->color = (0 << 24) | (0 << 16) | (0 << 8) | 255;
	else if (tcd->hit_block != '1')
        get_color_block_texture(tcd->block->image, dda, tcd);
	else if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
        get_color_wall_texture(imgs->wall_texture[1],
                               (int) dda->r_xy[1], tcd);
	else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
		get_color_wall_texture(imgs->wall_texture[3],
							   (int) dda->r_xy[1], tcd);
	else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
		get_color_wall_texture(imgs->wall_texture[0],
							   (int) dda->r_xy[0], tcd);
	else
		get_color_wall_texture(imgs->wall_texture[2],
							   (int) dda->r_xy[0], tcd);
	tcd->color = apply_fog(tcd->color, tcd->fog_strength);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, tcd->color);
	tcd->current_step += tcd->step;
}

//todo bug with size width
void	minimap_drawing(t_imgs *imgs, const float playerpos[2], t_world *world)
{
	const int start_y = ((playerpos[1] + world->height) / 4) - (286 / 2);
	const int start_x = ((playerpos[0] + world->width) / 4) - (286 / 2);
	int                 case_y;
	int                 case_x;
	int                 py;
	int                 px;
	uint32_t	wall_color;

	py = -1;
	wall_color = get_rgb_color(109, 96, 77, 255);
	while (++py < 286)
	{
		px = -1;
        case_y = ((py + start_y) / 16);
        while (++px < 286)
        {
            case_x = ((px + start_x) / 16);
			if (get_pixel(imgs->map_texture, px, py) != -692152577)
				continue ;
            else if (case_y < 0 || case_x < 0 || case_y > (world->height * 3) - 1 || case_x > (world->width * 3) - 1)
                mlx_put_pixel(imgs->img_map, px, py, wall_color);
			else if (world->world[get_chunk_from_pos(case_x, case_y)][case_y % world->height][case_x % world->width] != '0')
				mlx_put_pixel(imgs->img_map, px, py, wall_color);
		}
	}
}

void	ceil_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd, t_world *world)
{
	int					skyboxTexX;
	int					skyboxTexY;
	int					value;
	uint32_t			color;
	static const float	vertical_offset = -89.f * SCREEN_HEIGHT;

	if (world->bt_color[1] > 0)
	{
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, world->bt_color[1]);
		return ;
	}
	skyboxTexX = (int)((fmodf(dda->current_angle + PI_2, PI_2))
			/ PI_2 * (float)world->ceil->width) % (int)world->ceil->width;
	skyboxTexY = (int)((tcd->iterator - vertical_offset)
			* ((float)world->ceil->height / (float)world->ceil->width));
	if (skyboxTexY <= 0)
		skyboxTexY = 0;
	else
		skyboxTexY %= (int)world->ceil->height;
	value = (skyboxTexX + skyboxTexY * (int)world->ceil->width) * 4;
	color = get_rgb_color(world->ceil->pixels[value],
						  world->ceil->pixels[value + 1],
						  world->ceil->pixels[value + 2],
						  world->ceil->pixels[value + 3]);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, color);
}



void	floor_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd,t_player *player, t_world *world)
{
	const float	s = (MID_HEIGHT * 64) / (tcd->iterator - MID_HEIGHT);
	const float	d = (s / cosf(dda->current_angle - player->playerangle));
	const float	fog_strength = d / FOG_DISTANCE;
	int			value;
	uint32_t	color;

	if (tcd->iterator == 360)
	{
		tcd->iterator++;
		return;
	}
	if (fog_strength > 1)
	{
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++,
			(0 << 24) | (0 << 16) | (0 << 8) | 255);
		return ;
	}
	value = (((int)(player->player_pos_xy[0] + dda->cos
					* d) % 64)
			+ ((int)(player->player_pos_xy[1] + dda->sin
					* d) % 64) * 64) * 4;
	color = get_rgb_color(world->floor->pixels[value],
			world->floor->pixels[value + 1],
						  world->floor->pixels[value + 2],
						  world->floor->pixels[value + 3]);
	color = apply_fog(color, fog_strength);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, color);
}

void	columns_drawing(t_imgs *imgs, t_dda *dda, t_world *world, t_block **blocks, t_player *player, t_options *options)
{
	t_col_drawing	tcd;

	setup_col_struct(&tcd, dda, world, blocks);
	tcd.floor_d = cosf(dda->current_angle - player->playerangle);
	while (tcd.iterator < tcd.ceil_floor_lineH)
	{
		if (options->skybox == true)
			ceil_drawing(imgs, dda, &tcd, player);
		else
			mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++,
				world->bt_color[0]);
	}
	while (tcd.iterator < tcd.wall_lineH)
		wall_drawing(imgs, dda, &tcd);
	while (tcd.iterator < SCREEN_HEIGHT)
	{
		if (options->floor_texture == true)
			floor_drawing(imgs, dda, &tcd, player);
		else
			mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++,
				world->bt_color[1]);
	}
}
