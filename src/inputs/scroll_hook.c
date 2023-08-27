/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:50:39 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/27 14:50:40 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	right_move(t_player *player, mlx_image_t *img)
{
	if (!player->slot->next || player->slot->next->slot_id > 9)
		return ;
	img->instances->x += 61;
	player->slot = player->slot->next;
}

static void	left_move(t_player *player, mlx_image_t *img)
{
	if (!player->slot->prev)
		return ;
	img->instances->x -= 61;
	player->slot = player->slot->prev;
}

void	scroll_hook(double x, double y, void *param)
{
	t_core	*core;

	(void)x;
	core = param;
	if (core->player.is_in_inventory)
		return ;
	if (y > 0)
		right_move(&core->player, core->imgs.invbar_selector);
	else
		left_move(&core->player, core->imgs.invbar_selector);
}
