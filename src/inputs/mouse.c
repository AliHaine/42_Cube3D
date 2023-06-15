#include "../../includes/includes.h"

void	mouse(enum mouse_key key, enum action action, enum modifier_key mkey, void *param)
{
	static double	time = -2;
	t_sounds		*s;

	(void) mkey;
	s = (t_sounds *)param;
	if (action == 1)
		return ;
	if (time - mlx_get_time() >= -2)
		return ;
	if (key == 0)
		time = mlx_get_time();
	play_sound(s->hurt);
}