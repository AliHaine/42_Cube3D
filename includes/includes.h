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
# include <sys/time.h>

//raycast2//
void	raycasting(t_core *core);

//display.c
void		display(void *params);
void		draw_map(t_core *core);

//raycast.c
void		raycast(t_core *core);
void		draw_obstacles(t_core *core, t_ray ray, int r);

//draw.c
void	columns_drawing(t_core *core, t_dda *dda);
void	draw_columns(t_core *core, t_ray ray, int r);


//wall_direction.c
int			wall_direction(t_core *core, t_ray ray);
int			get_offset(int direction, t_ray ray);

//obstacle_direction.c
int			obstacle_direction(t_core *core, t_checkpoint check, t_ray ray);
int			get_obstacle_offset(int direction, t_checkpoint check);

//textures.c
uint32_t	get_color(mlx_texture_t *wall_texture, float fog_strength, int texture_xy[2]);
void		draw_energy_bar(mlx_image_t *img, short energy);

//loader//

void	sound_loader(t_sounds *sounds);
void	texture_loader(t_core *core);
void	mlx_hook_loader(t_core *core);
void	item_loader(t_core *core);

//raycast_utils.c
float		calc_ray_dist(t_core *core, float ray_x, float ray_y, float ray_angle);
int	        is_obstacle(t_core *core, t_ray *ray);

void	inputs(void *params);
void	inputs_hook(struct mlx_key_data key, void *params);
void	move_right_left(t_player *player, char **map, int direction);
void	move_forward_backward(t_player *player, char **map, int direction);
void	move_rotate(t_player *player, int direction, float speed);
void	mouse_cursor(mlx_t *mlx, t_player *player, const int screen_size[2]);
void	mouse(enum mouse_key, enum action, enum modifier_key, void *param);
void	resize_hook(int height, int width, void *params);
void	scroll_hook(double x, double y, void *param);

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

//animations//
void	attack_animation(t_core *core);
void    animation_listener(t_core *core);

	//player interaction//
void	player_listener(void *params);
void	inventory(t_core *core);
void	inventory_hook(void *params);
void	display_item(t_core *core, t_slot *slot);

void	set_char_at_forward(char c, t_player *player, char **map);

//item//
void    give_item(t_core *core, t_item *item, int slot_id, int number);

//heal//
bool	is_player_death(int player_health);
bool    hit_player(t_player *player, t_imgs *imgs);
void	heal_player(t_player *player, t_imgs *imgs);

//energy
void	take_energy(t_player *player, short value);
void	add_energy(t_player *player, short value);
bool	player_have_energy(short value);
bool	player_have_enough_energy(t_player *player, short value);

	//struct
void	struct_setup(t_core *core);

void	setup_slot_struct(t_core *core, t_player *player, t_item *item);
t_slot	*get_first_slot(t_slot *slot);

#endif
