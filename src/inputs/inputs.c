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


static void moving_inputs(mlx_t *mlx, t_player *player, t_map *map)
{
	if (!player->can_move)
	{
		player->is_moving = false;
		return ;
	}
	player->is_moving = true;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
    {
        if (get_right_char(player, map) == '0')
            move_right(player);
    }
	else if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
        if (get_left_char(player, map) == '0')
            move_left(player);
    }
	else if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
    {
        if (get_backward_char(player, map) == '0')
            move_backward(player);
    }
	else if (mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
    {
        if (get_forward_char(player, map) == '0')
            move_forward(player);
//		printf("coords x: %f, coords y:%f\n", player->player_coords_xy[0], player->player_coords_xy[1]);
//		printf("coords posx: %f, coords posy:%f\n", player->player_pos_xy[0], player->player_pos_xy[1]);
//		printf("cell x:%d, cell y: %d\n", player->player_cell_xy[0], player->player_cell_xy[1]);
//		printf("\n");
    }
	else
		player->is_moving = false;
	player->player_cell_xy[0] = (int)(player->player_pos_xy[0] / 64);
	player->player_cell_xy[1] = (int)(player->player_pos_xy[1] / 64);
}

int	get_chunk_from_pos2(int x, int y, int m_height, int m_width)
{
	int i;

	i = 0;
	printf("start %d %d %d\n--------------------\n", y, x, m_height);
	if (y < (m_height - 1))
	{
		printf("11\n");
		while (i++ < 4)
		{
			if (x < (m_width - 1) * i)
				return (i - 1);
		}
	}
	else if (y < m_height * 2)
	{
		printf("22\n");
		while (i++ < 4)
		{
			if (x < m_width * i)
				return ((i - 1) + 3);
		}
	}
	else
	{
		printf("33\n");
		while (i++ < 4)
		{
			if (x < m_width * i)
				return ((i - 1) + 6);
		}
	}
	//printf("rien %d %d\n-------------------------\n", x, y);
	return (0);
}

void	inputs(void *params)
{
	t_core	*core;

	core = (t_core *)params;
	mouse_cursor(core->mlx, &core->player, core->screen_size);
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core->mlx);
	rotation_inputs(core->mlx, &core->player);
	moving_inputs(core->mlx, &core->player, &core->maps[get_active_world(core->maps)]);
    if (is_player_chunk_change(&core->player, &core->maps[get_active_world(core->maps)]))
		world_dynamic_generator(&core->maps[0], &core->player);
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
