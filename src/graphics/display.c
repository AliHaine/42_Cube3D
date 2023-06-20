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
	int     	py;
	int	        px;
    const int   limit_x1 = ((core->consts.map_width) * 64) / core->consts.minimap_size;
    const int   limit_y1 = ((core->consts.map_height + 1) * 64) / core->consts.minimap_size;

	py = -1;
	while (++py < limit_y1 && py / RESIZE < core->consts.map_height + 1
        && py < SCREEN_HEIGHT)
	{
		px = -1;
		while (++px < limit_x1 && px / RESIZE < core->consts.map_width
			&& px < SCREEN_WIDTH)
		{
			if (core->consts.map[py / RESIZE][px / RESIZE] == '0'
				|| is_player_char(core->consts.map[py / RESIZE]
				[px / (64 / core->consts.minimap_size)])) {
				mlx_put_pixel(core->imgs.img_map, px, py,
							  core->consts.minimap_floor_color);
			}
			else if (core->consts.map[py / RESIZE][px / RESIZE] == '1')
				mlx_put_pixel(core->imgs.img_map, px, py,
					core->consts.minimap_wall_color);
		}
	}
}

static void	display_icon_in_invbar(t_slot *slot)
{
	t_slot	*iterator;

	iterator = slot;
	while (iterator->next)
	{
		if (iterator->item->name != HAND)
			iterator->item->icon->instances[0].enabled = true;
		iterator = iterator->next;
	}
}

static void	display_item_in_hand(t_player *player)
{
	t_slot *tempo;

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
	animation_listener(core);
	display_item_in_hand(&core->player);
	display_icon_in_invbar(get_first_slot(core->player.slot));
	draw_energy_bar(core->imgs.engbar, core->player.energy);
	mlx_delete_image(core->mlx, core->imgs.img_map);
	mlx_delete_image(core->mlx, core->imgs.img_3d);
	//Image du point du joueur
	//Playerpos c'est selon la resolution de l'ecran
	//Sinon c'est que des ptits calculs pour adapter la position du joueur
	//selon la taille de la map, de l'ecran et du decalage de la minimap de 10 pixels
	core->imgs.img_player->instances[0].x = ((core->player.playerpos[0]
				/ core->consts.minimap_size) - (MINIMAP_PLAYER_SIZE / 2)) + 10;
	core->imgs.img_player->instances[0].y = ((core->player.playerpos[1]
				/ core->consts.minimap_size) - (MINIMAP_PLAYER_SIZE / 2)) + core->screen_size[1];

	//Image avec toute la 3D
	core->imgs.img_3d = mlx_new_image(core->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	//Image de la minimap
	core->imgs.img_map = mlx_new_image(core->mlx, (int)
			((core->consts.map_width * 64) / core->consts.minimap_size), (int)
			(((core->consts.map_height + 1) * 64) / core->consts.minimap_size));
	//Dessiner la minimap
	draw_map(core);
	//Dessiner la 3D
	raycast(core);
	mlx_image_to_window(core->mlx, core->imgs.img_3d, 0, 0);
	mlx_image_to_window(core->mlx, core->imgs.img_map, 10, core->screen_size[1] - 202);
	//Definir l'ordre des images / qui est au dessus de qui
	core->imgs.img_3d->instances[0].z = 1;
	core->imgs.img_map->instances[0].z = 2;
	core->imgs.img_player->instances[0].z = 3;
}
