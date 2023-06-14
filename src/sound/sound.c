/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sound_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:46:06 by ttranche          #+#    #+#             */
/*   Updated: 2021/03/22 13:03:38 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TTRANCHE C file https://github.com/ttranche
	See the for more detailed :
	https://github.com/ttranche/cub3D/blob/main/bonus/cub_sound_bonus.c
*/


# include "bass/bass.h"
# include "../../includes/includes.h"

void	init_sound_empty(t_sounds *sounds)
{
	sounds->hurt = 0;
}

void	clear_sounds(t_sounds *sounds)
{
	if (sounds->hurt)
		BASS_StreamFree(sounds->hurt);
	BASS_Free();
}

bool	load_sound(uint32_t *s, char *path)
{
	static bool loaded;

	loaded |= BASS_Init(-1, 48000, 0, 0, 0);
	if (!loaded || *s)
		return (false);
	*s = BASS_StreamCreateFile(false, path, 0, 0, 0);
	return (true);
}

void	play_sound_alt(uint32_t s, bool play, bool loop)
{
	if (!s)
		return ;
	if (loop)
		BASS_ChannelFlags(s,
			BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
		BASS_ChannelPlay(s, 0);
	else
		BASS_ChannelPause(s);
}

void	play_sound(uint32_t s)
{
	if (!s)
		return ;
	BASS_ChannelStop(s);
	BASS_ChannelSetPosition(s, 0, 0);
	BASS_ChannelPlay(s, 0);
}
