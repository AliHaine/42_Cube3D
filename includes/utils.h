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

//std_func_utils//

int		ft_strlen(const char *s);
int		ft_atoi_for_texture(const char *s);
char	*ft_itoa(int n);

//struct//

void	init_tti_struct(t_t_i *ti, int a, int b, int c);
t_slot	*get_slot(t_core *core, int s);

//file//

void	go_to_line(t_file *file, int line);
void	reopen_file(t_file *file, int line, int flags);
bool	open_file(t_file *file, char *file_path, int flags);

//mlx image utiles//

bool	set_texture_from_path(char *line, mlx_texture_t **texture);
bool	set_image_from_path(mlx_t *mlx, char *path, mlx_image_t **image);
void		delete_image_from_struct(mlx_t *mlx, t_imgs *imgs);
uint32_t	get_rgb_color(unsigned short r, unsigned short g, unsigned short b, unsigned short a);
void	draw_pixel_to_img(mlx_image_t *img, t_t_i ti, uint32_t color);
uint32_t	get_pixel(mlx_texture_t *texture, int x, int y);
mlx_image_t *rotate_image(mlx_t *mlx, mlx_image_t *image, int img_width, int img_height, int angle);

//move_utils//
char	get_backward_char(t_player *player, char **map);
char	get_forward_char(t_player *player, char **map);
char	get_right_char(t_player *player, char **map);
char	get_left_char(t_player *player, char **map);
bool	is_player_running(t_player *player);

//raycastin and drawing

void	fisheyes_fixor(t_dda *dda, float player_angle);
void	get_color_from_wall_texture(mlx_texture_t *wall_texture, int r, t_wall_drawing *twd);

#endif
