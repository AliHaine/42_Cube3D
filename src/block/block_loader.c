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

void	block_loader(t_core *core)
{
	create_block(PORTAL, 0, 1, core->mlx, 'Z', false);
	create_block_animation(get_block(PORTAL), 14, core->mlx);
	create_block(NETHERRACK, 0, 1, core->mlx, 'R', true);
	create_block(OBSIDIAN, 0, 2, core->mlx, 'O', true);
	create_block(CRYING_OBSIDIAN, 0, 2, core->mlx, 'L', true);
	create_block(CRACKED_DEEPSLAT_TILES, 0, 2, core->mlx, 'P', true);
	create_block(DEEPSLATE_COAL_ORE, 0, 2, core->mlx, 'I', true);
	create_block(NETHER_WART_BLOCK, 0, 2, core->mlx, 'Y', true);
	create_block(GRASS, 0, 2, core->mlx, '@', true);
	create_block(BACKROOM_YELLOW, 0, 0, core->mlx, '[', true);
	create_block(BACKROOM_FLOOR, 0, 0, core->mlx, ']', true);
	create_block(BUG, 0, 0, core->mlx, '(', false);
}
