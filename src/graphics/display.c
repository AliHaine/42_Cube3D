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
			iterator->items_number_img_bar->instances[0].x = (div + ((iterator->slot_id - 1) * 61)) + 23;
			iterator->items_number_img_bar->instances[0].enabled = true;
			iterator->item->icon->instances[iterator->bar_icon_instance].x = div + ((iterator->slot_id - 1) * 61);
			iterator->item->icon->instances[iterator->bar_icon_instance].enabled = true;
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

//Loop hook qui va supprimer les images, les recreer, et les reafficher en boucle
void	display(void *params)
{
	t_core	*core;

	core = (t_core *) params;
	animation_listener(core->items, core->blocks);
	display_item_in_hand(&core->player);
	display_icon_in_invbar(get_first_slot(core->player.slot));
	mlx_delete_image(core->mlx, core->imgs.img_map);
	mlx_delete_image(core->mlx, core->imgs.img_3d);
	mlx_delete_image(core->mlx, core->imgs.img_player);
	core->imgs.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	core->imgs.img_map = mlx_texture_to_image(core->mlx, core->imgs.map_texture);
	raycasting(&core->player, &core->imgs, &core->maps[0], core->blocks);
	minimap_drawing(&core->imgs, core->player.player_pos_xy, &core->maps[0]);
	core->imgs.img_player = rotate_image(core->mlx, core->imgs.img_player_texture, core->player.playerangle + (PI / 2));
	mlx_resize_image(core->imgs.img_map, 250, 250);
	mlx_resize_image(core->imgs.img_player, 14, 14);
	mlx_image_to_window(core->mlx, core->imgs.img_3d, 0, 0);
	mlx_image_to_window(core->mlx, core->imgs.img_map, 20, 445);
	mlx_image_to_window(core->mlx, core->imgs.img_player, 137, 561);
	//Definir l'ordre des images / qui est au dessus de qui
	core->imgs.img_3d->instances[0].z = 1;
	//core->imgs.map_background->instances[0].z = 2;
	core->imgs.img_map->instances[0].z = 3;
	core->imgs.img_player->instances[0].z = 4;
	core->imgs.crosshair->instances[0].z = 5;
	core->imgs.invbar->instances[0].z = 6;
	core->imgs.invbar_selector->instances[0].z = 7;
    core->imgs.engbar->instances[0].z = 9;
}
