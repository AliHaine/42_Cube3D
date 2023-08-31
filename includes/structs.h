/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:25 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:47:29 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "includes.h"
# include "../includes/enum.h"
typedef struct s_item t_item;

typedef struct	s_imgs
{
	mlx_image_t		*img_3d;
	mlx_image_t		*img_map;
	mlx_image_t		*img_player;
	mlx_image_t		*crosshair;
	mlx_image_t		*invbar;
	mlx_image_t		*invbar_selector;
	mlx_image_t 	*engbar;
    mlx_image_t 	*hearth[2];
	mlx_image_t		*map_background;
	mlx_image_t		*inventory_gui;
	mlx_image_t     *floor_texture;
	mlx_image_t		*skybox;
    mlx_image_t		*skybox_nether;
	mlx_image_t		*backrooms_ceil;
	mlx_texture_t	*map_texture;
	mlx_texture_t	*trans;
	mlx_texture_t	*wall_texture[4];
	mlx_texture_t	*inventory_gui_texture;
	mlx_texture_t	*cursor;
	mlx_texture_t	*img_player_texture;
}	t_imgs;

typedef struct s_file
{
	int		fd;
	int		line_num;
	char	*line;
	char	*file_path;
	char 	*storage;
}	t_file;

typedef struct s_animation
{
	mlx_image_t		**image;
	bool			is_playing;
	int				depth_xy[2];
}	t_animation;

typedef struct s_slot
{
	short			slot_id;
	t_item			*item;
    uint32_t		icon_instance;
    uint32_t		bar_icon_instance;
	short			items_number;
	mlx_image_t		*items_number_img;
	mlx_image_t		*items_number_img_bar;
	bool			bar_mutex;
	struct s_slot	*next;
	struct s_slot	*prev;
}	t_slot;

typedef struct s_player
{
	float			player_pos_xy[2];
	int				player_cell_xy[2];
	float			playerangle;
	int				health;
	bool			have_player;
	int				move_speed;
	int				energy;
	t_slot			*slot;
	bool			is_in_inventory;
	bool			*holding_item;
	bool			can_move;
	bool			is_moving;
	bool			is_running;
}	t_player;

typedef struct s_options
{
	bool	floor_texture;
	bool	skybox;
	bool	sound;
	bool	break_blocks;
}	t_options;

typedef struct s_core
{
	mlx_t			*mlx;
	t_options		options;
	t_player		player;
	t_imgs			imgs;
    int             screen_size[2];
}	t_core;

#endif
