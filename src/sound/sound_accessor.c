# include "../../includes/sound.h"

static t_sounds g_sounds[4];

t_sounds *get_sound(Sound sound)
{
	return (&g_sounds[sound]);
}

void	set_sound(t_sounds sound)
{
	g_sounds[sound.sound_name] = sound;
}
