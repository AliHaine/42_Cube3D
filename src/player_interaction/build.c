/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:54:38 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 18:54:39 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	set_char_at_forward(char c, t_player *player)
{
	int		x;
	int		y;
	t_world	*world;

	world = get_world_active();
	x = player->player_pos_xy[0] + cosf(player->playerangle) * 55;
	y = player->player_pos_xy[1] + sinf(player->playerangle) * 55;
	world->world[get_chunk_from_pos(x / 64, y / 64)][(y / 64) % world->height][(x / 64) % world->width] = c;
}

static void	process_build(t_player *player, t_block *block, t_item *item)
{
	static int	i = 0;

	if (i <= 0)
	{
		play_sound_alt(get_sound(BLOCK_MINING_SOUND), true, true);
		i = block->strength;
	}
	i -= item->strength;
	if (i <= 0)
	{
		play_sound_alt(get_sound(BLOCK_MINING_SOUND), false, false);
		play_sound(get_sound(BLOCK_BREAK_SOUND));
		set_char_at_forward('0', player);
		player->is_building = false;
	}
}

void	player_build(t_player *player, t_options options)
{
	char	c;

	c = get_hit_char(player);
	if (c == '0' || options.break_blocks != true || player->is_in_inventory)
		return ;
	if (c == '1')
	{
		set_char_at_forward('0', player);
		return ;
	}
	player->slot->item->animation.is_playing = true;
	process_build(player, get_block_from_char(c), player->slot->item);
}
