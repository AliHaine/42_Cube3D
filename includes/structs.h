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
	int				map[12][20];
	float			fov;
}	t_const;

typedef struct s_core
{
	mlx_t			*mlx;
	float			playerpos[2];
	float			playerangle;
	t_const			*consts;
}	t_core;

#endif
