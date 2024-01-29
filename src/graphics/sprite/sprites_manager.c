/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:48:57 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 12:48:59 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

char	get_rand_sprite_char(t_world *world)
{
	static const char	tab_default[] = {'>', '<', '^', 'v'};
	static const char	tab_nether[] = {':', ';', '?', '/'};

	if (world->world_name == WORLD_DEFAULT)
		return (tab_default[get_rand_num(4, 1)]);
	else
		return (tab_nether[get_rand_num(4, 1)]);
}

void	sprites_place(t_world *world, int chunk)
{
	if (!world->sprites)
		return ;
	move_multiple_sprites(world, chunk);
	reload_sprite_pos(world);
}

void	add_sprite(t_world *world, int chunk, char c, int xy[2])
{
	int	len;

	len = 0;
	while (world->sprites[chunk] != NULL && world->sprites[chunk][len])
		len++;
	if (world->sprites[chunk] == NULL)
	{
		world->sprites[chunk] = (t_sprite **)malloc(sizeof(t_sprite *) * 2);
		world->sprites[chunk][0] = (t_sprite *)malloc(sizeof(t_sprite));
		world->sprites[chunk][1] = NULL;
	}
	else
		realloc_sprites(&world->sprites[chunk], len);
	world->sprites[chunk][len]->x_origin = xy[0];
	world->sprites[chunk][len]->y_origin = xy[1];
	world->sprites[chunk][len]->cell_xy[0] = (int)(world->sprites
		[chunk][len]->x_origin + (world->width * (chunk % 3)));
	world->sprites[chunk][len]->cell_xy[1] = (int)(world->sprites
		[chunk][len]->y_origin + (world->height
				* lround(((float)chunk - 1.f) / 3.f)));
	world->sprites[chunk][len]->sp_xy[0] = ((float)(world->sprites[chunk][len]->cell_xy[0]) + ((get_rand_num(9, 1) / 10) + 0.2f)) * 64;
	world->sprites[chunk][len]->sp_xy[1] = ((float)(world->sprites[chunk][len]->cell_xy[1]) + ((get_rand_num(9, 1) / 10) + 0.2f)) * 64;
	world->sprites[chunk][len]->chunk_sp_xy[0] = world->sprites[chunk][len]->sp_xy[0];
	world->sprites[chunk][len]->chunk_sp_xy[1] = world->sprites[chunk][len]->sp_xy[1];
	select_sprite(world->sprites[chunk][len], c);
}

void	sprites_generator(t_world *world)
{
	int	chunk;
	int	xy[2];

	chunk = -1;
	if (world->world_name != WORLD_DEFAULT
		&& world->world_name != WORLD_NETHER)
	{
		world->sprites = NULL;
		return ;
	}
	while (++chunk < 9)
	{
		xy[1] = -1;
		while (++xy[1] < world->height)
		{
			xy[0] = -1;
			while (++xy[0] < world->width)
				if (!get_rand_num(5, 1))
					add_sprite(world, chunk, get_rand_sprite_char
						(world), xy);
		}
	}
	reload_sprite_pos(world);
}
