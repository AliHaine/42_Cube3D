/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_accessor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:51:32 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/26 18:51:33 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/sound.h"

static t_sounds g_sounds[SOUND_NUMBER];

t_sounds	*get_sound(Sound sound)
{
	return (&g_sounds[sound]);
}

void	set_sound(t_sounds sound)
{
	g_sounds[sound.sound_name] = sound;
}
