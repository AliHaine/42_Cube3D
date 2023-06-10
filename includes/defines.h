/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:03:42 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 17:03:46 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define PI 3.141592653589793
# define SCREEN_HEIGHT 720
# define SCREEN_WIDTH 1280
# define MINIMAP_SIZE 8
# define WALK_SPEED 10
# define RAY_NUMBER 1280
# define MINIMAP_PLAYER_SIZE (MINIMAP_SIZE/3)
# define FOV 60
# define SENSIBILITY 2
# define FOG_DISTANCE 1000
# define TEXTURE_SIZE 64
# define RESIZE (64 / (64 / MINIMAP_SIZE))
# define DEFAULT_WALL "assets/default_wall.png"
# define LOAD 0

#endif
