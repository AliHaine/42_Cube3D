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

void	move_left(t_player *player)
{
		player->player_pos_xy[0] += cosf(player->playerangle - PI / 2) * player->move_speed;
		player->player_pos_xy[1] += sinf(player->playerangle - PI / 2) * player->move_speed;
		player->player_coords_xy[0] += cosf(player->playerangle - PI / 2) * player->move_speed;
		player->player_coords_xy[1] += sinf(player->playerangle - PI / 2) * player->move_speed;
}

void	move_right(t_player *player)
{
		player->player_pos_xy[0] -= cosf(player->playerangle - PI / 2) * player->move_speed;
		player->player_pos_xy[1] -= sinf(player->playerangle - PI / 2) * player->move_speed;
		player->player_coords_xy[0] -= cosf(player->playerangle - PI / 2) * player->move_speed;
		player->player_coords_xy[1] -= sinf(player->playerangle - PI / 2) * player->move_speed;
}

void	move_backward(t_player *player)
{
		player->player_pos_xy[0] -= cosf(player->playerangle) * player->move_speed;
		player->player_pos_xy[1] -= sinf(player->playerangle) * player->move_speed;
		player->player_coords_xy[0] -= cosf(player->playerangle) * player->move_speed;
		player->player_coords_xy[1] -= sinf(player->playerangle) * player->move_speed;
}

void	move_forward(t_player *player)
{
		player->player_pos_xy[0] += cosf(player->playerangle) * player->move_speed;
		player->player_pos_xy[1] += sinf(player->playerangle) * player->move_speed;
		player->player_coords_xy[0] += cosf(player->playerangle) * player->move_speed;
		player->player_coords_xy[1] += sinf(player->playerangle) * player->move_speed;
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
