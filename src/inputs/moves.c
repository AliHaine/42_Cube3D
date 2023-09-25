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

void	move_left(t_player *player)
{
	const float	dir_x = cosf(player->playerangle);
	const float	dir_y = sinf(player->playerangle);
	float		step_x;
	float		step_y;
	float		alpha;

	if (dir_y > 0)
		alpha = acos(check_overflow(dir_x));
	else
		alpha = -acos(check_overflow(dir_x));
	step_y = sinf(alpha + M_PI / 2) * player->move_speed;
	if (!is_block(player->player_pos_xy[0], player->player_pos_xy[1] - step_y)) {
		player->player_pos_xy[1] -= step_y;
		player->player_coords_xy[1] -= step_y;
	}
	step_x = cosf(alpha + M_PI / 2) * player->move_speed;
	if (!is_block(player->player_pos_xy[0] - step_x, player->player_pos_xy[1])) {
		player->player_pos_xy[0] -= step_x;
		player->player_coords_xy[0] -= step_x;
	}
}

void	move_right(t_player *player)
{
	const float	dir_x = cosf(player->playerangle);
	const float	dir_y = sinf(player->playerangle);
	float		step_x;
	float		step_y;
	float		alpha;

	if (dir_y > 0)
		alpha = acos(check_overflow(dir_x));
	else
		alpha = -acos(check_overflow(dir_x));
	step_y = sinf(alpha + M_PI / 2) * player->move_speed;
	if (!is_block(player->player_pos_xy[0], player->player_pos_xy[1] + step_y)) {
		player->player_pos_xy[1] += step_y;
		player->player_coords_xy[1] += step_y;
	}
	step_x = cosf(alpha + M_PI / 2) * player->move_speed;
	if (!is_block(player->player_pos_xy[0] + step_x, player->player_pos_xy[1])) {
		player->player_pos_xy[0] += step_x;
		player->player_coords_xy[0] += step_x;
	}
}

void	move_backward(t_player *player)
{
	float	step_x;
	float	step_y;

	step_x = cosf(player->playerangle) * player->move_speed;
	step_y = sinf(player->playerangle) * player->move_speed;
	if (!is_block(player->player_pos_xy[0], player->player_pos_xy[1] - step_y)) {
		player->player_pos_xy[1] -= step_y;
		player->player_coords_xy[1] -= step_y;
	}
	if (!is_block(player->player_pos_xy[0] - step_x, player->player_pos_xy[1])) {
		player->player_pos_xy[0] -= step_x;
		player->player_coords_xy[0] -= step_x;
	}
}

void	move_forward(t_player *player)
{
	float	step_x;
	float	step_y;

	step_x = cosf(player->playerangle) * player->move_speed;
	step_y = sinf(player->playerangle) * player->move_speed;
	if (!is_block(player->player_pos_xy[0] + step_x, player->player_pos_xy[1])) {
		player->player_pos_xy[0] += step_x;
		player->player_coords_xy[0] += step_x;
	}
	if (!is_block(player->player_pos_xy[0], player->player_pos_xy[1] + step_y)) {
		player->player_pos_xy[1] += step_y;
		player->player_coords_xy[1] += step_y;
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
