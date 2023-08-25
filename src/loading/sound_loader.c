#include "../../includes/includes.h"

void	sound_loader(t_options *options)
{
	if (!options->sound)
		return ;
	msg_write(1, -1, SOUND_INIT);
	usleep(450000 * LOAD);
	init_sound_empty();
	if (!load_sound(MINECRAFT_AMBIANT_SOUND, "assets/sounds/ambiant.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(PLAYER_HURT_SOUND, "assets/sounds/hurt.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(PLAYER_WALK_SOUND, "assets/sounds/player_walk.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(PLAYER_RUN_SOUND, "assets/sounds/player_run.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	msg_write(1, -1, SUCCESS);
}
