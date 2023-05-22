/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:48:19 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:48:26 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

void	move_right_left(t_player *player, char **map, int direction)
{
	if (map[(int)((player->playerpos[1]
				- (sinf(player->playerangle - PI / 2) * WALK_SPEED)) / 64)]
				[(int)((player->playerpos[0] -(cosf(player->playerangle - PI / 2)
				* WALK_SPEED)) / 64)] != '1'
				&& direction == 1)
	{
		player->playerpos[0] -= cosf(player->playerangle - PI / 2) * WALK_SPEED;
		player->playerpos[1] -= sinf(player->playerangle - PI / 2) * WALK_SPEED;
	}
	else if (map[(int)(player->playerpos[1]
			+ (sinf(player->playerangle - PI / 2) * WALK_SPEED)) / 64]
				[(int)((player->playerpos[0] + (cosf(player->playerangle - PI / 2)
				* WALK_SPEED)) / 64)] != '1'
				&& direction == 0)
	{
		player->playerpos[0] += cosf(player->playerangle - PI / 2) * WALK_SPEED;
		player->playerpos[1] += sinf(player->playerangle - PI / 2) * WALK_SPEED;
	}
}

void	move_forward_backward(t_player *player, char **map, int direction)
{
	if (map[(int)((player->playerpos[1]
				- (sinf(player->playerangle) * WALK_SPEED)) / 64)]
				[(int)((player->playerpos[0] - (cosf(player->playerangle)
				* WALK_SPEED)) / 64)] != '1'
					&& direction == 1)
	{
		player->playerpos[0] -= cosf(player->playerangle) * WALK_SPEED;
		player->playerpos[1] -= sinf(player->playerangle) * WALK_SPEED;
	}
	else if (map[(int)((player->playerpos[1] + (sinf(player->playerangle)
					* WALK_SPEED)) / 64)][(int)((player->playerpos[0] +
					(cosf(player->playerangle) * WALK_SPEED)) / 64)] != '1'
					&& direction == 0)
	{
		player->playerpos[0] += cosf(player->playerangle) * WALK_SPEED;
		player->playerpos[1] += sinf(player->playerangle) * WALK_SPEED;
	}
}

void	move_rotate(t_player *player, int direction)
{
	if (direction == 0)
	{
		player->playerangle -= SENSIBILITY;
		if (player->playerangle < 0)
			player->playerangle += 6.28319;
	}
	else if (direction == 1)
	{
		player->playerangle += SENSIBILITY;
		if (player->playerangle > 6.28319)
			player->playerangle -= 6.28319;
	}
}
