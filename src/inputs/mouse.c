#include "../../includes/includes.h"
#include "../../includes/defines.h"
void    resize_hook(int height, int width, void *params)
{
    *((int*)params) = height;
    *((int*)params + 1) = width;
}

void    mouse(mlx_t *mlx, t_player *player, const int screen_size[2])
{
    int x;
    int y;
    int diff;
    int screen_middle_x;
    float rotation_speed;

    screen_middle_x = screen_size[0] / 2;
    mlx_get_mouse_pos(mlx, &x, &y);
    diff = abs(screen_middle_x - x);
    rotation_speed = (float)diff / screen_middle_x * SENSIBILITY;
    if (x > screen_middle_x)
        move_rotate(player, 1, rotation_speed);
    else if (x < screen_middle_x)
        move_rotate(player, 0, rotation_speed);
    mlx_set_mouse_pos(mlx, screen_middle_x, screen_size[1] / 2);
}
