/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:51 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:47:54 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

void	draw_map(t_core *core)
{
	int	py;
	int	px;

	py = -1;
	while (++py < SCREEN_HEIGHT)
	{
		px = -1;
		while (++px < SCREEN_WIDTH)
		{
			if (core->consts.map[(py / 64)][(px / 64)] != '1')
				continue ;
			mlx_put_pixel(core->consts.img_map, px, py,
				core->consts.wall_color);
		}
	}
}

void	display(void *params)
{
	t_core	*core;

	core = (t_core *) params;
	mlx_delete_image(core->mlx, core->consts.img_dot);
	mlx_delete_image(core->mlx, core->consts.img_map);
	core->consts.img_map = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->consts.img_dot = mlx_texture_to_image(core->mlx,
			core->consts.texture_dot);
	draw_map(core);
	raycast(core);
	mlx_image_to_window(core->mlx, core->consts.img_map, 0, 0);
	mlx_image_to_window(core->mlx, core->consts.img_dot,
		core->player.playerpos[0] - 7.5, core->player.playerpos[1] - 7.5);
	core->consts.img_map->instances[0].z = 1;
	core->consts.img_dot->instances[0].z = 2;
}
