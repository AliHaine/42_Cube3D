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

/*static void	get_nether_portal(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd)
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
}*/

static void wall_drawing(t_imgs *imgs, t_dda *dda, t_col_drawing *tcd, t_block *block)
{
	if (tcd->fog_strength > 1)
		tcd->color = (0 << 24) | (0 << 16) | (0 << 8) | 255;
	else if (tcd->hit_block != '1')
		get_color_block_texture(block->image, dda, tcd);
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
			else if (map->world[case_y][case_x] == '1')
				mlx_put_pixel(imgs->img_map, px, py, wall_color);
		}
	}
}

void	get_color_from_floor_texture(mlx_texture_t *wall_texture, int r, t_col_drawing *tcd)
{
	int			value;

	//value = ((r % 64) + ((int)tcd->cstep * (int)wall_texture->height)) * 4;
	if (value >= 16384)
		return ;
	tcd->color = get_rgb_color(wall_texture->pixels[value],wall_texture->pixels[value + 1]
			,wall_texture->pixels[value + 2],wall_texture->pixels[value + 3]);
}

uint32_t	get_color(mlx_texture_t *texture, const int xy[2])
{
    int		total_step;
    uint8_t	r;
    uint8_t	g;
    uint8_t	b;


    total_step = (xy[0] + xy[1]) * 4;
    r = texture->pixels[total_step];
    g = texture->pixels[total_step + 1];
    b = texture->pixels[total_step + 2];
    return ((r << 24) | (g << 16) | (b << 8) | 255);
}

static void floor_drawing(mlx_texture_t *floor_texture, t_col_drawing *tcd, t_dda *dda, float playerpos[2], mlx_image_t *i3)
{
	double dirX = dda->cos,
	dirY = dda->sin,
	planeX = dda->o_xy[0],
	planeY = dda->o_xy[1]; //the 2d raycaster version of camera plane

// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
	float rayDirX0 = dirX - planeX;
	float rayDirY0 = dirY - planeY;
	float rayDirX1 = dirX + planeX;
	float rayDirY1 = dirY + planeY;

	// Current y position compared to the center of the screen (the horizon)
	int p = tcd->iterator - SCREEN_HEIGHT / 2;

	// Vertical position of the camera.
	float posZ = 0.5 * SCREEN_HEIGHT;

	// Horizontal distance from the camera to the floor for the current row.
	// 0.5 is the z position exactly in the middle between floor and ceiling.
	float rowDistance = posZ / p;

	// calculate the real world step vector we have to add for each x (parallel to camera plane)
	// adding step by step avoids multiplications with a weight in the inner loop
	float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
	float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;

	// real world coordinates of the leftmost column. This will be updated as we step to the right.
	float floorX = playerpos[0] + rowDistance * rayDirX0;
	float floorY = playerpos[1] + rowDistance * rayDirY0;

	static bool f = true;

	for(int x = 0; x < SCREEN_WIDTH; ++x)
	{
		// the cell coord is simply got from the integer parts of floorX and floorY
		int cellX = (int)(floorX);
		int cellY = (int)(floorY);

		// get the texture coordinate from the fractional part
		int tx = (int)(64 * (floorX - cellX)) & (64 - 1);
		int ty = (int)(64 * (floorY - cellY)) & (64 - 1);

		floorX += floorStepX;
		floorY += floorStepY;
		if (dda->ray == 1) {
			if (f)
				printf("fx %d, fy %d %d %d \n", tx, ty, cellX, cellY);
			f = false;
		} else
			f = true;

		// choose texture and draw the pixel
		int floorTexture = 3;
		int ceilingTexture = 6;
		uint32_t color;

		// floor
		/*color = texture[floorTexture][64 * ty + tx];
		color = (color >> 1) & 8355711; // make a bit darker
		buffer[y][x] = color;

		//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
		color = texture[ceilingTexture][64 * ty + tx];
		color = (color >> 1) & 8355711; // make a bit darker
		buffer[SCREEN_HEIGHT - y - 1][x] = color;*/
	}



    /*double distPlayer = 0.0;
    int texture_xy[2];

    // Calcule la distance actuelle par rapport à la caméra
    float currentDist = SCREEN_HEIGHT / (2.0 * tcd->iterator - SCREEN_HEIGHT);

    // Calcule le poids pour interpoler entre la position actuelle du rayon et la position du joueur
    float weight = (currentDist - distPlayer) / (dda->dist_hv[0] - distPlayer);

    // Calcule les coordonnées actuelles sur le sol en fonction du poids
    float currentFloorX = weight * dda->r_xy[0] + (1.0 - weight) * playerpos[0];
    float currentFloorY = weight * dda->r_xy[1] + (1.0 - weight) * playerpos[1];

    // Obtient les coordonnées de la texture pour le sol
    texture_xy[0] = (int)(currentFloorX * 64) % 64;
    texture_xy[1] = (int)(currentFloorY * 64) % 64;
    static bool y = true;
    if (dda->ray == 0)
    {
        if (y == true)
            //printf("%d %d\n", texture_xy[0], texture_xy[1]);
        y = false;
    } else
        y = true;
    // Obtient la couleur à partir de la texture et de la distance pour le dessin du sol
    //color = get_color(floor_texture, currentDist / FOG_DISTANCE, texture_xy);
    tcd->color = get_color(floor_texture ,texture_xy);

    // Dessine le pixel du sol
    mlx_put_pixel(i3, dda->ray, tcd->iterator, tcd->color);*/
	tcd->iterator++;
}

void	columns_drawing(t_imgs *imgs, t_dda *dda, t_map *map, t_block *blocks, t_player *player)
{
    t_col_drawing  tcd;

	setup_col_struct(&tcd, dda, map, blocks);
	while (tcd.iterator < tcd.ceil_floor_lineH)
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, map->bt_color[1]);
	while (tcd.iterator < tcd.wall_lineH)
		wall_drawing(imgs, dda, &tcd, &blocks[0]);
	while (tcd.iterator < SCREEN_HEIGHT)
		//floor_drawing(imgs->floor_texture, &tcd, dda, player->playerpos, imgs->img_3d);
		mlx_put_pixel(imgs->img_3d, dda->ray, tcd.iterator++, map->bt_color[0]);
}
