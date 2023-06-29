/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_differential_analysis.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:14:36 by ayagmur           #+#    #+#             */
/*   Updated: 2023/06/30 00:14:38 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	horizontal_cast(t_dda *dda, t_player player, char **map, t_core *core)
{
	float tan;
	bool hit;
	float o_xy[2];

	tan = -1.0 / tanf(dda->current_angle);
	hit = true;
	if (dda->sin > 0.001) //look down
	{
		dda->r_xy[1] = ((int)(player.playerpos[1] / 64) * 64) + 64;
		dda->r_xy[0] = ((int)player.playerpos[1] - dda->r_xy[1]) * tan + player.playerpos[0];
		//if (dda->r_xy[0] > 0 && dda->r_xy[0] < SCREEN_WIDTH)
		//	mlx_put_pixel(core->imgs.img_map, dda->r_xy[0]/ MINIMAP_SIZE, dda->r_xy[1]/ MINIMAP_SIZE,(0 << 24) + (255 << 16) + (255 << 8) + 255);

		o_xy[1] = 64;
		o_xy[0] = -o_xy[1] * tan;

	}
	else if (dda->sin < -0.001) //look up
	{
		dda->r_xy[1] = ((int)(player.playerpos[1] / 64) * 64) - 0.0001;
		dda->r_xy[0] = ((int)player.playerpos[1] - dda->r_xy[1]) * tan + player.playerpos[0];
		//if (dda->r_xy[0] > 0 && dda->r_xy[0] < SCREEN_WIDTH)
		//	mlx_put_pixel(core->imgs.img_map, dda->r_xy[0]/ MINIMAP_SIZE, dda->r_xy[1]/ MINIMAP_SIZE, (0 << 24) + (255 << 16) + (0 << 8) + 255);
		o_xy[1] = -64;
		o_xy[0] = -o_xy[1] * tan;
	}
	else
	{
		dda->r_xy[0] = player.playerpos[0];
		dda->r_xy[1] = player.playerpos[1];
		hit = false;
	}

	while (hit)
	{
		dda->m_xy[0] = dda->r_xy[0] / 64;
		dda->m_xy[1] = dda->r_xy[1] / 64;
		if (dda->r_xy[0] >= SCREEN_WIDTH || dda->r_xy[0] < 0)
			break;
		if (map[dda->m_xy[1]][dda->m_xy[0]] == '1')
		{

			dda->dist_vh[1] = dda->cos * (dda->r_xy[0] - player.playerpos[0]) - -sin(dda->current_angle) * (dda->r_xy[1] - player.playerpos[1]);
			//mlx_put_pixel(core->consts.img_map, rx, ry,(255 << 24) + (80 << 16) + (255 << 8) + 255);
			break ;
		}
		dda->r_xy[0] += o_xy[0];
		dda->r_xy[1] += o_xy[1];
	}
}

void	vertical_cast(t_dda *dda, t_player player, char **map, t_core *core)
{
	float tan;
	bool hit;
	float o_xy[2];

	tan = -tanf(dda->current_angle);
	hit = true;
	if (dda->cos > 0.001) //look right
	{
		dda->r_xy[0] = ((int)(player.playerpos[0] / 64) * 64) + 64;
		dda->r_xy[1] = ((int)player.playerpos[0] - dda->r_xy[0]) * tan + player.playerpos[1];
		//if (dda->r_xy[1] > 0 && dda->r_xy[1] < SCREEN_HEIGHT)
		//	mlx_put_pixel(core->imgs.img_map, dda->r_xy[0]/ MINIMAP_SIZE, dda->r_xy[1]/ MINIMAP_SIZE,(0 << 24) + (255 << 16) + (255 << 8) + 255);
		o_xy[0] = 64;
		o_xy[1] = -o_xy[0] * tan;
	}
	else if (dda->cos < -0.001) //look left
	{
		dda->r_xy[0] = ((int)(player.playerpos[0] / 64) * 64) - 0.0001;
		dda->r_xy[1] = ((int)player.playerpos[0] - dda->r_xy[0]) * tan + player.playerpos[1];
		//if (dda->r_xy[1] < SCREEN_HEIGHT && dda->r_xy[1] > 0)
		//	mlx_put_pixel(core->imgs.img_map, dda->r_xy[0] / MINIMAP_SIZE, dda->r_xy[1] / MINIMAP_SIZE, (0 << 24) + (255 << 16) + (0 << 8) + 255);
		o_xy[0] = -64;
		o_xy[1] = -o_xy[0] * tan;
	}
	else
	{
		dda->r_xy[0] = player.playerpos[0];
		dda->r_xy[1] = player.playerpos[1];
		hit = false;
	}

	while (hit)
	{
		dda->m_xy[0] = (int)dda->r_xy[0] / 64;
		dda->m_xy[1] = (int)dda->r_xy[1] / 64;
		if (dda->r_xy[1] >= SCREEN_HEIGHT || dda->r_xy[1] < 0)
			break ;
		if (map[dda->m_xy[1]][dda->m_xy[0]] == '1')
		{
			dda->dist_vh[0] = dda->cos * (dda->r_xy[0] - player.playerpos[0]) - -sin(dda->current_angle) * (dda->r_xy[1] - player.playerpos[1]);
			//mlx_put_pixel(core->consts.img_map, rx, ry,(0 << 24) + (255 << 16) + (255 << 8) + 255);
			break ;
		}
		dda->r_xy[0] += o_xy[0];
		dda->r_xy[1] += o_xy[1];
	}
	dda->v_xy[0] = dda->r_xy[0];
	dda->v_xy[1] = dda->r_xy[1];
}

void	raycasting(t_core *core)
{
	int ray;
	float start_angle;
	t_dda dda;

	ray = -1;
	start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (ray++ < RAY_NUMBER)
	{
		dda.dist_vh[0] = 10000;
		dda.dist_vh[1] = 10000;
		dda.current_angle = start_angle + (ray * core->consts.dist_between_ray);
		if (dda.current_angle < 0)
			dda.current_angle += 6.28319;
		if (dda.current_angle > 6.28319)
			dda.current_angle -= 6.28319;
		dda.cos = cos(dda.current_angle);
		dda.sin = sin(dda.current_angle);
		vertical_cast(&dda, core->player, core->consts.map, core);
		horizontal_cast(&dda, core->player, core->consts.map, core);
		if (dda.dist_vh[0] < dda.dist_vh[1])
		{
			dda.r_xy[0] = dda.v_xy[0];
			dda.r_xy[1] = dda.v_xy[1];
			dda.dist_vh[1] = dda.dist_vh[0];
		}
		if (dda.r_xy[0] > 0 && dda.r_xy[0] < SCREEN_WIDTH && dda.r_xy[1] > 0 && dda.r_xy[1] < SCREEN_HEIGHT)
		{
			mlx_put_pixel(core->imgs.img_map, dda.r_xy[0] / MINIMAP_SIZE, dda.r_xy[1] / MINIMAP_SIZE,
						  (255 << 24) + (255 << 16) + (0 << 8) + 255);
		}
	}

}
