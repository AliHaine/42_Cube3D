/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:42:54 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/26 13:42:55 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
#define SOUND_H

# include "includes.h"

typedef struct s_world t_world;

typedef enum e_sound {
	NORMAL_AMBIANT_SOUND,
	NETHER_AMBIANT_SOUND,
	END_AMBIANT_SOUND,
	BACKROOM_AMBIANT_SOUND,
	PLAYER_HURT_SOUND,
	PLAYER_WALK_SOUND,
	PLAYER_RUN_SOUND,
	BLOCK_MINING_SOUND,
	BLOCK_BREAK_SOUND,
	SOUND_NUMBER,
}	Sound;

typedef struct	s_sounds
{
	Sound		sound_name;
	uint32_t	sound;
}				t_sounds;

//loader
void	sound_loader();
void	init_sound_empty(void);
bool	load_sound(Sound sound, char *path);

//accessor
t_sounds *get_sound(Sound sound);
void	set_sound(t_sounds sound);


//sound
void	clear_sounds(t_sounds *sounds);
void	play_sound_alt(t_sounds *sound, bool play, bool loops);
void	play_sound(t_sounds *sound);
void	stop_sound(t_sounds *sound);


/*
	BASS 2.4 C/C++ header file
	Copyright (c) 1999-2019 Un4seen Developments Ltd.

	See the BASS.CHM file for more detailed documentation
*/

bool		BASS_Free();
bool		BASS_Init(int device, uint32_t freq, uint32_t flags, void *win,
					  void *dsguid);
bool		BASS_StreamFree(uint32_t handle);
bool		BASS_ChannelPlay(uint32_t handle, bool restart);
bool		BASS_ChannelStop(uint32_t handle);
uint32_t	BASS_ChannelFlags(uint32_t handle, uint32_t flags, uint32_t mask);
bool		BASS_ChannelSetPosition(uint32_t handle, uint64_t pos,
									uint32_t mode);
uint32_t	BASS_StreamCreateFile(bool mem, const void *file, uint64_t offset,
								  uint64_t length, uint32_t flags);
bool		BASS_ChannelPause(uint32_t handle);

#endif
