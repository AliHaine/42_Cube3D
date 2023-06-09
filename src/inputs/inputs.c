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

void	inputs(void *params)
{
	t_core	*core;

	core = (t_core *)params;
	mouse_cursor(core->mlx, &core->player, core->screen_size);
	if (mlx_is_key_down(core->mlx, MLX_KEY_D))
		move_right_left(&core->player, core->consts.map, 1);
	else if (mlx_is_key_down(core->mlx, MLX_KEY_A))
		move_right_left(&core->player, core->consts.map, 0);
	else if (mlx_is_key_down(core->mlx, MLX_KEY_S)
		|| mlx_is_key_down(core->mlx, MLX_KEY_DOWN))
		move_forward_backward(&core->player, core->consts.map, 1);
	else if (mlx_is_key_down(core->mlx, MLX_KEY_W)
		|| mlx_is_key_down(core->mlx, MLX_KEY_UP))
		move_forward_backward(&core->player, core->consts.map, 0);
    if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT))
        move_rotate(&core->player, 0, (float)SENSIBILITY / 10);
    if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT))
		move_rotate(&core->player, 1, (float)SENSIBILITY / 10);
    if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
}

void	inputs_hook(struct mlx_key_data key, void *params)
{
	t_core	*core;

	core = (t_core *)params;
	if (key.key == 340 && key.action == 1)
		core->player.move_speed = 25;
	else if (key.key == 340 && key.action == 0)
		core->player.move_speed = 10;
    if (key.key == 69 && key.action == 0)
        inventory(core);
}
