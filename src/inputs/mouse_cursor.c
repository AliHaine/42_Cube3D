#include "../../includes/includes.h"

void	set_cursor_at_pos(int height, int width, mlx_image_t *image)
{
	image->instances[0].x = height;
	image->instances[0].y = width;

}

void    resize_hook(int height, int width, void *params)
{
	t_core *core;

	core = (t_core *)params;
	core->screen_size[0] = height;
	core->screen_size[1] = width;
	set_cursor_at_pos(height, width, core->imgs.crosshair);
}

void    mouse_cursor(mlx_t *mlx, t_player *player, const int screen_size[2])
{
    int x;
    int y;
    int diff;
    int screen_middle_x;
    float rotation_speed;

    if (player->is_in_inventory == true)
        return ;
    screen_middle_x = screen_size[0] / 2;
    if (mlx_get_time() < 0.8)
    {
        mlx_set_mouse_pos(mlx, screen_middle_x, screen_size[1] / 2);
        return ;
    }
    mlx_get_mouse_pos(mlx, &x, &y);
    mlx_set_mouse_pos(mlx, screen_middle_x, screen_size[1] / 2);
    diff = abs(screen_middle_x - x);
    rotation_speed = (float)diff / screen_middle_x * SENSIBILITY;
    if (x > screen_middle_x)
        move_rotate(player, 1, rotation_speed);
    else if (x < screen_middle_x)
        move_rotate(player, 0, rotation_speed);
}
