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

typedef struct s_const
{
	mlx_image_t		*img_map;
	mlx_image_t		*img_dot;
	mlx_texture_t	*texture_dot;
	uint32_t		wall_color;
	uint32_t		ray_color;
	float			dist_between_ray;
	char			**map;
	float			fov;
}	t_const;

typedef struct s_player
{
	float			playerpos[2];
	float			playerangle;
	int				health;
}	t_player;

typedef struct s_core
{
	mlx_t			*mlx;
	t_const			consts;
	t_player		player;
}	t_core;

typedef struct s_three_i
{
	int	a;
	int	b;
	int	c;
}	t_t_i;

typedef enum {
	ERROR_MAP_CHAR,
	ERROR_MAP_NAME,
	ERROR_MAP_IMG,
	ERROR_MAP_EXIST,
	ERROR_ARGS,
} MsgType;


static const char *Messages[] = {
		"Error \nThere is an unknow char in the map",
		"Error \nThe name of the map is not compliant",
		"Error \nCan't load the img",
		"Error \nCan't open the map file",
		"Error \nArgs",
};

#endif
