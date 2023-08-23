/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:27:38 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/23 23:27:40 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEM_H
#define ITEM_H

# include "../includes.h"

typedef enum {
	HAND,
	SWORD_NETHER,
	SWORD_DIAMOND,
	SWORD_RUBY,
	SWORD_IRON,
	STICK,
	DIAMOND,
	IRON,
	FLINT,
	LIGHTER,
	DIAMOND_PICKAXE
}   Item;

static const char *ItemName[] = {
		"hand",
		"sword_nether",
		"sword_diamond",
		"sword_ruby",
		"sword_iron",
		"stick",
		"diamond",
		"iron",
		"flint",
		"lighter",
		"diamond_pickaxe"
};

typedef struct s_item
{
	Item			name;
	int				durability;
	int				damage;
	int				strength;
	int				range;
	int				max_stack;
	mlx_image_t		*image;
	mlx_image_t		*icon;
	int             instance_number;
	t_animation 	animation;
}	t_item;

//loader
void	item_loader(t_core *core);

//accessor
t_item	*get_item(Item item);
void	set_item(t_item *item);

void    give_item(t_core *core, t_item *item, int slot_id, int number);

#endif
