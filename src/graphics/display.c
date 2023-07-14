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
	const int start_y = (core->player.playerpos[1] / 4) - (286 / 2);
	const int start_x = (core->player.playerpos[0] / 4) - (286 / 2);
	int                 case_y;
	int                 case_x;
	int                 py;
	int                 px;

	py = -1;
	while (++py < 286)
	{
		px = -1;
		case_y = (py + start_y) / 16;
		while (++px < 286)
		{
			case_x = (px + start_x) / 16;
			if (get_pixel(core->imgs.map_texture, px, py) != -692152577)
				continue ;
			else if (case_y < 0 || case_x < 0 ||case_y > core->consts.map_height || case_x > core->consts.map_width - 1)
				mlx_put_pixel(core->imgs.img_map, px, py, core->consts.minimap_wall_color);
			else if (core->consts.map[case_y][case_x] == '1')
				mlx_put_pixel(core->imgs.img_map, px, py, core->consts.minimap_wall_color);
		}
	}
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
	animation_listener(core->items);
	display_item_in_hand(&core->player);
	display_icon_in_invbar(get_first_slot(core->player.slot));
	draw_energy_bar(core->imgs.engbar, core->player.energy);
	mlx_delete_image(core->mlx, core->imgs.img_map);
	mlx_delete_image(core->mlx, core->imgs.img_3d);
	mlx_delete_image(core->mlx, core->imgs.img_player);
	//Image du point du joueur
	//Playerpos c'est selon la resolution de l'ecran
	//Sinon c'est que des ptits calculs pour adapter la position du joueur
	//selon la taille de la map, de l'ecran et du decalage de la minimap de 10 pixels
	//Image avec toute la 3D
	core->imgs.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	//Image de la minimap
	core->imgs.img_map = mlx_texture_to_image(core->mlx, core->imgs.map_texture);
	//Dessiner la minimap
	draw_map(core);
	//Dessiner la 3D
	raycasting(&core->player, &core->consts, &core->imgs);
	mlx_resize_image(core->imgs.img_map, 250, 250);
	//draw_player(core);
	mlx_image_to_window(core->mlx, core->imgs.img_3d, 0, 0);
	mlx_image_to_window(core->mlx, core->imgs.img_map, 20, 445);
	//Definir l'ordre des images / qui est au dessus de qui
	core->imgs.img_3d->instances[0].z = 1;
	//core->imgs.map_background->instances[0].z = 2;
	core->imgs.img_map->instances[0].z = 3;
	//core->imgs.img_player->instances[0].z = 4;
	core->imgs.crosshair->instances[0].z = 5;
	core->imgs.invbar->instances[0].z = 6;
	core->imgs.invbar_selector->instances[0].z = 7;
}
