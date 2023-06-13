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

typedef struct s_point
{
	float x;
	float y;
}	t_point;

typedef struct s_imgs
{
	mlx_image_t		*img_3d;
	mlx_image_t		*img_map;
	mlx_image_t		*img_player;
}	t_imgs;

typedef struct s_ray
{
	float	start_angle;
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	ray_dist;
	bool	have_checkpoint;
	float	checkpoint_x;
	float	checkpoint_y;
	char	obstacle;
}	t_ray;

typedef struct s_three_i
{
	int	a;
	int	b;
	int	c;
}	t_t_i;

typedef struct s_file
{
	int		fd;
	int		file_size;
	int		line_num;
	char	*line;
	char	*file_path;
}	t_file;

typedef struct s_const
{
	mlx_texture_t	*wall_texture[4];
	mlx_texture_t	*door_texture;
	uint32_t		bot_color;
	uint32_t		top_color;
	uint32_t		minimap_wall_color;
	uint32_t		minimap_floor_color;
	uint32_t		ray_color;
	float			dist_between_ray;
	char			**map;
	float			fov;
	float			fog_distance;
	int				map_width;
	int				map_height;
	int				minimap_size;
	float			north_east;
	float			north_west;
	float			south_east;
	float			south_west;
}	t_const;

typedef struct s_player
{
	float			playerpos[2];
	float			playerangle;
	int				health;
	bool			have_player;
	int				move_speed;
}	t_player;

typedef struct s_core
{
	mlx_t			*mlx;
	t_const			consts;
	t_player		player;
	t_imgs			imgs;
    int             screen_size[2];
}	t_core;

typedef enum {
	ERROR_MAP_CHAR,
	ERROR_MAP_NAME,
	ERROR_MAP_IMG,
	ERROR_MAP_EXIST,
	ERROR_ARGS,
	ERROR_PLAYER,
	STARTING,
	SUCCESS,
	NO_ERROR,
	FAILURE,
	ERROR_FATAL,
	CORE_INIT,
	CHECK_MAP,
	GET_MAP_CONTENT,
	TRY_LOAD_TEXTURE,
	EMPTY_WALL,
	TRY_LOAD_COLOR,
	MINIMAP_INIT,
} MsgType;


static const char *Messages[] = {
		"\e[40;31mError \nThere is an unknow char in the map",
		"\e[40;31mError \nThe name of the map is not compliant",
		"\e[40;31mError \nCan't load the img",
		"\e[40;31mError \nCan't open the map file",
		"\e[40;31mError \nArgs",
		"\e[40;31mError \nNo player in the map",
		"\e[40;33mStarting..",
		"\e[40;32mSucces.",
		"\e[40;32mNo errors found.",
		"\e[40;31mFailure.",
		"\e[101;90mFATAL ERROR.",
		"\e[40;33mInitialization of Core values..",
		"\n\e[40;33mChecking the map contents..",
		"\n\e[40;33mStarting to get the map contents..",
		"\e[40;33mTrying to load texture: ",
		"\e[40;35mAll wall direction don't have texture, trying to set default.. ",
		"\e[40;33mTrying to load color: ",
		"\n\e[40;33mInitialization of Minimap.. ",
};

#endif
