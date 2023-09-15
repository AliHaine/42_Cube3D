/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:42:53 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/31 11:42:54 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "includes.h"

typedef struct s_world	t_world;

typedef struct s_sprite
{
	bool	is_seen;
	float	dist;
	int		c_xy[2];
	float	sp_xy[2];
	int		x;
	int		y;
	int		size[2];
	float	t_pos[2];
	float	offset[2];
	float	s_pos[3];
	float	tmp[2];
}			t_sprite;

typedef struct s_dda
{
	int			ray;
	float		r_xy[2];
	float		v_xy[2];
	float		o_xy[2];
	float		cos;
	float		sin;
	float		dist_hv[2];
	float		current_angle;
	float		current_angle_fix;
	int			hit_hv;
	int			hit_direction[2];
	int			chunk_hv[2];
	t_sprite	**sprites;
}	t_dda;

typedef struct s_col_drawing
{
	int			iterator;
	uint32_t	color;
	int			ceil_floor_line_h;
	int			wall_line_h;
	float		step;
	float		current_step;
	float		fog_strength;
	char		hit_block;
	float		floor_d;
}	t_col_drawing;

//dda//
void		raycasting(t_player *player, t_sprite **sprites, t_imgs *imgs, t_options *options);

//drawing.c
void		columns_drawing(t_imgs *imgs, t_dda *dda, t_player *player, t_options *options);
void		draw_energy_bar(mlx_image_t *img, int energy);
void		minimap_drawing(t_imgs *imgs, const float playerpos[2], t_world *map);

//raycastin and drawing

void		fisheyes_fixor(t_dda *dda, float player_angle);
void		get_color_wall_texture(mlx_texture_t *wall_texture, int r, t_col_drawing *tcd);
void		get_color_block_texture(t_dda *dda, t_col_drawing *tcd);
uint32_t	apply_fog(uint32_t color, float fog_strength);

// sprites.c
void		draw_sprites(t_player *player, t_sprite **sprites, t_imgs *imgs);

#endif
