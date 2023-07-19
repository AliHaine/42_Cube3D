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

void setup_wall_struct(t_col_drawing *twd, t_dda *dda)
{
	int convertor ;

	convertor = (64 * SCREEN_HEIGHT) / dda->dist_hv[0];
    twd->iterator = 0;
    twd->sky_lineH = (SCREEN_HEIGHT - dda->wall_height) / 2;
	twd->wall_lineH = (SCREEN_HEIGHT + dda->wall_height) / 2;
	twd->step = 64.0f / (float)convertor;
	twd->current_step = 0.0f;
	if (twd->wall_lineH > SCREEN_HEIGHT) {
		twd->current_step = (convertor - SCREEN_HEIGHT) / 2.0;
		twd->wall_lineH = SCREEN_HEIGHT;
	}
	twd->current_step *= twd->step;
    if (dda->hit_hv == 1 && dda->hit_direction[0] == 3)
        dda->r_xy[1] = 63 - ((int)dda->r_xy[1] % 64);
    else if (dda->hit_hv == 0 && dda->hit_direction[1] == 2)
        dda->r_xy[0] = 63 - ((int)dda->r_xy[0] % 64);
}
