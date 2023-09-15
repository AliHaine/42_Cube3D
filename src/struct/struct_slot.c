/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_slot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:38:24 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/07 20:38:26 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static t_slot	*add_new_noed(mlx_t *mlx, short val, t_slot *current, t_item *hand_item)
{
	current->prev = malloc(sizeof(t_slot));
	current->prev->icon_instance = -1;
	current->prev->bar_icon_instance = -1;
	current->prev->slot_id = val;
	current->prev->item = hand_item;
	current->items_number = 1;
	current->items_number_img = mlx_put_string(mlx, "1", 0, 0);
	current->items_number_img_bar = mlx_put_string(mlx, "1", 0, 0);
	current->items_number_img_bar->instances[0].y = (SCREEN_HEIGHT - 85) + 25;
	current->items_number_img->instances->enabled = false;
	current->items_number_img_bar->instances->enabled = false;
	current->items_number_img->instances[0].z = 11;
	current->bar_mutex = false;
	current->prev->next = current;
	return (current->prev);
}

static t_slot	*add_first_noed(mlx_t *mlx, t_item *hand_item)
{
	t_slot	*first;

	first = malloc(sizeof(t_slot));
	first->slot_id = 47;
	first->icon_instance = -1;
	first->bar_icon_instance = -1;
	first->item = hand_item;
	first->items_number = 1;
	first->items_number_img = mlx_put_string(mlx, "1", 0, 0);
	first->items_number_img_bar = mlx_put_string(mlx, "1", 0, 0);
	first->items_number_img_bar->instances[0].y = (SCREEN_HEIGHT - 85) + 25;
	first->items_number_img->instances->enabled = false;
	first->items_number_img_bar->instances->enabled = false;
	first->bar_mutex = false;
	first->items_number_img->instances[0].z = 11;
	first->next = 0;
	return (first);
}

void	free_slot(t_slot *slot)
{
	t_slot	*current;

	while (slot->prev)
		slot = slot->prev;
	current = slot;
	while (current)
	{
		slot = slot->next;
		free(current);
		current = slot;
	}
}

void	setup_slot_struct(mlx_t *mlx, t_player *player)
{
	int	i;

	i = 47;
	player->slot = add_first_noed(mlx, get_item(HAND));
	while (i-- > 0)
		player->slot = add_new_noed(mlx, i, player->slot, get_item(HAND));
	player->slot = player->slot->next;
	player->slot->prev = 0;
}

t_slot	*get_first_slot(t_slot *slot)
{
	t_slot	*copy;

	copy = slot;
	while (copy->slot_id != 1)
		copy = copy->prev;
	return (copy);
}
