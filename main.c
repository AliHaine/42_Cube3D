
#include "MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define MAP_HEIGHT 12
#define MAP_WIDTH 20
#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1280
#define WALK_SPEED 5
#define PI 3.141592653589793
#define RAY_RESOLUTION 5
#define FOV 90
#define NUM_RAYS 64;

struct	t_core
{
	mlx_t			*mlx;
	mlx_image_t		*img_map;
	mlx_image_t		*img_dot;
	mlx_texture_t	*texture_dot;
	uint32_t		color;

	float			playerpos[2];
	float			playerangle;
};

int	map[12][20] =
{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	draw_map(struct t_core *core)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] == 1)
			{
				for (int py = y * 64; py < SCREEN_HEIGHT && py < (y * 64) + 64; py++)
				{
					for (int px = x * 64; px < SCREEN_WIDTH && px < (x * 64) + 64; px++)
					{
						mlx_put_pixel(core->img_map, px, py, core->color);
					}
				}
			}
		}
	}
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}


void	engine(void *params) {
	struct t_core *core;

	core = (struct t_core *) params;
	if (mlx_is_key_down(core->mlx, MLX_KEY_D)
		&& map[(int) (core->playerpos[1] / 64)][(int) (core->playerpos[0] + 18 + WALK_SPEED) / 64] != 1
		&& map[(int) ((core->playerpos[1] + 18) / 64)][(int) (core->playerpos[0] + 18 + WALK_SPEED) / 64] != 1) {
		core->playerpos[0] += cos((core->playerangle * 180 / M_PI) + M_PI * 2) * WALK_SPEED;
		core->playerpos[1] -= sin((core->playerangle * 180 / M_PI) + M_PI * 2) * WALK_SPEED;
	}
	if (mlx_is_key_down(core->mlx, MLX_KEY_A)
		&& map[(int) (core->playerpos[1] / 64)][(int) ((core->playerpos[0] - 2) - WALK_SPEED) / 64] != 1
		&& map[(int) ((core->playerpos[1] + 18) / 64)][(int) ((core->playerpos[0] - WALK_SPEED)) / 64] != 1) {
		core->playerpos[0] -= WALK_SPEED;
	}
	if (mlx_is_key_down(core->mlx, MLX_KEY_S)
		&& map[(int) ((core->playerpos[1] + 18 + WALK_SPEED) / 64)][(int) (core->playerpos[0]) / 64] != 1
		&& map[(int) ((core->playerpos[1] + WALK_SPEED) + 18) / 64][(int) (core->playerpos[0] + 18) / 64] != 1) {
		core->playerpos[1] += WALK_SPEED;
	}
	if (mlx_is_key_down(core->mlx, MLX_KEY_W)
		&& map[(int) (((core->playerpos[1] - 5) - WALK_SPEED) / 64)][(int) (core->playerpos[0]) / 64] != 1
		&& map[(int) ((core->playerpos[1] - WALK_SPEED) / 64)][(int) (core->playerpos[0] + 16) / 64] != 1) {
		core->playerpos[1] -= WALK_SPEED;
	}
	if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT)) {
		core->playerangle += 0.0005;
		if (core->playerangle > 360)
			core->playerangle -= 360;
		//printf("player angle: %f(degree) %f(radians)\n", core->playerangle, core->playerangle * (PI / 180));
	}
	if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT)) {
		core->playerangle -= 0.0005;
		if (core->playerangle < 0)
			core->playerangle += 360;
		//printf("player angle: %f(degree) %f(radians)\n", core->playerangle, core->playerangle * (PI / 180));
	}
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE)) {
		mlx_close_window(core->mlx);
	}

	mlx_delete_image(core->mlx, core->img_dot);
	mlx_delete_image(core->mlx, core->img_map);
	core->img_map = mlx_new_image(core->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	core->img_dot = mlx_texture_to_image(core->mlx, core->texture_dot);
	draw_map(core);

	float ray_x = core->playerpos[0];
	float ray_y = core->playerpos[1];

	while (ray_x >= 0 && ray_x < MAP_WIDTH && ray_y >= 0 && ray_y < MAP_HEIGHT && map[(int)ray_x][(int)ray_y] == 0)
	{
		ray_x += cos(core->playerangle * (PI / 180));
		ray_y += sin(core->playerangle * (PI / 180));
	}
	printf("rx: %f ry: %f px: %f py: %f\n", ray_x, ray_y, core->playerpos[0], core->playerpos[1]);

	mlx_image_to_window(core->mlx, core->img_map, 0, 0);
	mlx_image_to_window(core->mlx, core->img_dot, core->playerpos[0], core->playerpos[1]);
	mlx_image_to_window(core->mlx, core->img_dot, ray_x, ray_y);
	core->img_map->instances[0].z = 1;
	core->img_dot->instances[0].z = 2;
}

int	main(void)
{
	struct t_core	*core = (struct t_core *)malloc(sizeof(struct t_core));

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	core->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	core->img_map = mlx_new_image(core->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	core->texture_dot = mlx_load_png("red_dot.png");
	core->img_dot = mlx_texture_to_image(core->mlx, core->texture_dot);
	core->color = (150<<24) + (150<<16) + (150<<8) + 255;
	core->playerpos[0] = 5 * 64;
	core->playerpos[1] = 5 * 64;
	core->playerangle = 0;
	draw_map(core);
	mlx_image_to_window(core->mlx, core->img_map, 0, 0);
	mlx_image_to_window(core->mlx, core->img_dot, core->playerpos[0], core->playerpos[1]);

	mlx_loop_hook(core->mlx, &engine, core);
	mlx_loop(core->mlx);
	mlx_delete_image(core->mlx, core->img_map);
	mlx_delete_image(core->mlx, core->img_dot);
	mlx_delete_texture(core->texture_dot);
	mlx_close_window(core->mlx);
	mlx_terminate(core->mlx);
	free(core);
	return (0);
}
