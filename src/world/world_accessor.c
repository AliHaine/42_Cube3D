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

static t_world			g_worlds[WORLD_NUMBER];

t_world	*get_world(int num)
{
	return (&g_worlds[num]);
}

t_world	*get_world_active(void)
{
	int	i;

	i = WORLD_NUMBER;
	while (i-- > 0)
		if (get_world(i)->is_active)
			return (get_world(i));
	return (0);
}

void	set_world(t_world world, int num)
{
	g_worlds[num] = world;
}

void	free_world(void)
{
	int	i;

	i = WORLD_NUMBER;
	while (i-- > 0)
	{
		free_tab_three(get_world(i)->world);
		free(get_world(i)->biome);
	}
}
