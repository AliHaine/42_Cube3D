/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biome_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 23:39:24 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/20 23:39:26 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	get_biomes_size(t_biome **biomes)
{
	int	i;

	i = 0;
	if (!biomes)
		return (0);
	while (*(biomes++))
		i++;
	return (i);
}

t_biome	*get_random_biome(t_biome **biomes)
{
	int	biomes_size;

	biomes_size = get_biomes_size(biomes);
	if (biomes_size == 0)
		return (0);
	return (biomes[get_rand_num(biomes_size, 1)]);
}

t_block	get_random_block_from_biome(t_biome *biome)
{
	return (biome->block[get_rand_num(biome->block_number, 1)]);
}
