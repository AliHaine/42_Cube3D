/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:16 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:47:19 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include "structs.h"
# include "utils.h"
# include "defines.h"

//display.c
void		display(void *params);
void		draw_map(t_core *core);

//raycast.c
void		raycast(t_core *core);

//wall_direction.c
int			wall_direction(t_core *core, t_ray ray);
int			get_offset(int direction, t_ray ray);

//obstacle_direction.c
int			obstacle_direction(t_core *core, t_ray ray);
int			get_obstacle_offset(int direction, t_ray ray);

//textures.c
uint32_t	get_color(mlx_texture_t *wall_texture, float fog_strength, int texture_xy[2]);

//raycast_utils.c
float		calc_ray_dist(t_core *core, float ray_x, float ray_y, float ray_angle);

void	inputs(void *params);
void	inputs_hook(struct mlx_key_data key, void *params);
void	move_right_left(t_player *player, char **map, int direction);
void	move_forward_backward(t_player *player, char **map, int direction);
void	move_rotate(t_player *player, int direction, float speed);
void	mouse_cursor(mlx_t *mlx, t_player *player, const int screen_size[2]);
void	mouse(enum mouse_key, enum action, enum modifier_key, void *param);
void	resize_hook(int height, int width, void *params);

//parsing//

void	map_manager(char *argv[], t_core *core);
void	texture_main(t_file *file, t_core *core);
bool	parse_main(t_t_i ti, t_file *file, t_core *core);

//sound//
void	init_sound_empty(t_sounds *sounds);
void	clear_sounds(t_sounds *sounds);
bool	load_sound(uint32_t *s, char *path);
void	play_sound_alt(uint32_t s, bool play, bool loop);
void	play_sound(uint32_t s);

#endif
