#include "../../includes/includes.h"

void	mouse(enum mouse_key key, enum action action, enum modifier_key mkey, void *param)
{
	//mettre un cooldown pour empecher le spam
	t_sounds *s = (t_sounds *)param;

	play_sound(s->hurt);
	printf("debut\n");
	printf("%d %d %d\n", key, action, mkey);
	printf("fin\n");
}