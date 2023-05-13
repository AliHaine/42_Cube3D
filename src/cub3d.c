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

int	g_map[12][20] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

static t_core	*core_init(void)
{
	t_core	*core;

	core = (t_core *)malloc(sizeof(t_core));
	core->consts = (t_const *)malloc(sizeof(t_const));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	core->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	core->consts->img_map = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->consts->texture_dot = mlx_load_png("assets/red_dot.png");
	core->consts->img_dot = mlx_texture_to_image(core->mlx,
			core->consts->texture_dot);
	core->consts->wall_color = (150 << 24) + (150 << 16) + (150 << 8) + 255;
	core->consts->ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 255;
	core->playerpos[0] = 5 * 64;
	core->playerpos[1] = 5 * 64;
	core->consts->fov = FOV * (PI / 180);
	core->consts->dist_between_ray = core->consts->fov / RAY_NUMBER;
	core->playerangle = 0;
	ft_memcpy(core->consts->map, g_map, sizeof(g_map));
	return (core);
}

int	main(int argc, char *argv[])
{
	t_core	*core;

	if (argc != 2)
		return (1);
	parse_main(argv[1]);
	core = core_init();
	mlx_loop_hook(core->mlx, &display, core);
	mlx_loop_hook(core->mlx, &inputs, core);
	mlx_loop(core->mlx);
	mlx_delete_image(core->mlx, core->consts->img_map);
	mlx_delete_image(core->mlx, core->consts->img_dot);
	mlx_delete_texture(core->consts->texture_dot);
	mlx_close_window(core->mlx);
	mlx_terminate(core->mlx);
	free(core->consts);
	free(core);
	return (0);
}
