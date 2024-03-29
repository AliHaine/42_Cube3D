/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biome.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:21:53 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/22 22:21:54 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIOME_H
# define BIOME_H

# include "block.h"

typedef struct s_block	t_block;

typedef enum {
	BIOME_NATURE,
	BIOME_DARK,
	BIOME_BACKROOM,
	BIOME_DRAGON,
	BIOME_RED,
	BIOME_END,
	BIOME_CHORUS,
	BIOME_NUMBER,
}	Biome;

typedef struct s_biome
{
	Biome	name;
	t_block	*block;
	int		block_number;
}	t_biome;

//accessor
t_biome		*get_biome(Biome biome);
void		set_biome(t_biome biome, int num);
void		set_biome_sprites(t_sprite **sprites, Biome biome);
void		free_biome(void);

//biome_utils
t_biome		*get_random_biome(t_biome **biome);
int			get_biomes_size(t_biome **biome);
t_block		get_random_block_from_biome(t_biome *biome);

#endif
