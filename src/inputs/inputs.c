/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:48:11 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:48:14 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	rotation_inputs(mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		move_rotate(player, 0, (float)SENSIBILITY / 10);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		move_rotate(player, 1, (float)SENSIBILITY / 10);
}

static void	choose_move(mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_right(player);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left(player);
	if (mlx_is_key_down(mlx, MLX_KEY_S)
		|| mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move_backward(player);
	if (mlx_is_key_down(mlx, MLX_KEY_W)
		|| mlx_is_key_down(mlx, MLX_KEY_UP))
		move_forward(player);
}

static void	moving_inputs(mlx_t *mlx, t_player *player)
{
	if (!is_move_key_down(mlx))
	{
		player->is_moving = false;
		return ;
	}
	player->is_moving = true;
	choose_move(mlx, player);
}

void	inputs(void *params)
{
	t_core	*core;

	core = (t_core *)params;
	mouse_cursor(core->mlx, &core->player, core->screen_size);
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
	if (!core->player.can_move)
		return ;
	rotation_inputs(core->mlx, &core->player);
	moving_inputs(core->mlx, &core->player);
	if (is_chunk_change(&core->player.player_cell_xy,
			get_world_active()))
		world_dynamic_generator(&core->player);
	core->player.player_cell_xy[0] = (int)(core->player.player_pos_xy[0] / 64);
	core->player.player_cell_xy[1] = (int)(core->player.player_pos_xy[1] / 64);
}

void	inputs_hook(struct mlx_key_data key, void *params)
{
	t_core	*core;

	core = (t_core *)params;
	if (key.key == 340 && key.action == 1)
	{
		core->player.is_running = true;
		core->player.move_speed = MOVE_SPEED * 2;
	}
	else if (key.key == 340 && key.action == 0)
	{
		core->player.is_running = false;
		core->player.move_speed = MOVE_SPEED;
	}
	if (key.key == 69 && key.action == 0)
		inventory(core);
}
