#include "../../includes/includes.h"

static void	play_animation(t_animation *animation)
{
	static double	time;
	static int		i = 0;
	if (time - mlx_get_time() > animation->speed)
		return;
	time = mlx_get_time();
	if (!animation->image[i + 1])
	{
		animation->image[i]->enabled = false;
		animation->image[0]->enabled = true;
		i = 0;
		animation->is_playing = false;
		return ;
	}
	animation->image[i++]->enabled = 0;
	animation->image[i]->enabled = 1;
}

void    animation_manager(t_animation *animation)
{
	play_animation(animation);
}