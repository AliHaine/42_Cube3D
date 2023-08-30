/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_accessor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:27:24 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/23 23:27:25 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/concepts/item.h"

static t_item			*g_items[ITEM_NUMBER];

t_item	*get_item(Item item)
{
	return (g_items[item]);
}

void	set_item(t_item *item)
{
	g_items[item->name] = item;
}