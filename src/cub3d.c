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


//C'est juste pour creer un point qui represente le joueur sur la minimap
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
	core->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "セグメンテーションフォルトのないプログラムは、鋭い剣のように正確に使える。", true);
	core->imgs.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->consts.ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 150;
	core->consts.minimap_wall_color = (42 << 24) + (42 << 16) + (42 << 8) + 200;
	core->consts.minimap_floor_color = (128 << 24) + (128 << 16) + (128 << 8) + 200;
	core->consts.top_color = (0 << 24) + (0 << 16) + (0 << 8) + 255;
	core->consts.bot_color = (0 << 24) + (0 << 16) + (0 << 8) + 255;
	core->consts.ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 255;
	core->consts.south_east = PI / 4;
	core->consts.south_west = (3 * PI) / 4;
	core->consts.north_east = (7 * PI) / 4;
	core->consts.north_west = (5 * PI) / 4;
	//Le FOV est en degres et hop ptite formule qui le met en radians parce-que les fonctions cosf et sinf ne prennent que les radians
	core->consts.fov = FOV * (PI / 180);
	//Calcul de la distance que les rayons doivent avoir entre eux
	core->consts.dist_between_ray = core->consts.fov / RAY_NUMBER;
	core->consts.minimap_size = (int)(64 / MINIMAP_SIZE);
	core->imgs.img_player = create_minimap_player(core);
	//core->consts.wall_texture = mlx_load_png("assets/brick64.png");
    core->consts.door_texture = mlx_load_png("assets/door.png");
	core->consts.wall_texture[3] = mlx_load_png("assets/default_wall.png");
    core->screen_size[0] = SCREEN_WIDTH;
    core->screen_size[1] = SCREEN_HEIGHT;
	mlx_set_cursor(core->mlx, mlx_create_cursor(mlx_load_png("assets/trans.png")));
	mlx_image_to_window(core->mlx, core->imgs.img_player, 0, 0);
	return (core);
}

int	main(int argc, char *argv[])
{
	t_core	core;

	if (argc != 2)
		msg_write(2, 1, ERROR_ARGS);
	core_init(&core);
	map_manager(argv[1], &core);
	// J'init l'image la psq elle a besoin des variables initialisees par map_manager
	// C'est censé adapter la minimap a la taille de la carte mais pas a la resolution donc ca segfault tjr
	core.imgs.img_map = mlx_new_image(core.mlx, (int)
			((core.consts.map_width * 64) / core.consts.minimap_size), (int)
			(((core.consts.map_height + 1) * 64) / core.consts.minimap_size));
	mlx_loop_hook(core.mlx, &display, &core);
	mlx_loop_hook(core.mlx, &inputs, &core);
    mlx_resize_hook(core.mlx, &resize_hook, &core.screen_size);
	mlx_loop(core.mlx);
	mlx_delete_image(core.mlx, core.imgs.img_3d);
	mlx_delete_image(core.mlx, core.imgs.img_player);
	mlx_delete_image(core.mlx, core.imgs.img_map);
	mlx_close_window(core.mlx);
	mlx_terminate(core.mlx);
	return (0);
}
