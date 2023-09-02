/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biome_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:17:47 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/02 16:17:48 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

/* Create new Biome with specified Block
 *
 * @param block_number	Set the number of Block that make up your Biome
 * @param ...			Set the Enum value of the Blocks making up your Biome, you can define
 * 						as many blocks you want but do not set 2 times the same Block in same Biome
 *
 * */

static t_biome	biome_creator(int block_number, ...)
{
	t_biome	biome;
	va_list	va_biome;

	va_start(va_biome, block_number);
	biome.block = malloc(sizeof(t_block) * block_number);
	biome.block_number = block_number;
	while (block_number-- > 0)
		biome.block[block_number] = *get_block(va_arg(va_biome, Block));
	va_end(va_biome);
	return (biome);
}

void	biome_loader(void)
{
	set_biome(biome_creator(6, NETHERRACK, NETHER_WART_BLOCK, OBSIDIAN, CRYING_OBSIDIAN, CRACKED_DEEPSLAT_TILES, DEEPSLATE_COAL_ORE), BIOME_DARK);
	set_biome(biome_creator(1, BACKROOM_YELLOW), BIOME_BACKROOM);
	set_biome(biome_creator(4, CHISELED_NETHER_BRICKS, CRACKED_NETHER_BRICKS, DRAGON_EGG, GRAY_GLAZED_TERRACOTTA), BIOME_DRAGON);
	set_biome(biome_creator(4, REDSTONE_BLOCK, RED_GLAZED_TERRACOTTA, CRIMSON_NYLIUM, CRIMSON_NYLIUM_SIDE), BIOME_RED);
}
