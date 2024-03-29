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

#include "../../../includes/includes.h"

static void	jump_to_next(t_dda *dda, const float playerpos[2], bool val)
{
	int		m_xy[2];
	t_world	*world;

	world = get_world_active();
	while (1)
	{
		m_xy[0] = (int)dda->r_xy[0] / 64;
		m_xy[1] = (int)dda->r_xy[1] / 64;
		dda->chunk_hv[val] = get_chunk_from_pos(m_xy[0], m_xy[1]);
		if (m_xy[0] >= (world->width * 3) || m_xy[1] >= (world->height * 3) || dda->r_xy[0] < 0 || dda->r_xy[1] < 0 || world->world[dda->chunk_hv[val]][m_xy[1] % world->height][m_xy[0] % world->width] == ' ')
			break ;
		if (world->world[dda->chunk_hv[val]][m_xy[1] % world->height][m_xy[0] % world->width] != '0')
		{
			dda->dist_hv[val] = dda->cos * (dda->r_xy[0] - playerpos[0])
				- -dda->sin * (dda->r_xy[1] - playerpos[1]);
			break ;
		}
		dda->r_xy[0] += dda->o_xy[0];
		dda->r_xy[1] += dda->o_xy[1];
	}
}

static void	horizontal_cast(t_dda *dda, float playerpos[2])
{
	float	tan;

	tan = -1.0f / tanf(dda->current_angle);
	dda->r_xy[0] = playerpos[0];
	dda->r_xy[1] = playerpos[1];
	if (dda->sin > 0.001)
	{
		dda->r_xy[1] = ((int)(playerpos[1] / 64) *64) + 64;
		dda->r_xy[0] = (playerpos[1] - dda->r_xy[1]) * tan + playerpos[0];
		dda->o_xy[1] = 64;
		dda->o_xy[0] = -dda->o_xy[1] * tan;
		dda->hit_direction[1] = 2;
	}
	else if (dda->sin < -0.001)
	{
		dda->r_xy[1] = ((int)(playerpos[1] / 64) *64) - 0.0002;
		dda->r_xy[0] = (playerpos[1] - dda->r_xy[1]) * tan + playerpos[0];
		dda->o_xy[1] = -64;
		dda->o_xy[0] = -dda->o_xy[1] * tan;
		dda->hit_direction[1] = 0;
	}
	if (dda->hit_direction[1] >= 0)
		jump_to_next(dda, playerpos, 0);
}

static void	vertical_cast(t_dda *dda, float playerpos[2])
{
	float	tan;

	tan = -tanf(dda->current_angle);
	dda->r_xy[0] = playerpos[0];
	dda->r_xy[1] = playerpos[1];
	if (dda->cos > 0.001)
	{
		dda->r_xy[0] = ((int)(playerpos[0] / 64) *64) + 64;
		dda->r_xy[1] = (playerpos[0] - dda->r_xy[0]) * tan + playerpos[1];
		dda->o_xy[0] = 64;
		dda->o_xy[1] = -dda->o_xy[0] * tan;
		dda->hit_direction[0] = 1;
	}
	else if (dda->cos < -0.001)
	{
		dda->r_xy[0] = ((int)(playerpos[0] / 64) *64) - 0.0002;
		dda->r_xy[1] = (playerpos[0] - dda->r_xy[0]) * tan + playerpos[1];
		dda->o_xy[0] = -64;
		dda->o_xy[1] = -dda->o_xy[0] * tan;
		dda->hit_direction[0] = 3;
	}
	if (dda->hit_direction[0] > 0)
		jump_to_next(dda, playerpos, 1);
	dda->v_xy[0] = dda->r_xy[0];
	dda->v_xy[1] = dda->r_xy[1];
}

void	raycasting(t_player *player, t_imgs *imgs, t_options *options)
{
	float		start_angle;
	float		dists[SCREEN_WIDTH];
	t_dda		dda;

	dda.ray = -1;
	start_angle = player->playerangle - (FOV / 2);
	while (dda.ray++ < RAY_NUMBER - 1)
	{
		dda.hit_direction[0] = -1;
		dda.hit_direction[1] = -1;
		dda.dist_hv[0] = 100000;
		dda.dist_hv[1] = 100000;
		dda.hit_hv = 0;
		dda.current_angle = start_angle + (dda.ray * DIST_BETWEEN_RAY);
		if (dda.current_angle < 0)
			dda.current_angle += 6.28319f;
		if (dda.current_angle > 6.28319f)
			dda.current_angle -= 6.28319f;
		dda.cos = cosf(dda.current_angle);
		dda.sin = sinf(dda.current_angle);
		vertical_cast(&dda, player->player_pos_xy);
		horizontal_cast(&dda, player->player_pos_xy);
		if (dda.dist_hv[1] < dda.dist_hv[0])
		{
			dda.r_xy[0] = dda.v_xy[0];
			dda.r_xy[1] = dda.v_xy[1];
			dda.dist_hv[0] = dda.dist_hv[1];
			dda.hit_hv = 1;
			dda.chunk_hv[0] = dda.chunk_hv[1];
		}
		dists[dda.ray] = dda.dist_hv[dda.hit_hv];
		fisheyes_fixor(&dda, player->playerangle);
		columns_drawing(imgs, &dda, player, options);
	}
	draw_sprites(player, imgs, dists);
}
