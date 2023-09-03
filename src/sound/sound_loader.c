/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:51:52 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/26 18:51:57 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	sound_loader(void)
{
	msg_write(1, -1, SOUND_INIT);
	usleep(450000 * LOAD);
	init_sound_empty();
	if (!load_sound(NORMAL_AMBIANT_SOUND, "assets/sounds/normal_ambiant.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(NETHER_AMBIANT_SOUND, "assets/sounds/nether_ambiant.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(END_AMBIANT_SOUND, "assets/sounds/end_ambiant.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(BACKROOM_AMBIANT_SOUND, "assets/sounds/backroom_ambiant.mp3"))
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
	if (!load_sound(BLOCK_MINING_SOUND, "assets/sounds/block_mining.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	if (!load_sound(BLOCK_BREAK_SOUND, "assets/sounds/block_break.mp3"))
		msg_write(2, 2, ERROR_FATAL);
	else
		msg_write(1, -1, SUCCESS);
	msg_write(1, -1, SUCCESS);
}
