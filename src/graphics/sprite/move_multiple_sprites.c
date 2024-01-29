/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_multiple_sprites.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:59:02 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 14:59:04 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

/* Forced to put this atrocity for the norm */

static void	move_multiple_sprites_quater(t_world *world)
{
	t_sprite	**chunk1;
	t_sprite	**chunk2;
	t_sprite	**chunk3;

	chunk1 = world->sprites[2];
	chunk2 = world->sprites[5];
	chunk3 = world->sprites[8];
	world->sprites[2] = world->sprites[1];
	world->sprites[5] = world->sprites[4];
	world->sprites[8] = world->sprites[7];
	world->sprites[1] = world->sprites[0];
	world->sprites[4] = world->sprites[3];
	world->sprites[7] = world->sprites[6];
	world->sprites[0] = chunk1;
	world->sprites[3] = chunk2;
	world->sprites[6] = chunk3;
}

static void	move_multiple_sprites_ter(t_world *world)
{
	t_sprite	**chunk1;
	t_sprite	**chunk2;
	t_sprite	**chunk3;

	chunk1 = world->sprites[0];
	chunk2 = world->sprites[1];
	chunk3 = world->sprites[2];
	world->sprites[0] = world->sprites[3];
	world->sprites[1] = world->sprites[4];
	world->sprites[2] = world->sprites[5];
	world->sprites[3] = world->sprites[6];
	world->sprites[4] = world->sprites[7];
	world->sprites[5] = world->sprites[8];
	world->sprites[6] = chunk1;
	world->sprites[7] = chunk2;
	world->sprites[8] = chunk3;
}

static void	move_multiple_sprites_bis(t_world *world, int dir)
{
	t_sprite	**chunk1;
	t_sprite	**chunk2;
	t_sprite	**chunk3;

	if (dir == 5)
	{
		chunk1 = world->sprites[0];
		chunk2 = world->sprites[3];
		chunk3 = world->sprites[6];
		world->sprites[0] = world->sprites[1];
		world->sprites[3] = world->sprites[4];
		world->sprites[6] = world->sprites[7];
		world->sprites[1] = world->sprites[2];
		world->sprites[4] = world->sprites[5];
		world->sprites[7] = world->sprites[8];
		world->sprites[2] = chunk1;
		world->sprites[5] = chunk2;
		world->sprites[8] = chunk3;
	}
	else if (dir == 7)
		move_multiple_sprites_ter(world);
	else if (dir == 3)
		move_multiple_sprites_quater(world);
}

void	move_multiple_sprites(t_world *world, int dir)
{
	t_sprite	**chunk1;
	t_sprite	**chunk2;
	t_sprite	**chunk3;

	if (dir == 1)
	{
		chunk1 = world->sprites[6];
		chunk2 = world->sprites[7];
		chunk3 = world->sprites[8];
		world->sprites[6] = world->sprites[3];
		world->sprites[7] = world->sprites[4];
		world->sprites[8] = world->sprites[5];
		world->sprites[3] = world->sprites[0];
		world->sprites[4] = world->sprites[1];
		world->sprites[5] = world->sprites[2];
		world->sprites[0] = chunk1;
		world->sprites[1] = chunk2;
		world->sprites[2] = chunk3;
	}
	else
		move_multiple_sprites_bis(world, dir);
}
