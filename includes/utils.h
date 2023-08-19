#ifndef UTILS_H
#define UTILS_H

#include "includes.h"
#include "../src/utils/get_next_line/get_next_line.h"

void	basical_map_check(char **map_name);

void	msg_write_multiple(int fd, const char *str1, const char *str2);
void	msg_write(int fd, int exitVal, MsgType msg);

//map_utils//

bool	is_player_char(char c);
bool	is_allowed_char(char c);
short	get_direction_code(char *s);
bool	set_default_wall_texture(t_imgs *imgs);
bool	is_wall_empty(const t_imgs *imgs);
bool    is_color_char(char c);

//std_func_utils//

int     get_rand_num(int max_val);
void	put_two_string(char *dst, const char *s1, const char *s2, char *num);
int		ft_strlen(const char *s);
int		ft_atoi_for_texture(const char *s);
char	*ft_itoa(int n);
bool	is_str_blank(const char *s);
void	free_tab(char **tab, int size);
void	copy_tab(char **tab_src, char **tab_dst, int height, int width);
bool	is_value_beetween(int value, int beet, int target);

//struct//

//file//

void	go_to_line(t_file *file, int line);
void	reopen_file(t_file *file, int line, int flags);
bool	open_file(t_file *file, char *file_path, int flags);
void	close_file(t_file *file);

//mlx image utiles//

bool	set_texture_from_path(char *line, mlx_texture_t **texture);
bool	set_image_from_path(mlx_t *mlx, char *path, mlx_image_t **image);
void		delete_image_from_struct(mlx_t *mlx, t_imgs *imgs);
uint32_t	get_rgb_color(unsigned short r, unsigned short g, unsigned short b, unsigned short a);
uint32_t	get_pixel(mlx_texture_t *texture, int x, int y);
mlx_image_t *rotate_image(mlx_t *mlx, mlx_texture_t *image, float angle);

//move_utils//
char	get_backward_char(t_player *player, t_map *map);
char	get_forward_char(t_player *player, t_map *map);
char	get_right_char(t_player *player, t_map *map);
char	get_left_char(t_player *player, t_map *map);
bool	is_player_running(t_player *player);

//raycastin and drawing

void	fisheyes_fixor(t_dda *dda, float player_angle);
void	get_color_wall_texture(mlx_texture_t *wall_texture, int r, t_col_drawing *tcd);
void	get_color_block_texture(mlx_image_t *block_texture, t_dda *dda, t_col_drawing *tcd);
uint32_t	apply_fog(uint32_t color, float fog_strength);

// inventory / s_slot
t_slot	*get_slot(t_core *core, int s);
int		detect_pointed_slot(t_core *core, int x, int y);
void	set_pos_by_id(t_slot *slot, int id);
void	reset_slot(t_core *core, t_slot *slot);
void	change_item_number(t_core *core, t_slot *src, short n);

//block_utils

t_block *get_block_from_char(t_block **block, char block_char);

//world_utils
bool    is_player_chunk_change(t_player *player, t_map *map);
int	get_chunk_from_pos(int x, int y, int m_height, int m_width);
int	get_active_world(t_map maps[2]);
bool    world_dynamic_generator(t_map *map, t_player *player);

//tester
void print_entire_world(t_map *map);


#endif
