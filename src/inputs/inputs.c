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


static void moving_inputs(mlx_t *mlx, t_player *player)
{
	char c;

	if (!player->can_move)
	{
		player->is_moving = false;
		return ;
	}
	player->is_moving = true;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
    {
        if (get_right_char(player) == '0')
            move_right(player);
    }
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
        if (get_left_char(player) == '0')
            move_left(player);
    }
	else if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
        if (get_backward_char(player) == '0')
            move_backward(player);
    }
	else if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
    {
		c = get_forward_char(player);
		if (c == '0' || c != '1' && !is_rigid_block(get_block_name_from_char(c)))
            move_forward(player);
    }
	else
		player->is_moving = false;
	player->player_cell_xy[0] = (int)(player->player_pos_xy[0] / 64);
	player->player_cell_xy[1] = (int)(player->player_pos_xy[1] / 64);
}

void	inputs(void *params)
{
	t_core	*core;

	core = (t_core *)params;
	mouse_cursor(core->mlx, &core->player, core->screen_size);
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
	rotation_inputs(core->mlx, &core->player);
	moving_inputs(core->mlx, &core->player);
    if (is_player_chunk_change(&core->player, get_world_active()))
		world_dynamic_generator(&core->player);
}

//todo
void	inputs_hook(struct mlx_key_data key, void *params)
{
	t_core	*core;

	core = (t_core *)params;
	if (key.key == 340 && key.action == 1) {
		core->player.is_running = true;
		core->player.move_speed = MOVE_SPEED * 2;
	}
	else if (key.key == 340 && key.action == 0) {
		core->player.is_running = false;
		core->player.move_speed = MOVE_SPEED;
	}
    if (key.key == 69 && key.action == 0)
        inventory(core);
}
