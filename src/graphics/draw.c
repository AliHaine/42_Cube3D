
#include "../../includes/includes.h"

void	draw_sprite(t_core *core, t_ray ray, t_checkpoint check, int r)
{
	(void)core, (void)ray, (void)check, (void)r;
}


static void	draw_door(t_core *core, t_ray ray, t_checkpoint check, int r)
{
	float			ray_distance;
	float			wall_height;
	uint32_t		color;
	int				texture_xy[2];
	int				py;

	ray_distance = calc_ray_dist(core, check.checkpoint_x, check.checkpoint_y,
			ray.ray_angle);
	texture_xy[0] = get_obstacle_offset(obstacle_direction(core, check, ray),
			check);
	wall_height = (SCREEN_HEIGHT * 64) / ray_distance;
	py = (SCREEN_HEIGHT - wall_height) / 2;
	while (py >= 0 && py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
				* TEXTURE_SIZE) / wall_height / 2;
		color = get_color(core->imgs.door_texture, ray_distance / FOG_DISTANCE,
				texture_xy);
		if (color != 0)
			mlx_put_pixel(core->imgs.img_3d, r, py, color);
		py++;
	}
}

void	draw_obstacles(t_core *core, t_ray ray, int r)
{
	int	i;

	i = -1;
	while (++i < ray.checkpoint_number)
	{
		if (ray.checkpoints[i].obstacle == 'D')
			draw_door(core, ray, ray.checkpoints[i], r);
		else if (ray.checkpoints[i].obstacle == 'Z')
			draw_sprite(core, ray, ray.checkpoints[i], r);
	}
}

void	draw_columns(t_core *core, t_ray ray, int r)
{
	float			wall_height;
	int				py;
	uint32_t		color;
	int				texture_xy[2];

	texture_xy[0] = get_offset(ray.wall_direction, ray);
	wall_height = (SCREEN_HEIGHT * 64) / ray.ray_dist;
	py = 0;
	while (py < (SCREEN_HEIGHT - wall_height) / 2 && py < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, r, py++, core->consts.top_color);
	while (py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		texture_xy[1] = ((py * 2 - SCREEN_HEIGHT + wall_height)
				* TEXTURE_SIZE) / wall_height / 2;
		color = get_color(core->imgs.wall_texture[ray.wall_direction],
ray.ray_dist / FOG_DISTANCE, texture_xy);
		mlx_put_pixel(core->imgs.img_3d, r, py++, color);
	}
	while (py < SCREEN_HEIGHT)
		mlx_put_pixel(core->imgs.img_3d, r, py++, core->consts.bot_color);
}
