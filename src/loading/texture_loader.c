/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:35:49 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/02 12:35:51 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	other_loader(mlx_t *mlx, t_imgs *imgs)
{
	if (!set_texture_from_path("assets/others/trans.png", &imgs->trans))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/guis/invbar.png", &imgs->invbar))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/guis/engbar.png", &imgs->engbar))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/blocks/grass.png", &imgs->floor_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/skybox.png", &imgs->skybox))
		msg_write(2, 2, ERROR_FATAL);
    if (!set_image_from_path(mlx, "assets/skybox_nether.png", &imgs->skybox_nether))
        msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/skybox_end.png", &imgs->skybox_end))
		msg_write(2, 2, ERROR_FATAL);
    if (!set_texture_from_path("assets/guis/inventory_gui2.png", &imgs->inventory_gui_texture))
        msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/cursor.png", &imgs->cursor))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/guis/minimap_background.png", &imgs->map_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/player_dot.png", &imgs->img_player_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/blocks/backrooms_ceil.png", &imgs->backrooms_ceil))
		msg_write(2, 2, ERROR_FATAL);
}

static void	icon_loader(mlx_t *mlx, t_imgs *imgs)
{
	if (!set_image_from_path(mlx, "assets/icons/crosshair.png", &imgs->crosshair))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/icons/invbar_selector.png", &imgs->invbar_selector))
		msg_write(2, 2, ERROR_FATAL);
	mlx_resize_image(imgs->invbar_selector, imgs->invbar_selector->width / 1.5,
		imgs->invbar_selector->height / 1.5);
	if (!set_image_from_path(mlx, "assets/icons/hearth_full.png", &imgs->hearth[1]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/icons/hearth_empty.png", &imgs->hearth[0]))
		msg_write(2, 2, ERROR_FATAL);
}

void	texture_loader(t_core *core)
{
	icon_loader(core->mlx, &core->imgs);
	other_loader(core->mlx, &core->imgs);
}
