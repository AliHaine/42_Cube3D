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
	if (new_world->world_name == old_world->world_name)
		new_world = get_world(WORLD_DEFAULT);
	stop_sound(old_world->ambiant_sound);
	old_world->is_active = false;
	new_world->is_active = true;
	play_sound(new_world->ambiant_sound);
}

void	replace_on_world(float coords[][2], int num)
{
	if (num == 1)
		coords[0][1] += get_world_active()->height * 64;
	else if (num == 3)
		coords[0][0] += get_world_active()->width * 64;
	else if (num == 5)
		coords[0][0] -= get_world_active()->width * 64;
	else if (num == 7)
		coords[0][1] -= get_world_active()->height * 64;
}
