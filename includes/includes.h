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
# include "../libft/libft.h"

void	display(void *params);
void	draw_map(t_core *core);
void	raycast(t_core *core);

void	inputs(void *params);
void	move_right_left(t_core *core, int direction);
void	move_forward_backward(t_core *core, int direction);
void	move_rotate(t_core *core, int direction);

//parsing//

void	parse_main(char *str);

//---utils---//

bool	is_cub(const char *str);

void	msg_write(int fd, int exitVal, MsgType msg);

//map_utils//

char	*convert_to_path(char *name);

//std_func_utils//

void	ft_strcpy(char *s1, const char *s2);
void	ft_strcat(char *s1, const char *s2);
int		ft_strlen(const char *s);

#endif
