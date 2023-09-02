/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biome_accessor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:22:11 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/22 22:22:46 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

static t_biome			g_biomes[BIOME_NUMBER];

t_biome	*get_biome(Biome biome)
{
	return (&g_biomes[biome]);
}

void	set_biome(t_biome biome, int num)
{
	g_biomes[num] = biome;
}
