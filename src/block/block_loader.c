/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:23 by ayagmur           #+#    #+#             */
/*   Updated: 2023/07/31 17:17:25 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/* Create a new block with the specified properties
 *
 * Before call this function, make sure to follow these steps :
 * - Add the block in UPPERCASE to the enum Block,
 * - Then add the block name in BlockName.
 * - Add the texture of block in asset/blocks, The texture name must match the enum value and BlockName.
 *
 * @param block_name	The Enum 'Block' value representing the type of Block.
 * @param item			The item associate with
 * the block (for looting or other..)
 * @param strength		Higher values make harder the block to break. Low value is like ~10-, and high value is like ~ 120+
 * @param block_char	The char associate to the Block, each block must have UNIQUE char
 * @param is_rigid		Whether the block is rigid player can't through */

static void	create_block(Block block_name, t_item *item, int strength, mlx_t *mlx, char block_char, bool is_rigid)
{
	char	*path;
	t_block	*block;

	block = malloc(sizeof(t_block));
	block->name = block_name;
	block->item = item;
	block->strength = strength;
	block->block_char = block_char;
	block->is_rigid = is_rigid;
	block->animation.is_playing = false;
	path = malloc(sizeof(char) * (ft_strlen(BlockName[block_name]) + 19));
	put_two_string(path, "assets/blocks/", BlockName[block_name], 0);
	if (!set_image_from_path(mlx, path, &block->image))
		msg_write(2, 2, ERROR_FATAL);
	free(path);
	set_block(block);
}

static void	create_block_animation(t_block *block, int anim_size, mlx_t *mlx)
{
	int		i;
	char	*path;

	i = 0;
	block->animation.is_playing = true;
	block->animation.depth_xy[0] = 0;
	block->animation.depth_xy[1] = 0;
	block->animation.image = malloc(sizeof(mlx_image_t) * (anim_size + 1));
	path = malloc(sizeof(char) * (ft_strlen(BlockName[block->name]) + 20));
	while (i++ < anim_size)
	{
		put_two_string(path, "assets/blocks/", BlockName[block->name], ft_itoa(i));
		if (!set_image_from_path(mlx, path, &block->animation.image[i - 1]))
		{
			free(path);
			msg_write(2, 2, ERROR_FATAL);
		}
		mlx_image_to_window(mlx, block->animation.image[i - 1], SCREEN_WIDTH / 1.4, SCREEN_HEIGHT - 290);
		block->animation.image[i - 1]->instances[0].enabled = false;
		block->animation.image[i - 1]->instances[0].z = 8;
		free(path);
		if (i >= 10)
			path = malloc(sizeof(char) * (ft_strlen(BlockName[block->name]) + 21));
		else
			path = malloc(sizeof(char) * (ft_strlen(BlockName[block->name]) + 21));
	}
	free(path);
	block->animation.image[i - 1] = 0;
}

void	block_loader(mlx_t *mlx)
{
	create_block(NETHERPORTAL, 0, 1, mlx, 'Z', false);
	create_block_animation(get_block(NETHERPORTAL), 14, mlx);
	create_block(NETHERRACK, 0, 10, mlx, 'R', true);
	create_block(OBSIDIAN, 0, 120, mlx, 'O', true);
	create_block(CRYING_OBSIDIAN, 0, 2, mlx, 'L', true);
	create_block(CRACKED_DEEPSLAT_TILES, 0, 2, mlx, 'P', true);
	create_block(DEEPSLATE_COAL_ORE, 0, 2, mlx, 'I', true);
	create_block(NETHER_WART_BLOCK, 0, 2, mlx, 'Y', true);
	create_block(GRASS, 0, 2, mlx, '@', true);
	create_block(BACKROOM_YELLOW, 0, 55, mlx, '[', true);
	create_block(BACKROOM_FLOOR, 0, 45, mlx, ']', true);
	create_block(BUG, 0, 0, mlx, '(', false);
	create_block(CHISELED_NETHER_BRICKS, 0, 45, mlx, 'N', true);
	create_block(CRACKED_NETHER_BRICKS, 0, 45, mlx, 'B', true);
	create_block(DRAGON_EGG, 0, 0, mlx, 'D', true);
	create_block(GRAY_GLAZED_TERRACOTTA, 0, 0, mlx, '?', true);
	create_block(REDSTONE_BLOCK, 0, 0, mlx, '=', true);
	create_block(RED_MUSHROOM_BLOCK, 0, 0, mlx, '+', true);
	create_block(RED_GLAZED_TERRACOTTA, 0, 0, mlx, '|', true);
	create_block(CRIMSON_NYLIUM, 0, 69, mlx, '}', true);
	create_block(CRIMSON_NYLIUM_SIDE, 0, 68, mlx, '{', true);
	create_block(FLOWER, 0, 0, mlx, 'T', false);
	create_block(BLOCK_END_PORTAL, 0, 350, mlx, '$', false);
	create_block(BLOCK_END_STONE, 0, 45, mlx, 'x', true);
	create_block(BLOCK_END_STONE_BRICKS, 0, 80, mlx, 'X', true);
	create_block(BLOCK_CHORUS_PLANT, 0, 45, mlx, 'k', true);
	create_block(BLOCK_CHORUS_FLOWER_DEAD, 0, 150, mlx, 'K', true);
	create_block(BLOCK_CHORUS_FLOWER, 0, 85, mlx, 'l', true);

}
