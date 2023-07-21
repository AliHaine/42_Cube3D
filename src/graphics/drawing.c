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

void	draw_energy_bar(mlx_image_t *engbar_texture, short energy)
{
    t_t_i		ti;
    uint32_t	full_color;
    uint32_t	empty_color;

    init_tti_struct(&ti, ((energy * 4.3)), 3, 2);
    full_color = get_rgb_color(192, 19, 186, 255);
    empty_color = get_rgb_color(100, 80, 190, 255);
    while (ti.c != 10)
    {
        if (ti.c == 9 || ti.c == 2)
        {
            ti.b++;
            ti.a -= 2;
        }
        draw_pixel_to_img(engbar_texture, ti, full_color);
        if (energy < 100)
        {
            if (ti.c == 9 || ti.c == 2)
                ti.a += 4;
            ti.a -= 100 * 4.3;
            ti.a = abs(ti.a);
            ti.b += energy * 4.3;
            draw_pixel_to_img(engbar_texture, ti, empty_color);
        }
        ti.b = 3;
        ti.c++;
        ti.a = energy * 4.3;
    }
}

static void wall_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd)
{
    if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
        get_color_from_wall_texture(imgs->wall_texture[1], (int)dda->r_xy[1], tcd);
    else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
        get_color_from_wall_texture(imgs->wall_texture[3], (int)dda->r_xy[1], tcd);
    else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
        get_color_from_wall_texture(imgs->wall_texture[0], (int)dda->r_xy[0], tcd);
    else
        get_color_from_wall_texture(imgs->wall_texture[2], (int)dda->r_xy[0], tcd);
    mlx_put_pixel(imgs->img_3d, dda->ray, tcd->iterator++, tcd->color);
    tcd->current_step += tcd->step;
}

static void floor_drawing(mlx_texture_t *floor_texture, t_col_drawing *tcd, t_dda *dda, float playerpos[2], mlx_image_t *i3)
{
    /*float fy;
    float tx;
    float ty;
	float ray_lengh = dda->dist_hv[0] / cosf(dda->current_angle);
    static bool f = false;

    fy = tcd->iterator - (SCREEN_HEIGHT / 2.0);
    tx = playerpos[0] / 2 + cosf(dda->current_angle) * 158 * 64 / fy / cosf(dda->current_angle_fix);
    ty = playerpos[1] / 2 - sinf(dda->current_angle) * 158 * 64 / fy / cosf(dda->current_angle_fix);
	if (dda->ray == 0)
	{
		//if (!f)%
			printf("%f %d %d %f %d %f %f\n", fy, (int)dda->r_xy[1], (int)tx, ty, tcd->sky_lineH, ray_lengh, dda->dist_hv[0]);
			//printf("%f %f %d %d %f %f\n", tx, ty, (int)dda->r_xy[0], (int)dda->r_xy[1], dda->dist_hv[0], dda->dist_hv[1]);
		//f = true;
	} else
		f = false;*/
    tcd->iterator++;
}

void	minimap_drawing(float direction, t_const consts, t_imgs *imgs, const float playerpos[2])
{
	const int start_y = (playerpos[1] / 4) - (286 / 2);
	const int start_x = (playerpos[0] / 4) - (286 / 2);
	int                 case_y;
	int                 case_x;
	int                 py;
	int                 px;

	py = -1;
	while (++py < 286)
	{
		px = -1;
		case_y = (py + start_y) / 16;
		while (++px < 286)
		{
			case_x = (px + start_x) / 16;
			if (get_pixel(imgs->map_texture, px, py) != -692152577)
				continue ;
			else if (case_y < 0 || case_x < 0 ||case_y > consts.map_height || case_x > consts.map_width - 1)
				mlx_put_pixel(imgs->img_map, px, py, consts.minimap_wall_color);
			else if (consts.map[case_y][case_x] == '1')
				mlx_put_pixel(imgs->img_map, px, py, consts.minimap_wall_color);
		}
	}
	//mlx_put_pixel(imgs->img_map, 90, 90, get_rgb_color(0, 255, 0,255));
}

void	columns_drawing(t_imgs *imgs, t_dda *dda, uint32_t bt_color[2], float playerpos[2])
{
    t_col_drawing  tcd;

    setup_wall_struct(&tcd, dda);;
	while (tcd.iterator < tcd.sky_lineH)
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, bt_color[1]);
	while (tcd.iterator < tcd.wall_lineH)
		wall_drawing(imgs, dda, &tcd);
	while (tcd.iterator < SCREEN_HEIGHT)
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, bt_color[0]);
       //floor_drawing(imgs->floor_texture, &tcd, dda, playerpos, imgs->img_3d);
}