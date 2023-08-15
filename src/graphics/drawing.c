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

void	minimap_drawing(t_imgs *imgs, const float playerpos[2], t_map *map)
{
	const int start_y = ((playerpos[1] + map->height) / 4) - (286 / 2);
	const int start_x = ((playerpos[0] + map->width) / 4) - (286 / 2);
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
		case_y = (py + start_y) / 16;
		while (++px < 286)
		{
			case_x = (px + start_x) / 16;
			if (get_pixel(imgs->map_texture, px, py) != -692152577)
				continue ;
			else if (case_y < 0 || case_x < 0 || case_y > (map->height * 3) - 1 || case_x > (map->width * 3) - 1)
				mlx_put_pixel(imgs->img_map, px, py, wall_color);
			else if (map->world[case_y][case_x] == '1')
				mlx_put_pixel(imgs->img_map, px, py, wall_color);
		}
	}
}

void	columns_drawing(t_imgs *imgs, t_dda *dda, t_map *map, t_block **blocks, t_player *player)
{
    t_col_drawing  tcd;

	setup_col_struct(&tcd, dda, map, blocks);
	while (tcd.iterator < tcd.ceil_floor_lineH)
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, map->bt_color[1]);
	while (tcd.iterator < tcd.wall_lineH)
		wall_drawing(imgs, dda, &tcd);
	while (tcd.iterator < SCREEN_HEIGHT)
		//floor_drawing(imgs->floor_texture, &tcd, dda, player->player_pos_yx, imgs->img_3d);
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, map->bt_color[0]);
}
