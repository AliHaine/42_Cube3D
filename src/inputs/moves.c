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
				- (sinf(player->playerangle - PI / 2) * player->move_speed)) / 64)]
				[(int)((player->playerpos[0] - (cosf(player->playerangle
				- PI / 2) * player->move_speed)) / 64)] != '1'
				&& direction == 1)
	{
		player->playerpos[0] -= cosf(player->playerangle - PI / 2) * player->move_speed;
		player->playerpos[1] -= sinf(player->playerangle - PI / 2) * player->move_speed;
	}
	else if (map[(int)(player->playerpos[1]
			+ (sinf(player->playerangle - PI / 2) * player->move_speed)) / 64]
				[(int)((player->playerpos[0] + (cosf(player->playerangle - PI / 2)
				* player->move_speed)) / 64)] != '1'
				&& direction == 0)
	{
		player->playerpos[0] += cosf(player->playerangle - PI / 2) * player->move_speed;
		player->playerpos[1] += sinf(player->playerangle - PI / 2) * player->move_speed;
	}
}

void	move_forward_backward(t_player *player, char **map, int direction)
{
	if (map[(int)((player->playerpos[1]
				- (sinf(player->playerangle) * player->move_speed)) / 64)]
				[(int)((player->playerpos[0] - (cosf(player->playerangle)
				* player->move_speed)) / 64)] != '1'
					&& direction == 1
					&& map[(int)(player->playerpos[1] / 64)][(int)(player->playerpos[0] / 64)] != 1)
	{
		player->playerpos[0] -= cosf(player->playerangle) * player->move_speed;
		player->playerpos[1] -= sinf(player->playerangle) * player->move_speed;
	}
	else if (map[(int)((player->playerpos[1] + (sinf(player->playerangle)
					* player->move_speed)) / 64)][(int)((player->playerpos[0] +
					(cosf(player->playerangle) * player->move_speed)) / 64)] != '1'
					&& direction == 0)
	{
		player->playerpos[0] += cosf(player->playerangle) * player->move_speed;
		player->playerpos[1] += sinf(player->playerangle) * player->move_speed;
	}
}

void	move_rotate(t_player *player, int direction, float speed)
{
	if (direction == 0)
	{
		player->playerangle -= speed;
		if (player->playerangle < 0)
			player->playerangle += 6.28319;
	}
	else if (direction == 1)
	{
		player->playerangle += speed;
		if (player->playerangle > 6.28319)
			player->playerangle -= 6.28319;
	}
}
