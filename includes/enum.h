/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:47:17 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/04 19:47:18 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum {
	ERROR_MAP_CHAR,
	ERROR_PARSING_CHAR,
	ERROR_KEY_ALREADY,
	ERROR_MAP_NAME,
	ERROR_MAP_IMG,
	ERROR_MAP_EXIST,
	ERROR_ARGS,
	ERROR_PLAYER,
	ERROR_MAP_SIZE,
	SET_DEFAULT_MAP,
	STARTING,
	SUCCESS,
	NO_ERROR,
	FAILURE,
	ERROR_FATAL,
	CORE_INIT,
	SOUND_INIT,
	CHECK_MAP,
	GET_MAP_CONTENT,
	TRY_LOAD_TEXTURE,
	TRY_LOAD_SOUND,
	TRY_LOAD_WORLD,
	TRY_LOAD_ITEM,
	EMPTY_WALL,
	TRY_LOAD_COLOR,
	MINIMAP_INIT,
	DEATH_PLAYER,
	OPTIONS_CREATE_FAILURE,
	BAD_OPTION_PATERN,
	OPTIONS_LOAD,
	UNKNOWN_OPTION,
	OPTION_WRONG_VALUE,
}	MsgType;

typedef enum {
	PEACEFUL,
	EASY,
	NORMAL,
	HARD,
}	Difficulty;

static const char	*g_messages[] = {
	"\e[40;31mError \nThere is an unknow char in the world",
	"\e[40;31mError \nThere is an unknow char in the parsing",
	"\e[40;31mError \nTwo time te same key in map",
	"\e[40;31mError \nThe name of the world is not compliant",
	"\e[40;31mError \nCan't load the img",
	"\e[40;31mError \nCan't open the world file",
	"\e[40;31mError \nArgs",
	"\e[40;31mError \nNo player in the world",
	"\e[40;31mError \nThe size of the world is not supported",
	"\e[40;33mSet default world..",
	"\e[40;33mStarting..",
	"\e[40;32mSucces.",
	"\e[40;32mNo errors found.",
	"\e[40;31mFailure.",
	"\e[101;90mFATAL ERROR.",
	"\n\e[40;33mInitialization of Core values..",
	"\n\e[40;33mInitialization of sounds..",
	"\n\e[40;33mChecking the world contents..",
	"\n\e[40;33mStarting to get the world contents..",
	"\e[40;33mTrying to load texture: ",
	"\e[40;33mTrying to load sound: ",
	"\e[40;33mTrying to load world: ",
	"\e[40;33mTrying to load item: ",
	"\e[40;35mAll wall direction don't have texture, trying to set default.. ",
	"\e[40;33mTrying to load color: ",
	"\n\e[40;33mInitialization of Minimap.. ",
	"\e[40;31mYou died.",
	"\e[40;31mFailed to create options file",
	"\e[40;31mError: Option must be \"VAR=VALUE\\n\" | Ignoring this line",
	"\e[40;33mTrying to load options: ",
	"\e[40;31mError: Unknown option",
	"\e[40;31mError: Value must be \"TRUE\" or \"FALSE\"",
};

#endif
