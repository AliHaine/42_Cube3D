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

void	draw_energy_bar(mlx_image_t *img, short energy)
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
        draw_pixel_to_img(img, ti, full_color);
        if (energy < 100)
        {
            if (ti.c == 9 || ti.c == 2)
                ti.a += 4;
            ti.a -= 100 * 4.3;
            ti.a = abs(ti.a);
            ti.b += energy * 4.3;
            draw_pixel_to_img(img, ti, empty_color);
        }
        ti.b = 3;
        ti.c++;
        ti.a = energy * 4.3;
    }
}

static void wall_drawing(t_imgs *imgs, t_dda *dda, t_wall_drawing *twd)
{
    if (dda->hit_hv == 1 && dda->hit_direction[0] == 1)
        get_color_from_wall_texture(imgs->wall_texture[1], (int)dda->r_xy[1], twd);
    else if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
        get_color_from_wall_texture(imgs->wall_texture[3], (int)dda->r_xy[1], twd);
    else if (dda->hit_hv == 0 && dda->hit_direction[1] == 0)
        get_color_from_wall_texture(imgs->wall_texture[0], (int)dda->r_xy[0], twd);
    else
        get_color_from_wall_texture(imgs->wall_texture[2], (int)dda->r_xy[0], twd);
    mlx_put_pixel(imgs->img_3d, dda->ray, twd->iterator++, twd->color);
    twd->current_step += twd->step;
}

static void floor_drawing(mlx_texture_t *floor_texture, t_wall_drawing *twd, t_dda *dda, float playerpos[2])
{
    //todo
}

void	columns_drawing(t_imgs *imgs, t_dda *dda, uint32_t bt_color[2], float playerpos[2])
{
    t_wall_drawing  twd;

    setup_wall_struct(&twd, dda);
	while (twd.iterator < twd.sky_lineH)
		mlx_put_pixel(imgs->img_3d, dda->ray, twd.iterator++, bt_color[1]);
    //printf("i = %d\n", i);
	while (twd.iterator < twd.wall_lineH)
		wall_drawing(imgs, dda, &twd);
    //printf("%d\n", i);
	while (twd.iterator < SCREEN_HEIGHT)
        //printf("so\n");
       floor_drawing(imgs->floor_texture, &twd, dda, playerpos);
		//mlx_put_pixel(imgs->img_3d, dda->ray, twd.iterator++, bt_color[0]);
}