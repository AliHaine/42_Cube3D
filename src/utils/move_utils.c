#include "../../includes/includes.h"

char	get_forward_char(t_player *player)
{
	t_world	*world;

	world = get_world_active();
	return (world->world[4][(int)((player->player_pos_xy[1] + (sinf(player->playerangle)
															 * player->move_speed)) / 64) % world->height][(int)((player->player_pos_xy[0] +
																												(cosf(player->playerangle) * player->move_speed)) / 64) % world->width]);
}

bool	is_move_key_down(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_A) ||
			mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN) ||
				mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_UP))
		return (true);
	return (false);
}

bool	is_player_running(t_player *player)
{
	if (player->move_speed > MOVE_SPEED)
		return (true);
	return (false);
}

bool	is_player_under_block(t_player *player)
{
	t_world	*world;
	char	c;

	world = get_world_active();
	c = world->world[get_chunk_from_pos((int)player->player_pos_xy[0] / 64, (int)player->player_pos_xy[1] / 64)][(int)player->player_pos_xy[1] / 64 % world->height][(int)player->player_pos_xy[0] / 64 % world->width];
	//printf("%f %f %d %d %d\n", player->player_pos_xy[0], player->player_pos_xy[1], (int)player->player_pos_xy[0] / 64 % world->height, (int)player->player_pos_xy[1] / 64 % world->height,
	//	   get_chunk_from_pos((int)player->player_pos_xy[0] / 64, (int)player->player_pos_xy[1] / 64));
	if (c != '0' && c == '1' || is_rigid_block(get_block_name_from_char(c)))
		return (true);
	return (false);
}
