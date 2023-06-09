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

static void	jump_to_next(t_dda *dda, const float o_xy[2], char **map, const float playerpos[2], bool val, int max)
{
	int	m_xy[2];

	while (1)
	{
		m_xy[0] = (int)dda->r_xy[0] / 64;
		m_xy[1] = (int)dda->r_xy[1] / 64;
		if (m_xy[val] > max || dda->r_xy[val] < 0) {
			break;
		}
		if (map[m_xy[1]][m_xy[0]] == '1')
		{
			dda->dist_hv[val] = dda->cos * (dda->r_xy[0] - playerpos[0])
					- -dda->sin * (dda->r_xy[1] - playerpos[1]);
			break ;
		}
		dda->r_xy[0] += o_xy[0];
		dda->r_xy[1] += o_xy[1];
	}
}

static void	horizontal_cast(t_dda *dda, t_player player, char **map, t_core *core)
{
	float	tan;
	float	o_xy[2];

	tan = -1.0f / tanf(dda->current_angle);
	dda->r_xy[0] = player.playerpos[0];
	dda->r_xy[1] = player.playerpos[1];
	if (dda->sin > 0.001) //look down
	{
		dda->r_xy[1] = ((int)(player.playerpos[1] / 64) * 64) + 64;
		dda->r_xy[0] = (player.playerpos[1] - dda->r_xy[1]) * tan + player.playerpos[0];
		o_xy[1] = 64;
		o_xy[0] = -o_xy[1] * tan;
		dda->hit_direction[1] = 2;

	}
	else if (dda->sin < -0.001) //look up
	{
		dda->r_xy[1] = ((int)(player.playerpos[1] / 64) * 64) - 0.0001;
		dda->r_xy[0] = (player.playerpos[1] - dda->r_xy[1]) * tan + player.playerpos[0];
		o_xy[1] = -64;
		o_xy[0] = -o_xy[1] * tan;
		dda->hit_direction[1] = 0;
	}

	if (dda->hit_direction[1] >= 0)
		jump_to_next(dda, o_xy, map, player.playerpos, 0, core->consts.map_width);
}

static void	vertical_cast(t_dda *dda, t_player player, char **map, t_core *core)
{
	float	tan;
	float	o_xy[2];

	tan = -tanf(dda->current_angle);
	dda->r_xy[0] = player.playerpos[0];
	dda->r_xy[1] = player.playerpos[1];
	if (dda->cos > 0.001) //look right
	{
		dda->r_xy[0] = ((int)(player.playerpos[0] / 64) * 64) + 64;
		dda->r_xy[1] = (player.playerpos[0] - dda->r_xy[0]) * tan + player.playerpos[1];
		o_xy[0] = 64;
		o_xy[1] = -o_xy[0] * tan;
		dda->hit_direction[0] = 1;
	}
	else if (dda->cos < -0.001) //look left
	{
		dda->r_xy[0] = ((int)(player.playerpos[0] / 64) * 64) - 0.0001;
		dda->r_xy[1] = (player.playerpos[0] - dda->r_xy[0]) * tan + player.playerpos[1];
		o_xy[0] = -64;
		o_xy[1] = -o_xy[0] * tan;
		dda->hit_direction[0] = 3;
	}
	if (dda->hit_direction[0] > 0)
		jump_to_next(dda, o_xy, map, player.playerpos, 1, core->consts.map_height);
	dda->v_xy[0] = dda->r_xy[0];
	dda->v_xy[1] = dda->r_xy[1];
}

void	raycasting(t_core *core)
{
	float start_angle;
	t_dda dda;

	dda.ray = -1;
	start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (dda.ray++ < RAY_NUMBER)
	{
		dda.hit_direction[0] = -1;
		dda.hit_direction[1] = -1;
		dda.dist_hv[0] = 10000;
		dda.dist_hv[1] = 10000;
        dda.hit_hv = 0;
		dda.current_angle = start_angle + (dda.ray * core->consts.dist_between_ray);
		if (dda.current_angle < 0)
			dda.current_angle += 6.28319f;
		if (dda.current_angle > 6.28319f)
			dda.current_angle -= 6.28319f;
		dda.cos = cosf(dda.current_angle);
		dda.sin = sinf(dda.current_angle);
		vertical_cast(&dda, core->player, core->consts.map, core);
		horizontal_cast(&dda, core->player, core->consts.map, core);
		if (dda.dist_hv[1] < dda.dist_hv[0])
		{
			dda.r_xy[0] = dda.v_xy[0];
			dda.r_xy[1] = dda.v_xy[1];
			dda.dist_hv[0] = dda.dist_hv[1];
			dda.hit_hv = 1;
		}
		fisheyes_fixor(&dda, core->player.playerangle);
		columns_drawing(core, &dda);
	}

}
