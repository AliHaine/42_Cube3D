# include "../../includes/sound.h"

void	init_sound_empty(void)
{
	t_sounds sound;

	sound.sound = 0;
	sound.sound_name = MINECRAFT_AMBIANT_SOUND;
	set_sound(sound);
	sound.sound_name = PLAYER_HURT_SOUND;
	set_sound(sound);
	sound.sound_name = PLAYER_WALK_SOUND;
	set_sound(sound);
	sound.sound_name = PLAYER_RUN_SOUND;
	set_sound(sound);
}

/*void	clear_sounds(t_sounds *sounds)
{
	if (sounds->player_hurt)
		BASS_StreamFree(sounds->player_hurt);
	if (sounds->player_walk)
		BASS_StreamFree(sounds->player_walk);
	if (sounds->player_run)
		BASS_StreamFree(sounds->player_run);
	BASS_Free();
}*/

bool	load_sound(Sound sound, char *path)
{
	static bool	loaded;
	t_sounds new_sound;

	msg_write_multiple(1, Messages[TRY_LOAD_SOUND], path);
	new_sound.sound_name = sound;
	loaded |= BASS_Init(-1, 48000, 0, 0, 0);
	if (!loaded)
		return (false);
	new_sound.sound = BASS_StreamCreateFile(false, path, 0, 0, 0);
	set_sound(new_sound);
	return (true);
}

void	play_sound_alt(Sound sound, bool play, bool loop)
{
	t_sounds *play_sound;

	play_sound = get_sound(sound);
	if (!play_sound->sound)
		return ;
	if (loop)
		BASS_ChannelFlags(play_sound->sound,
			BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
		BASS_ChannelPlay(play_sound->sound, 0);
	else
		BASS_ChannelPause(play_sound->sound);
}

void	play_sound(Sound sound)
{
	t_sounds *play_sound;

	play_sound = get_sound(sound);
	if (!play_sound->sound)
		return ;
	BASS_ChannelStop(play_sound->sound);
	BASS_ChannelSetPosition(play_sound->sound, 0, 0);
	BASS_ChannelPlay(play_sound->sound, 0);
}
