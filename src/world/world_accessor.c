/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_accessor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:23:49 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/22 22:23:50 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/concepts/world.h"

static t_world			g_worlds[2];

t_world	*get_world(int num)
{
	return (&g_worlds[num]);
}

t_world	*get_world_active()
{
	int	i;

	i = 2;
	while (i-- >= 0)
		if (get_world(i)->is_active)
			return (get_world(i));
	return (0);
}

void set_world(t_world world, int num)
{
	g_worlds[num] = world;
}
