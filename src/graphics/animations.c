/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:51:57 by ayagmur           #+#    #+#             */
/*   Updated: 2023/06/30 23:52:00 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//playing any animation attack

static void	play_attack_animation(t_animation *animation, mlx_image_t *def)
{
	static int		i = 0;

	if (!animation->image)
		return ;
	def->enabled = false;
	if (!animation->image[i + 1])
	{
		animation->image[i - 1]->instances->x += animation->depth_xy[0];
		animation->image[i - 1]->instances->y += animation->depth_xy[1];
		animation->image[i - 1]->instances[0].enabled = false;
		def->enabled = true;
		animation->is_playing = false;
		i = 0;
		return ;
	}
	if (i > 0)
	{
		animation->image[i - 1]->instances->x += animation->depth_xy[0];
		animation->image[i - 1]->instances->y += animation->depth_xy[1];
		animation->image[i - 1]->instances[0].enabled = 0;
	}
	animation->image[i]->instances[0].x -= animation->depth_xy[0];
	animation->image[i]->instances[0].y -= animation->depth_xy[1];
	animation->image[i++]->instances[0].enabled = 1;
}

static void	play_block_animation(t_animation *animation, t_block *block)
{
	static int		i = 0;
	static double	old_time = 0;

	if (!animation->image)
		return ;
	if (mlx_get_time() < old_time + 0.1)
		return ;
	old_time = mlx_get_time();
	if (!animation->image[i + 1])
	{
		i = 0;
		return ;
	}
	block->image = animation->image[i++];
}

void	animation_listener(void)
{
	t_block	*block;
	t_item	*item;
	int		i;

	i = 0;
	item = get_item(i);
	while (item)
	{
		if (item->animation.is_playing)
			play_attack_animation(&item->animation, item->image);
		item = get_item(i++);
	}
	i = 0;
	block = get_block(i);
	while (block)
	{
		if (block->animation.is_playing)
			play_block_animation(&block->animation, block);
		block = get_block(i++);
	}
}
