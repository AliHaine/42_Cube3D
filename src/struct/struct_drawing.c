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

void setup_wall_struct(t_wall_drawing *twd, float wall_height, float dist)
{
	int convertor ;

	convertor = (64 * SCREEN_HEIGHT) / dist;
	twd->lineH = ((SCREEN_HEIGHT + wall_height) / 2);
	twd->step = 64.0f / (float)convertor;
	twd->current_step = 0.0f;
	if (twd->lineH > SCREEN_HEIGHT) {
		twd->current_step = (convertor - SCREEN_HEIGHT) / 2.0;
		twd->lineH = SCREEN_HEIGHT;
	}
	twd->current_step *= twd->step;
}
