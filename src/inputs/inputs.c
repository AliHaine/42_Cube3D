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

void	inputs(void *params)
{
	t_core	*core;


	core = (t_core *)params;

	mouse(core->mlx, &core->player);
	// Je sais pas expliquer les calculs qu'il y a dans ces fonctions inutile de demander
	// C'est de la trigonometrie c'est tout ce que je peux dire
	// Renseigne toi sur les cercles trigo et tu comprendras ptetre
	if (mlx_is_key_down(core->mlx, MLX_KEY_D))
		move_right_left(&core->player, core->consts.map, 1);
	if (mlx_is_key_down(core->mlx, MLX_KEY_A))
		move_right_left(&core->player, core->consts.map, 0);
	if (mlx_is_key_down(core->mlx, MLX_KEY_S)
		|| mlx_is_key_down(core->mlx, MLX_KEY_DOWN))
		move_forward_backward(&core->player, core->consts.map, 1);
	if (mlx_is_key_down(core->mlx, MLX_KEY_W)
		|| mlx_is_key_down(core->mlx, MLX_KEY_UP))
		move_forward_backward(&core->player, core->consts.map, 0);
	if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT))
		move_rotate(&core->player, 0);
	if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT))
		move_rotate(&core->player, 1);
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
}
