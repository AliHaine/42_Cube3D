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

void setup_col_struct(t_col_drawing *tcd, t_dda *dda, t_world *world, t_block **blocks)
{
	int convertor;

	convertor = (64 * SCREEN_HEIGHT) / dda->dist_hv[0];
	tcd->iterator = 0;
	tcd->ceil_floor_lineH = (SCREEN_HEIGHT - dda->wall_height) / 2;
	tcd->wall_lineH = 0;
	if (dda->wall_height != 0)
		tcd->wall_lineH = (SCREEN_HEIGHT + dda->wall_height) / 2;
	tcd->step = 64.0f / (float)convertor;
	tcd->current_step = 0.0f;
	tcd->fog_strength = dda->dist_hv[0] / FOG_DISTANCE;
    if (dda->chunk_hv[0] < 0) //todo probleme n'est pas cense arrive (si aucun bloc)
        dda->chunk_hv[0] = 0;
	tcd->hit_block = world->world[dda->chunk_hv[0]][((int)dda->r_xy[1] / 64) % world->height][((int)dda->r_xy[0] / 64) % world->width];
    if (tcd->hit_block != '1') {
		tcd->block = get_block_from_char(blocks, tcd->hit_block);
		if (!tcd->block) {
			//printf("chunk: %d disth: %f distv: %f ry: %d rx: %d vx: %d vy: %d\n", dda->chunk_hv[0], dda->dist_hv[0], dda->dist_hv[1], ((int)dda->r_xy[1] / 64) % world->height, ((int)dda->r_xy[0] / 64) % world->width, (int)dda->v_xy[0] / 64 % world->width, (int)dda->v_xy[1] / 64 % world->width);
			tcd->hit_block = '1';
		}
	}
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
