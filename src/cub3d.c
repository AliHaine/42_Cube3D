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

static mlx_image_t	*create_minimap_player(mlx_t *mlx, uint32_t ray_color)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	y = -1;
	img = mlx_new_image(mlx, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE);
	while (++y < MINIMAP_PLAYER_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_PLAYER_SIZE)
			mlx_put_pixel(img, x, y, ray_color);
	}
	return (img);
}

static void	const_init(t_const *consts)
{
	consts->ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 150;
	consts->minimap_wall_color = (42 << 24) + (42 << 16) + (42 << 8) + 200;
	consts->minimap_floor_color = (128 << 24) + (128 << 16) + (128 << 8) + 200;
	consts->top_color = (0 << 24) + (0 << 16) + (0 << 8) + 255;
	consts->bot_color = (0 << 24) + (0 << 16) + (0 << 8) + 255;
	consts->ray_color = (220 << 24) + (20 << 16) + (60 << 8) + 255;
	consts->south_east = PI / 4;
	consts->south_west = (3 * PI) / 4;
	consts->north_east = (7 * PI) / 4;
	consts->north_west = (5 * PI) / 4;
	consts->fov = FOV * (PI / 180);
	consts->dist_between_ray = consts->fov / RAY_NUMBER;
	consts->minimap_size = (int)(64 / MINIMAP_SIZE);
}

static void	imgs_init(mlx_t *mlx, t_imgs *imgs, uint32_t ray_color)
{
    imgs->animation = NO_ANIMATION;
	imgs->wall_texture[0] = 0;
	imgs->wall_texture[1] = 0;
	imgs->wall_texture[2] = 0;
	imgs->wall_texture[3] = 0;
	imgs->door_texture = mlx_load_png("assets/door.png");
	imgs->img_3d = mlx_new_image(mlx, SCREEN_WIDTH,
									  SCREEN_HEIGHT);
	imgs->img_player = create_minimap_player(mlx, ray_color);
	if (!set_texture_from_path("assets/grass.png", &imgs->grass_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/trans.png", &imgs->trans))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/e_0.png", &imgs->enemy))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/crosshair.png", &imgs->crosshair))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/invbar.png", &imgs->invbar))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/invbar_selector.png", &imgs->invbar_selector))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/engbar.png", &imgs->engbar))
		msg_write(2, 2, ERROR_FATAL);
    if (!set_image_from_path(mlx, "assets/hearth_full.png", &imgs->hearth[1]))
        msg_write(2, 2, ERROR_FATAL);
    if (!set_image_from_path(mlx, "assets/hearth_empty.png", &imgs->hearth[0]))
        msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/icon_sword_nether.png", &imgs->icon_sword_nether))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/texture/sword1resize.png", &imgs->sword[0]))
        msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/texture/sword2resize.png", &imgs->sword[1]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/texture/sword3resize.png", &imgs->sword[2]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/texture/sword4resize.png", &imgs->sword[3]))
		msg_write(2, 2, ERROR_FATAL);
}

static void	sound_init(t_core *core)
{
	msg_write(1, -1, SOUND_INIT);
	usleep(450000 * LOAD);
	init_sound_empty(&core->sounds);
	if (!load_sound(&(core->sounds.ambiant), "assets/sounds/ambiant.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(&core->sounds.hurt, "assets/sounds/hurt.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	play_sound(core->sounds.ambiant);
	msg_write(1, -1, SUCCESS);
}

static void	core_init(t_core *core)
{
	msg_write(1, -1, CORE_INIT);
	usleep(600000 * LOAD);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	core->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "セグメンテーションフォルトのないプログラムは、鋭い剣のように正確に使える。", true);
	const_init(&core->consts);
	imgs_init(core->mlx, &core->imgs, core->consts.ray_color);
	sound_init(core);
	core->imgs.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->imgs.img_player = create_minimap_player(core->mlx, core->consts.ray_color);
	mlx_set_cursor(core->mlx, mlx_create_cursor(core->imgs.trans));
	//voir pourquoi on est obliger de mettre 2 fois le cursor
	mlx_image_to_window(core->mlx, core->imgs.crosshair, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_image_to_window(core->mlx, core->imgs.img_player, 0, 0);
	mlx_image_to_window(core->mlx, core->imgs.invbar, SCREEN_WIDTH / 3.17,SCREEN_HEIGHT - 95);
	mlx_image_to_window(core->mlx, core->imgs.invbar_selector, SCREEN_WIDTH / 3.17,SCREEN_HEIGHT - 95);
	mlx_image_to_window(core->mlx, core->imgs.engbar, SCREEN_WIDTH / 3,SCREEN_HEIGHT - 115);
	mlx_image_to_window(core->mlx, core->imgs.hearth[0], SCREEN_WIDTH / 2.9,SCREEN_HEIGHT - 155);
	mlx_image_to_window(core->mlx, core->imgs.hearth[0], SCREEN_WIDTH / 2.69,SCREEN_HEIGHT - 155);
	mlx_image_to_window(core->mlx, core->imgs.hearth[0], SCREEN_WIDTH / 2.51,SCREEN_HEIGHT - 155);

	mlx_image_to_window(core->mlx, core->imgs.hearth[1], SCREEN_WIDTH / 2.9,SCREEN_HEIGHT - 155);
	mlx_image_to_window(core->mlx, core->imgs.hearth[1], SCREEN_WIDTH / 2.69,SCREEN_HEIGHT - 155);
	mlx_image_to_window(core->mlx, core->imgs.hearth[1], SCREEN_WIDTH / 2.51,SCREEN_HEIGHT - 155);
	mlx_image_to_window(core->mlx, core->imgs.icon_sword_nether, SCREEN_WIDTH / 3.05,SCREEN_HEIGHT - 80);

	mlx_image_to_window(core->mlx, core->imgs.crosshair, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_image_to_window(core->mlx, core->imgs.sword[0], SCREEN_WIDTH / 1.4, SCREEN_HEIGHT - 290);
	mlx_image_to_window(core->mlx, core->imgs.sword[1], SCREEN_WIDTH / 1.6, SCREEN_HEIGHT - 310);
	mlx_image_to_window(core->mlx, core->imgs.sword[2], SCREEN_WIDTH / 1.7, SCREEN_HEIGHT - 320);
	mlx_image_to_window(core->mlx, core->imgs.sword[3], SCREEN_WIDTH / 1.8, SCREEN_HEIGHT - 330);
	core->imgs.sword[1]->enabled = 0;
	core->imgs.sword[2]->enabled = 0;
	core->imgs.sword[3]->enabled = 0;
    core->imgs.hearth[0]->enabled = 1;
    core->imgs.hearth[1]->enabled = 1;
	core->screen_size[0] = SCREEN_WIDTH;
    core->screen_size[1] = SCREEN_HEIGHT;
	core->player.have_player = false;
	core->player.move_speed = 10;
    core->player.health = 2;
	core->player.energy = 100;
	core->player.toolbar_slot = 0;
	msg_write(1, -1, SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_core	core;
	(void)argc;

	msg_write(1, -1, STARTING);
	core_init(&core);
	usleep(60000);
	map_manager(argv, &core);
	// J'init l'image la psq elle a besoin des variables initialisees par map_manager
	// C'est censé adapter la minimap a la taille de la carte mais pas a la resolution donc ca segfault tjr
	msg_write(1, -1, MINIMAP_INIT);
	usleep(800000 * LOAD);
	core.imgs.img_map = mlx_new_image(core.mlx, (int)
			((core.consts.map_width * 64) / core.consts.minimap_size), (int)
			(((core.consts.map_height + 1) * 64) / core.consts.minimap_size));
	msg_write(1, -1, SUCCESS);
	mlx_loop_hook(core.mlx, &display, &core);
	mlx_loop_hook(core.mlx, &inputs, &core);
	mlx_loop_hook(core.mlx, &player_listener, &core);
	mlx_key_hook(core.mlx, &inputs_hook, &core);
    mlx_resize_hook(core.mlx, &resize_hook, &core);
	mlx_mouse_hook(core.mlx, &mouse, &core);
	mlx_scroll_hook(core.mlx, &scroll_hook, &core);
	mlx_loop(core.mlx);
	delete_image_from_struct(core.mlx, &core.imgs);
	mlx_close_window(core.mlx);
	mlx_terminate(core.mlx);
	return (0);
}
