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

static mlx_image_t	*create_minimap_player(t_core *core)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	y = -1;
	img = mlx_new_image(core->mlx, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE);
	while (++y < MINIMAP_PLAYER_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_PLAYER_SIZE)
		{
			mlx_put_pixel(img, x, y, core->consts.ray_color);
		}
	}
	return (img);
}

static t_core	*core_init(t_core *core)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	core->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	core->consts.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->consts.img_map = mlx_new_image(core->mlx, (core->consts.map_width * 64) / core->consts.minimap_size,
			(core->consts.map_height * 64) / core->consts.minimap_size);
	core->consts.texture_dot = mlx_load_png("assets/red_dot.png");
	core->consts.ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 150;
	core->consts.minimap_wall_color = (210 << 24) + (180 << 16) + (140 << 8) + 255;
	core->consts.minimap_floor_color = (255 << 24) + (222 << 16) + (173 << 8) + 255;
	core->consts.top_color = (0 << 24) + (0 << 16) + (0 << 8) + 255;
	core->consts.bot_color = (0 << 24) + (0 << 16) + (0 << 8) + 255;
	core->consts.ray_color = (255 << 24) + (239 << 16) + (213 << 8) + 255;
	core->consts.fov = FOV * (PI / 180);
	core->consts.dist_between_ray = core->consts.fov / RAY_NUMBER;
	core->consts.minimap_size = (int)(64 / MINIMAP_SIZE);
	core->consts.img_player = create_minimap_player(core);
	mlx_image_to_window(core->mlx, core->consts.img_player, 0, 0);
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
	mlx_delete_image(core.mlx, core.consts.img_3d);
	mlx_delete_image(core.mlx, core.consts.img_player);
	mlx_delete_image(core.mlx, core.consts.img_map);
	mlx_delete_texture(core.consts.texture_dot);
	mlx_close_window(core.mlx);
	mlx_terminate(core.mlx);
	return (0);
}
