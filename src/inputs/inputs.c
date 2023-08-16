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
#include "../../includes/defines.h"

static void	rotation_inputs(mlx_t *mlx, t_player *player)
{
    if (!player->can_move)
        return ;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		move_rotate(player, 0, (float)SENSIBILITY / 10);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		move_rotate(player, 1, (float)SENSIBILITY / 10);
}


static void moving_inputs(mlx_t *mlx, t_player *player, char **map)
{
	if (!player->can_move)
	{
		player->is_moving = false;
		return ;
	}
	player->is_moving = true;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_right_left(player, map, 1);
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_right_left(player, map, 0);
	else if (mlx_is_key_down(mlx, MLX_KEY_S)
			 || mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move_forward_backward(player, map, 1);
	else if (mlx_is_key_down(mlx, MLX_KEY_W)
			 || mlx_is_key_down(mlx, MLX_KEY_UP))
		move_forward_backward(player, map, 0);
	else
		player->is_moving = false;
}

void	inputs(void *params)
{
	t_core	*core;

	core = (t_core *)params;
	mouse_cursor(core->mlx, &core->player, core->screen_size);
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
	rotation_inputs(core->mlx, &core->player);
	//printf("%f %f\n", core->player.player_pos_yx[0] / 64 , core->player.player_pos_yx[1] / 64);
	moving_inputs(core->mlx, &core->player, core->maps[0].world[4]);
}

void	inputs_hook(struct mlx_key_data key, void *params)
{
	t_core	*core;

	core = (t_core *)params;
	if (key.key == 340 && key.action == 1)
			core->player.move_speed = MOVE_SPEED * 2;
	else if (key.key == 340 && key.action == 0)
		core->player.move_speed = MOVE_SPEED;
    if (key.key == 69 && key.action == 0)
        inventory(core);
}
