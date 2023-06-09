#include "../../includes/includes.h"

void	sound_loader(t_sounds *sounds)
{
	msg_write(1, -1, SOUND_INIT);
	usleep(450000 * LOAD);
	init_sound_empty(sounds);
	if (!load_sound(&sounds->ambiant, "assets/sounds/ambiant.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(&sounds->hurt, "assets/sounds/hurt.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	play_sound(sounds->ambiant);
	msg_write(1, -1, SUCCESS);
}