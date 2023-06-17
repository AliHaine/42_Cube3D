#include "../../includes/includes.h"

void	attack_animation(t_core *core)
{
    static double	time;
    static int		i = 0;

    if (time - mlx_get_time() > -0.01)
        return;
    time = mlx_get_time();
    if (i == 3)
    {
        core->imgs.sword[3]->enabled = 0;
        core->imgs.sword[0]->enabled = 1;
        core->imgs.animation = NO_ANIMATION;
        i = 0;
        return ;
    }
    core->imgs.sword[i++]->enabled = 0;
    core->imgs.sword[i]->enabled = 1;
}

void    animation_manager(t_imgs *imgs)
{
    (void)imgs;
}