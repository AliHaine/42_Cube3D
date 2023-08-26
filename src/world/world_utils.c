/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:26:14 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/17 22:26:17 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	change_active_world(t_world	*new_world)
{
	t_world	*old_world;

	old_world = get_world_active();
	stop_sound(old_world->ambiant_sound);
	old_world->is_active = false;
	new_world->is_active = true;
	play_sound(new_world->ambiant_sound);
}
