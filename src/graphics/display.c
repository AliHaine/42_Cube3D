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
	while (++py < ((core->consts.map_height + 1) * 64) / core->consts.minimap_size
		&& py / (64 / core->consts.minimap_size) < core->consts.map_height + 1
		&& py < SCREEN_HEIGHT)
	{
		px = -1;
		while (++px < ((core->consts.map_width) * 64) / core->consts.minimap_size
			&& px / (64 / core->consts.minimap_size) < core->consts.map_width
			&& px < SCREEN_WIDTH)
		{
			if (core->consts.map[py / (64 / core->consts.minimap_size)][px / (64 / core->consts.minimap_size)] == '0'
				|| is_player_char(core->consts.map[py / (64 / core->consts.minimap_size)]
				[px / (64 / core->consts.minimap_size)]))
				mlx_put_pixel(core->consts.img_map, px, py,
					core->consts.minimap_floor_color);
			else if (core->consts.map[py / (64 / core->consts.minimap_size)]
				[px / (64 / core->consts.minimap_size)] == '1')
				mlx_put_pixel(core->consts.img_map, px, py,
					core->consts.minimap_wall_color);
		}
	}
}

void	display(void *params)
{
	t_core	*core;

	core = (t_core *) params;
	mlx_delete_image(core->mlx, core->consts.img_map);
	mlx_delete_image(core->mlx, core->consts.img_3d);
	core->consts.img_player->instances[0].x = ((core->player.playerpos[0]
				/ core->consts.minimap_size) - (MINIMAP_PLAYER_SIZE / 2)) + 10;
	core->consts.img_player->instances[0].y = ((core->player.playerpos[1]
				/ core->consts.minimap_size) - (MINIMAP_PLAYER_SIZE / 2)) + 10;
	core->consts.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->consts.img_map = mlx_new_image(core->mlx, (int)
			((core->consts.map_width * 64) / core->consts.minimap_size), (int)
			(((core->consts.map_height + 1) * 64) / core->consts.minimap_size));
	draw_map(core);
	raycast(core);
	mlx_image_to_window(core->mlx, core->consts.img_3d, 0, 0);
	mlx_image_to_window(core->mlx, core->consts.img_map, 10, 10);
	core->consts.img_3d->instances[0].z = 1;
	core->consts.img_map->instances[0].z = 2;
	core->consts.img_player->instances[0].z = 3;
}
