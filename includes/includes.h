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
# include <stdarg.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include "structs.h"
# include "utils.h"
# include "defines.h"
# include <sys/time.h>
# include "enum.h"

# include "sound.h"

# include "concepts/world.h"
# include "concepts/block.h"
# include "concepts/item.h"
# include "raycast.h"


void		display(void *params);

void	sprites_drawing(t_imgs *imgs, t_sprite *sprites, t_player *player);

//loader//

//void	sound_loader(t_sounds *sounds, t_options *options);
void	texture_loader(t_core *core);
void	mlx_hook_loader(t_core *core);

//??

void	inputs(void *params);
void	inputs_hook(struct mlx_key_data key, void *params);
void	move_left(t_player *player);
void	move_right(t_player *player);
void	move_backward(t_player *player);
void	move_forward(t_player *player);
void	move_rotate(t_player *player, int direction, float speed);
void	mouse_cursor(mlx_t *mlx, t_player *player, const int screen_size[2]);
void	mouse(enum mouse_key, enum action, enum modifier_key, void *param);
void	resize_hook(int height, int width, void *params);
void	scroll_hook(double x, double y, void *param);

//parsing//

void	map_manager(char *argv, t_imgs *imgs, t_player *player);
void	texture_main(t_file *file, t_imgs *imgs, uint32_t bt_color[2]);
bool	parse_main(t_file *file, t_player *player, t_world *map);
void	initialize_options(t_core *core);

//animations//
void    animation_listener();

	//player interaction//
void	player_listener(void *params);
void	inventory(t_core *core);
void	inventory_hook(void *params);
void	display_item(t_core *core, t_slot *slot);
void	crafting_engine(t_core *core);
void	craft(t_core *core);
void	teleport_player(t_player *player);
void	player_build(t_player *player, t_options options);

void	set_char_at_forward(char c, t_player *player);

//heal//
bool	is_player_death(int player_health);
bool    hit_player(t_player *player, t_imgs *imgs);
void	heal_player(t_player *player, t_imgs *imgs);

//energy
bool	take_energy(t_player *player, int value);
bool	add_energy(t_player *player, int value);
bool	player_have_energy(int value);
bool	player_have_enough_energy(t_player *player, int value);

void	setup_slot_struct(mlx_t *mlx, t_player *player);
t_slot	*get_first_slot(t_slot *slot);

void setup_col_struct(t_col_drawing *tcd, t_dda *dda, t_world *world);


//portal
void	portal_listener(t_player *player, t_world *world);
void	portal_open(t_player *player);

#endif
