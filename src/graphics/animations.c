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

	def->enabled = false;
	if (!animation->image[i + 1])
	{
		animation->image[i - 1]->instances->x += 150;
		animation->image[i - 1]->instances[0].enabled = false;
		def->enabled = true;
		animation->is_playing = false;
		i = 0;
		return ;
	}
	if (i > 0)
	{
		animation->image[i - 1]->instances->x += 150;
		animation->image[i - 1]->instances[0].enabled = 0;
	}
	animation->image[i]->instances[0].x -= 150;
	animation->image[i++]->instances[0].enabled = 1;
}

void    animation_listener(t_item *items)
{
	//changer pour une quantite indefini d'anim
	if (items[0].animation.is_playing)
	{
		play_attack_animation(&items[0].animation, items[0].image);
	} else if (items[1].animation.is_playing) {
		play_attack_animation(&items[1].animation, items[1].image);
	} else if (items[2].animation.is_playing) {
        play_attack_animation(&items[2].animation, items[2].image);
    } else if (items[3].animation.is_playing) {
        play_attack_animation(&items[3].animation, items[3].image);
    } else if (items[4].animation.is_playing) {
		play_attack_animation(&items[4].animation, items[4].image);
	}
}
