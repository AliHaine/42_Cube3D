/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:42 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:47:45 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"
#include "../includes/defines.h"

static t_core	*core_init(t_core *core)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	core->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	core->consts.img_map = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->consts.texture_dot = mlx_load_png("assets/red_dot.png");
	core->consts.img_dot = mlx_texture_to_image(core->mlx,
			core->consts.texture_dot);
	core->consts.wall_color = (150 << 24) + (150 << 16) + (150 << 8) + 255;
	core->consts.ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 255;
	core->consts.fov = FOV * (PI / 180);
	core->consts.dist_between_ray = core->consts.fov / RAY_NUMBER;
	return (core);
}

int	main(int argc, char *argv[])
{
	t_core	core;

	if (argc != 2)
		msg_write(2, 1, ERROR_ARGS);
	core_init(&core);
	map_manager(argv[1], &core);
	mlx_loop_hook(core.mlx, &display, &core);
	mlx_loop_hook(core.mlx, &inputs, &core);
	mlx_loop(core.mlx);
	mlx_delete_image(core.mlx, core.consts.img_map);
	mlx_delete_image(core.mlx, core.consts.img_dot);
	mlx_delete_texture(core.consts.texture_dot);
	mlx_close_window(core.mlx);
	mlx_terminate(core.mlx);
	return (0);
}
