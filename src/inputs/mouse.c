/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:18:53 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/16 14:18:59 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	mouse(enum mouse_key key, enum action action, enum modifier_key mkey, void *param)
{
	static double	time = -2;
	t_core			*core;

	(void) mkey;
	core = (t_core *)param;
	if (!player_have_enough_energy(&core->player, 20) || core->player.is_in_inventory == true)
		return ;
	if (key == 0 && action == 0)
    	hit_player(&core->player, &core->imgs);
	else if (key == 1 && action == 0 )
		heal_player(&core->player, &core->imgs);
	if (key != 0 || action == 1)
		return ;
	if (time - mlx_get_time() >= -0.1)
		return ;
	time = mlx_get_time();
	core->player.slot->item->animation.is_playing = true;
	if (get_forward_char(&core->player) == '1'
		&& core->options.break_blocks == true)
		set_char_at_forward('0', &core->player, get_world_active());
	play_sound(PLAYER_HURT_SOUND);
}
