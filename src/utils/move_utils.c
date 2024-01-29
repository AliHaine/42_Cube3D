/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:52:34 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 18:52:35 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

bool	is_move_key_down(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_A)
		|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		return (true);
	return (false);
}

bool	is_player_running(t_player *player)
{
	if (player->move_speed > MOVE_SPEED)
		return (true);
	return (false);
}

bool	is_block(float x, float y)
{
	t_world	*world;
	char	c;

	world = get_world_active();
	c = world->world[get_chunk_from_pos((int)x / 64, (int)y / 64)]
	[(int)y / 64 % world->height][(int)x / 64 % world->width];
	if (c != '0' && c == '1' || is_rigid_block(get_block_name_from_char(c)))
		return (true);
	return (false);
}

float	check_overflow(float val)
{
	if (val > 1)
		return (1);
	else if (val < -1)
		return (-1);
	return (val);
}
