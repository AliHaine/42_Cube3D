/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:47:12 by ayagmur           #+#    #+#             */
/*   Updated: 2023/07/14 12:47:14 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void setup_col_struct(t_col_drawing *tcd, t_dda *dda, t_map *map, t_block *blocks)
{
	int convertor;

	convertor = (64 * SCREEN_HEIGHT) / dda->dist_hv[0];
	tcd->iterator = 0;
	tcd->ceil_floor_lineH = (SCREEN_HEIGHT - dda->wall_height) / 2;
	tcd->wall_lineH = (SCREEN_HEIGHT + dda->wall_height) / 2;
	tcd->step = 64.0f / (float)convertor;
	tcd->current_step = 0.0f;
	tcd->fog_strength = dda->dist_hv[0] / FOG_DISTANCE;
	tcd->hit_block = map->world[(int)dda->r_xy[1] / 64][(int)dda->r_xy[0] / 64];
	tcd->block = &blocks[0];
	if (tcd->wall_lineH > SCREEN_HEIGHT) {
		tcd->current_step = (convertor - SCREEN_HEIGHT) / 2.0;
		tcd->wall_lineH = SCREEN_HEIGHT;
	}
	tcd->current_step *= tcd->step;
    if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
        dda->r_xy[1] = 63 - ((int)dda->r_xy[1] % 64);
    else if (dda->hit_hv == 0 && dda->hit_direction[1] == 2)
        dda->r_xy[0] = 63 - ((int)dda->r_xy[0] % 64);
}
