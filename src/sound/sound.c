/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:51:21 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/26 18:51:22 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/sound.h"

void	init_sound_empty(void)
{
	t_sounds sound;

	sound.sound = 0;
	sound.sound_name = NORMAL_AMBIANT_SOUND;
	set_sound(sound);
	sound.sound_name = NETHER_AMBIANT_SOUND;
	set_sound(sound);
	sound.sound_name = BACKROOM_AMBIANT_SOUND;
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

void	play_sound_alt(t_sounds *sound, bool play, bool loop)
{
	if (!sound->sound)
		return ;
	if (loop)
		BASS_ChannelFlags(sound->sound,
			BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
		BASS_ChannelPlay(sound->sound, 0);
	else
		BASS_ChannelPause(sound->sound);
}

void	play_sound(t_sounds *sound)
{
	if (!sound->sound)
		return ;
	BASS_ChannelStop(sound->sound);
	BASS_ChannelSetPosition(sound->sound, 0, 0);
	BASS_ChannelPlay(sound->sound, 0);
}

void	stop_sound(t_sounds *sound)
{
	if (!sound->sound)
		return ;
	BASS_ChannelStop(sound->sound);
	BASS_ChannelSetPosition(sound->sound, 0, 0);
}
