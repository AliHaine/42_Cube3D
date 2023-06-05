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
uint32_t	wall_texture(t_core *core, int x, int y);
char		wall_direction(t_core *core, t_ray ray);

void	inputs(void *params);
void	move_right_left(t_player *player, char **map, int direction);
void	move_forward_backward(t_player *player, char **map, int direction);
void	move_rotate(t_player *player, int direction);

//parsing//

void	map_manager(char *str, t_core *core);
int		texture_main(int fd_map, t_core *core);
void	parse_main(t_t_i ti, int fd_map, t_core *core);



#endif
