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

/*static int	get_chunk_from_pos2(int x, int y, int m_height, int m_width, int val, t_dda *dda)
{
    int i;

    i = 0;
    //printf("start %d %d %d %d\n-------------------------\n", x, y, val, dda->ray);
    if (y < m_height)
    {
        while (i++ < 4)
        {
            if (x < m_width * i)
                return (i - 1);
        }
    }
    else if (y < m_height * 2)
    {
        while (i++ < 4)
        {
            if (x < m_width * i)
                return ((i - 1) + 3);
        }
    }
    else
    {
        while (i++ < 4)
        {
            if (x < m_width * i)
                return ((i - 1) + 6);
        }
    }
    //printf("rien %d %d %d %d\n-------------------------\n", x, y, val, dda->ray);
    return (4);
}*/

static void	jump_to_next(t_dda *dda, t_map *map, const float playerpos[2], bool val, int max)
{
	int	m_xy[2];

	while (1)
	{
		m_xy[0] = (int)dda->r_xy[0] / 64;
		m_xy[1] = (int)dda->r_xy[1] / 64;
		dda->chunk = get_chunk_from_pos(m_xy[0], m_xy[1], map->height, map->width);
		if (m_xy[val] >= max || dda->r_xy[val] < 0 || map->world[dda->chunk][m_xy[1] % map->height][m_xy[0] % map->width] == ' ')
			break ;
		if (map->world[dda->chunk][m_xy[1] % map->height][m_xy[0] % map->width] != '0')
		{
			dda->dist_hv[val] = dda->cos * (dda->r_xy[0] - playerpos[0])
					- -dda->sin * (dda->r_xy[1] - playerpos[1]);
			break ;
		}
		dda->r_xy[0] += dda->o_xy[0];
		dda->r_xy[1] += dda->o_xy[1];
	}
}

static void	horizontal_cast(t_dda *dda, float playerpos[2],t_map *map)
{
	float	tan;

	tan = -1.0f / tanf(dda->current_angle);
	dda->r_xy[0] = playerpos[0];
	dda->r_xy[1] = playerpos[1];
	if (dda->sin > 0.001) //look down
	{
		dda->r_xy[1] = ((int)(playerpos[1] / 64) * 64) + 64;
		dda->r_xy[0] = (playerpos[1] - dda->r_xy[1]) * tan + playerpos[0];
		dda->o_xy[1] = 64;
		dda->o_xy[0] = -dda->o_xy[1] * tan;
		dda->hit_direction[1] = 2;
	}
	else if (dda->sin < -0.001) //look up
	{
		dda->r_xy[1] = ((int)(playerpos[1] / 64) * 64) - 0.0002;
		dda->r_xy[0] = (playerpos[1] - dda->r_xy[1]) * tan + playerpos[0];
		dda->o_xy[1] = -64;
		dda->o_xy[0] = -dda->o_xy[1] * tan;
		dda->hit_direction[1] = 0;
	}
	if (dda->hit_direction[1] >= 0)
		jump_to_next(dda, map, playerpos, 0, map->width * 3);
}

static void	vertical_cast(t_dda *dda, float playerpos[2], t_map *map)
{
	float	tan;

	tan = -tanf(dda->current_angle);
	dda->r_xy[0] = playerpos[0];
	dda->r_xy[1] = playerpos[1];
	if (dda->cos > 0.001) //look right
	{
		dda->r_xy[0] = ((int)(playerpos[0] / 64) * 64) + 64;
		dda->r_xy[1] = (playerpos[0] - dda->r_xy[0]) * tan + playerpos[1];
		dda->o_xy[0] = 64;
		dda->o_xy[1] = -dda->o_xy[0] * tan;
		dda->hit_direction[0] = 1;
	}
	else if (dda->cos < -0.001) //look left
	{
		dda->r_xy[0] = ((int)(playerpos[0] / 64) * 64) - 0.0002;
		dda->r_xy[1] = (playerpos[0] - dda->r_xy[0]) * tan + playerpos[1];
		dda->o_xy[0] = -64;
		dda->o_xy[1] = -dda->o_xy[0] * tan;
		dda->hit_direction[0] = 3;
	}
	if (dda->hit_direction[0] > 0)
		jump_to_next(dda, map, playerpos, 1, map->height * 3);
	dda->v_xy[0] = dda->r_xy[0];
	dda->v_xy[1] = dda->r_xy[1];
}

void	raycasting(t_player *player, t_imgs *imgs, t_map *map, t_block **blocks)
{
	float start_angle;
	t_dda dda;

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
		vertical_cast(&dda, player->player_pos_xy, map);
		horizontal_cast(&dda, player->player_pos_xy, map);
		if (dda.dist_hv[1] < dda.dist_hv[0])
		{
			dda.r_xy[0] = dda.v_xy[0];
			dda.r_xy[1] = dda.v_xy[1];
			dda.dist_hv[0] = dda.dist_hv[1];
			dda.hit_hv = 1;
		}
		fisheyes_fixor(&dda, player->playerangle);
		dda.wall_height = (SCREEN_HEIGHT * 64) / dda.dist_hv[0];
		if (dda.dist_hv[0] > dda.dist_hv[1])
			dda.wall_height = (SCREEN_HEIGHT * 64) / dda.dist_hv[1];
		columns_drawing(imgs, &dda, map, blocks, player);
	}
}
