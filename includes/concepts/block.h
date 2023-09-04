/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:40:58 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/22 20:40:59 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_H
# define BLOCK_H

# include "../includes.h"

typedef struct s_item	t_item;

typedef enum {
	NETHERPORTAL,
	NETHERRACK,
	OBSIDIAN,
	CRYING_OBSIDIAN,
	CRACKED_DEEPSLAT_TILES,
	DEEPSLATE_COAL_ORE,
	NETHER_WART_BLOCK,
	GRASS,
	BACKROOM_YELLOW,
	BACKROOM_FLOOR,
	BUG,
	CHISELED_NETHER_BRICKS,
	CRACKED_NETHER_BRICKS,
	DRAGON_EGG,
	GRAY_GLAZED_TERRACOTTA,
	REDSTONE_BLOCK,
	RED_MUSHROOM_BLOCK,
	RED_GLAZED_TERRACOTTA,
	CRIMSON_NYLIUM,
	CRIMSON_NYLIUM_SIDE,
	FLOWER,
	BLOCK_END_PORTAL,
	BLOCK_END_STONE,
	BLOCK_END_STONE_BRICKS,
	BLOCK_CHORUS_PLANT,
	BLOCK_CHORUS_FLOWER_DEAD,
	BLOCK_CHORUS_FLOWER,
	BLOCK_NUMBER,
}	Block;

static const char		*g_block_name[] = {
	"netherportal",
	"netherrack",
	"obsidian",
	"crying_obsidian",
	"cracked_deepslate_tiles",
	"deepslate_coal_ore",
	"nether_wart_block",
	"grass",
	"backroom_yellow",
	"backroom_floor",
	"bug",
	"chiseled_nether_bricks",
	"cracked_nether_bricks",
	"dragon_egg",
	"gray_glazed_terracotta",
	"redstone_block",
	"red_mushroom_block",
	"red_glazed_terracotta",
	"crimson_nylium",
	"crimson_nylium_side",
	"flower",
	"block_end_portal",
	"end_stone_bricks",
	"end_stone",
	"chorus_plant",
	"chorus_flower_dead",
	"chorus_flower",
};

typedef struct s_block
{
	Block			name;
	char			block_char;
	t_item			*item;
	int				strength;
	t_animation		animation;
	mlx_image_t		*image;
	bool			is_rigid;
}	t_block;

//loader
void			block_loader(mlx_t *mlx);

//accessor
t_block			*get_block(Block block);
t_block			*get_block_from_char(char block_char);
mlx_image_t		*get_block_image(Block block);
Block			get_block_name_from_char(char block_char);
void			set_block(t_block *block);

//utils
bool			is_rigid_block(Block block);
bool			is_char_block(char c);

#endif
