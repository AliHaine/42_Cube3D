/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 23:51:57 by ayagmur           #+#    #+#             */
/*   Updated: 2024/01/24 15:37:20 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void    moving_handling_item(t_core *core)
{
    static int p = 0;
    static int pos = 0;
    static t_slot *save = 0;
    static double time = 0;

    if (save == 0)
        save = core->player.slot;
    else if (core->player.slot != save) {
        save->item->image->instances[0].y = SCREEN_HEIGHT - save->item->image->height;
        save = core->player.slot;
        pos = 0;
    }
    if (p == 0 && mlx_get_time() - time >= 0.05 && pos < 4) {
        p = 0;
        pos += 1;
        time = mlx_get_time();
        save->item->image->instances[0].y += 7;
    } else if (p == 1 || (mlx_get_time() - time >= 0.05 && pos == 4)) {
        if (pos == 0) {
            p = 0;
            return;
        }
        p = 1;
        pos -= 1;
        time = mlx_get_time();
        save->item->image->instances[0].y -= 7;
    }
}

//playing any animation attack

static void	play_attack_animation(t_animation *animation, mlx_image_t *def)
{
	static int	i = 0;

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

	i = ITEM_NUMBER;
	while (i-- > 0)
	{
		item = get_item(i);
		if (item->animation.is_playing)
			play_attack_animation(&item->animation, item->image);
	}
	i = BLOCK_NUMBER;
	while (i-- > 0)
	{
		block = get_block(i);
		if (block->animation.is_playing)
			play_block_animation(&block->animation, block);
	}
}
