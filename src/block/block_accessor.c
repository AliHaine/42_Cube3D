/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_accessor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:50:38 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/23 22:50:39 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/concepts/block.h"

static t_block	*g_blocks[12];

t_block	*get_block(Block block)
{
	return (g_blocks[block]);
}

t_block *get_block_from_char(char block_char)
{
	int	i;

	i = 0;
	while (g_blocks[i])
	{
		if (g_blocks[i]->block_char == block_char)
			return (g_blocks[i]);
		i++;
	}
	return (0);
}

Block get_block_name_from_char(char block_char)
{
	int	i;

	i = 0;
	while (g_blocks[i])
	{
		if (g_blocks[i]->block_char == block_char)
			return (g_blocks[i]->name);
		i++;
	}
	return (0);
}

mlx_image_t	*get_block_image(Block block)
{
	return (g_blocks[block]->image);
}

int	get_block_number()
{
	int	i;

	i = 0;
	while (g_blocks[i++]);
	return (i);
}

void	set_block(t_block *block)
{
	g_blocks[block->name] = block;
	g_blocks[11] = 0;
}
