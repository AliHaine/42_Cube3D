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
	/*if (!set_texture_from_path("assets/others/e_0.png", &imgs->enemy))
		msg_write(2, 2, ERROR_FATAL);*/
	if (!set_image_from_path(mlx, "assets/guis/invbar.png", &imgs->invbar))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/guis/engbar.png", &imgs->engbar))
		msg_write(2, 2, ERROR_FATAL);

	if (!set_image_from_path(mlx, "assets/grass.png", &imgs->floor_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/skybox.png", &imgs->skybox))
		msg_write(2, 2, ERROR_FATAL);
    if (!set_texture_from_path("assets/guis/inventory_gui2.png", &imgs->inventory_gui_texture))
        msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/cursor.png", &imgs->cursor))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/guis/minimap_background.png", &imgs->map_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/player_dot.png", &imgs->img_player_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal.png", &imgs->nether_portal[0]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal1.png", &imgs->nether_portal[1]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal2.png", &imgs->nether_portal[2]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal3.png", &imgs->nether_portal[3]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal4.png", &imgs->nether_portal[4]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal5.png", &imgs->nether_portal[5]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal6.png", &imgs->nether_portal[6]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal7.png", &imgs->nether_portal[7]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal8.png", &imgs->nether_portal[8]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal9.png", &imgs->nether_portal[9]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal10.png", &imgs->nether_portal[10]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal11.png", &imgs->nether_portal[11]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal12.png", &imgs->nether_portal[12]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal13.png", &imgs->nether_portal[13]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/walls/netherportal/netherportal14.png", &imgs->nether_portal[14]))
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
