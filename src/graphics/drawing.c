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

static void	get_nether_portal(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd)
{
	static double	previous_time = 0.f;
	static int		act = -1;
	double			actual_time;

	if (act == -1)
	{
		previous_time = mlx_get_time();
		act = 0;
	}
	actual_time = mlx_get_time();
	if (actual_time >= previous_time + 0.2f)
	{
		previous_time = actual_time;
		if (act + 1 >= 15)
			act = 0;
		else
			act++;
	}
	if (dda->hit_hv == 1)
		return (get_color_from_wall_texture(
				imgs->nether_portal[act], (int)dda->r_xy[1], tcd));
	else
		return (get_color_from_wall_texture(
				imgs->nether_portal[act], (int)dda->r_xy[0], tcd));
}

static void wall_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd)
{
	if (tcd->fog_strength > 1)
		tcd->color = (0 << 24) | (0 << 16) | (0 << 8) | 255;
	else if (dda->hit_block == 'D')
		get_nether_portal(imgs, dda, tcd);
	else if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
		get_color_from_wall_texture(imgs->wall_texture[1],
			(int)dda->r_xy[1], tcd);
	else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
		get_color_from_wall_texture(imgs->wall_texture[3],
			(int)dda->r_xy[1], tcd);
	else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
		get_color_from_wall_texture(imgs->wall_texture[0],
			(int)dda->r_xy[0], tcd);
	else
		get_color_from_wall_texture(imgs->wall_texture[2],
			(int)dda->r_xy[0], tcd);
	tcd->color = apply_fog(tcd->color, tcd->fog_strength);
	mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, tcd->color);
	tcd->current_step += tcd->step;
}

static void floor_drawing(mlx_texture_t *floor_texture, t_col_drawing *tcd, t_dda *dda, float playerpos[2], mlx_image_t *i3)
{

    tcd->iterator++;
}

void	minimap_drawing(float angle, t_imgs *imgs, const float playerpos[2], t_map *map)
{
	const int start_y = (playerpos[1] / 4) - (286 / 2);
	const int start_x = (playerpos[0] / 4) - (286 / 2);
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
			else if (case_y < 0 || case_x < 0 || case_y > map->height - 1 || case_x > map->width - 1)
				mlx_put_pixel(imgs->img_map, px, py, wall_color);
			else if (map->map[case_y][case_x] == '1')
				mlx_put_pixel(imgs->img_map, px, py, wall_color);
		}
	}
}

void	columns_drawing(t_imgs *imgs, t_dda *dda, uint32_t bt_color[2], float playerpos[2])
{
    t_col_drawing  tcd;

	setup_col_struct(&tcd, dda);;
	while (tcd.iterator < tcd.sky_lineH)
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, bt_color[1]);
	while (tcd.iterator < tcd.wall_lineH)
		wall_drawing(imgs, dda, &tcd);
	while (tcd.iterator < SCREEN_HEIGHT)
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, bt_color[0]);
}
