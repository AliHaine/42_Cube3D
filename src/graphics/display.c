/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:51 by ngalzand          #+#    #+#             */
/*   Updated: 2024/01/24 15:25:33 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	set_imgs_z(t_imgs *imgs)
{
	imgs->img_3d->instances[0].z = 1;
	imgs->img_map->instances[0].z = 3;
	imgs->img_player->instances[0].z = 4;
	imgs->crosshair->instances[0].z = 7;
    imgs->crosshair->instances[0].x = (SCREEN_WIDTH / 2) - 8;
    imgs->crosshair->instances[0].y = (SCREEN_HEIGHT / 2) - 8;
	imgs->invbar->instances[0].z = 6;
	imgs->invbar_selector->instances[0].z = 7;
	imgs->engbar->instances[0].z = 9;
}

static void	display_icon_in_invbar(t_slot *slot)
{
	t_slot				*iterator;
	static const int	div = SCREEN_WIDTH / 3.35;

	iterator = slot;
	while (iterator->prev)
		iterator = iterator->prev;
	while (iterator->next && iterator->next->slot_id < 11)
	{
		if (iterator->item->name != HAND && !iterator->bar_mutex)
		{
			iterator->items_number_img_bar->instances[0].x
				= (div + ((iterator->slot_id - 1) * 61)) + 23;
			iterator->items_number_img_bar->instances[0].enabled = true;
			iterator->item->icon->instances[iterator->bar_icon_instance].x
				= div + ((iterator->slot_id - 1) * 61);
			iterator->item->icon->instances[iterator->bar_icon_instance].enabled
				= true;
		}
		else
			iterator->items_number_img_bar->instances[0].enabled = false;
		iterator = iterator->next;
	}
}

static void	display_item_in_hand(t_player *player)
{
	t_slot	*tempo;

	tempo = get_first_slot(player->slot);
	while (tempo->next)
	{
		tempo->item->image->instances[0].enabled = 0;
		tempo = tempo->next;
	}
	player->slot->item->image->instances[0].enabled = 1;
}

void	display(void *params)
{
	t_core	*core;


	core = (t_core *) params;
	animation_listener();
	display_item_in_hand(&core->player);
	display_icon_in_invbar(get_first_slot(core->player.slot));
	mlx_delete_image(core->mlx, core->imgs.img_map);
	core->imgs.img_map = mlx_texture_to_image
		(core->mlx, core->imgs.map_texture);

	raycasting(&core->player, &core->imgs, &core->options);

	minimap_drawing(&core->imgs, core->player.player_pos_xy, get_world_active());
	mlx_delete_image(core->mlx, core->imgs.img_player);
	core->imgs.img_player = rotate_image(core->mlx,
			core->imgs.img_player_texture, core->player.playerangle + (PI / 2));
	mlx_resize_image(core->imgs.img_map, 250, 250);
	mlx_image_to_window(core->mlx, core->imgs.img_map, 20, 445);
	mlx_image_to_window(core->mlx, core->imgs.img_player, 132, 556);
	set_imgs_z(&core->imgs);
}
