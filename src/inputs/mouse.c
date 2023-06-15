#include "../../includes/includes.h"

void	mouse(enum mouse_key key, enum action action, enum modifier_key mkey, void *param)
{
	static double	time = -2;
	t_core			*core;

	(void) mkey;
	core = (t_core *)param;
	if (key != 0 || action == 1)
		return ;
	if (time - mlx_get_time() >= -0.5)
		return ;
	time = mlx_get_time();
	core->test = 1;
	if (get_forward_char(&core->player, core->consts.map) == '1') {
		set_char_at_forward(0, &core->player, core->consts.map);
	}
	play_sound(core->sounds.hurt);
}