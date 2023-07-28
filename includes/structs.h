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

# include "../includes/enum.h"

typedef struct	s_sounds
{
	uint32_t	ambiant;
	uint32_t	player_hurt;
	uint32_t	player_walk;
}				t_sounds;

typedef struct s_imgs
{
	mlx_image_t		*img_3d;
	mlx_image_t		*img_map;
	mlx_image_t		*img_player;
	mlx_image_t 	*crosshair;
	mlx_image_t 	*invbar;
	mlx_image_t 	*invbar_selector;
	mlx_image_t 	*engbar;
    mlx_image_t 	*hearth[2];
	mlx_image_t 	*sword_nether[5];
	mlx_image_t 	*hand[9];
	mlx_image_t		*map_background;
	mlx_image_t		*icon_sword_nether;
	mlx_image_t		*inventory_gui;
	mlx_texture_t	*map_texture;
    mlx_texture_t	*enemy;
	mlx_texture_t	*trans;
	mlx_texture_t	*wall_texture[4];
    mlx_texture_t   *floor_texture;
	mlx_texture_t	*door_texture;
	mlx_texture_t	*grass_texture;
	mlx_texture_t	*inventory_gui_texture;
	mlx_texture_t	*cursor;
	mlx_texture_t	*img_player_texture;
}	t_imgs;

typedef struct s_dda
{
	int	ray;
    float r_xy[2];
	float v_xy[2];
	float cos;
	float sin;
    float dist_hv[2];
	float current_angle; // current angle
    float current_angle_fix; //fish eye fix
	int hit_hv;
	int hit_direction[2];
	float wall_height;

}	t_dda;

typedef struct s_col_drawing
{
    int iterator;
	uint32_t color;
    int sky_lineH;
	int wall_lineH;
	float step;
	float current_step;
}	t_col_drawing;

typedef struct s_file
{
	int		fd;
	int		file_size;
	int		line_num;
	char	*line;
	char	*file_path;
}	t_file;

typedef struct s_map
{
	char **map;
	int height;
	int width;
	uint32_t	bt_color[2];
	Difficulty difficulty;
}	t_map;

typedef struct s_animation
{
	mlx_image_t		**image;
	bool			is_playing;
}	t_animation;

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
	float			playerpos[2];
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

typedef struct s_core
{
	mlx_t			*mlx;
	t_player		player;
	t_imgs			imgs;
	t_sounds		sounds;
	t_item			items[7];
	t_animation 	animations[7];
	t_map 			*maps;
    int             screen_size[2];
}	t_core;

#endif
