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

void		display(void *params);
void		draw_map(t_core *core);
void		raycast(t_core *core);
uint32_t	get_color_from_wall_texture(mlx_texture_t *wall_texture, const int texture_xy[2]);
short		wall_direction(t_core *core, t_ray ray);
int			wall_calc(t_const *consts, float angle);

void	inputs(void *params);
void	inputs_hook(struct mlx_key_data key, void *params);
void	move_right_left(t_player *player, char **map, int direction);
void	move_forward_backward(t_player *player, char **map, int direction);
void	move_rotate(t_player *player, int direction, float speed);
void	mouse(mlx_t *mlx, t_player *player, const int screen_size[2]);
void    resize_hook(int height, int width, void *params);

//parsing//

void	map_manager(char *str, t_core *core);
void	texture_main(t_file *file, t_core *core);
bool	parse_main(t_t_i ti, t_file *file, t_core *core);



#endif
