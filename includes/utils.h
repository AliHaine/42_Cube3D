#ifndef UTILS_H
# define UTILS_H

# include "includes.h"
# include "../src/utils/get_next_line/get_next_line.h"

void		basical_map_check(char **map_name);

void		msg_write_multiple(int fd, const char *str1, const char *str2);
void		msg_write(int fd, int exitVal, MsgType msg);

char		**ft_split(char const *s, char c);

//map_utils//

bool		is_player_char(char c);
bool		is_allowed_char(char c);
short		get_direction_code(char *s);
bool		set_default_wall_texture(t_imgs *imgs);
bool		is_wall_empty(const t_imgs *imgs);

//std_func_utils//

int			get_rand_num(int max_val, int sleeper);
void		put_two_string(char *dst, const char *s1, const char *s2, char *num);
int			ft_strlen(const char *s);
int			ft_atoi_for_texture(const char *s);
char		*ft_itoa(int n);
bool		is_str_blank(const char *s);
void		free_tab_three(char ***tab);
void		copy_tab(char **tab_src, char **tab_dst, int height, int width);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);

//file//

void		go_to_line(t_file *file, int line);
void		reopen_file(t_file *file, int line, int flags);
bool		open_file(t_file *file, char *file_path, int flags);
void		close_file(t_file *file);

//mlx image utiles//

bool		set_texture_from_path(char *line, mlx_texture_t **texture);
bool		set_image_from_path(mlx_t *mlx, char *path, mlx_image_t **image);
void		delete_image_from_struct(mlx_t *mlx, t_imgs *imgs);
uint32_t	get_rgb_color(int r, int g, int b, int a);
uint32_t	get_pixel(mlx_texture_t *texture, int x, int y);
mlx_image_t	*rotate_image(mlx_t *mlx, mlx_texture_t *image, float angle);

//move_utils//
char		get_hit_char(t_player *player);
bool		is_move_key_down(mlx_t *mlx);
bool		is_player_running(t_player *player);
float		check_overflow(float val);
bool		is_block(float x, float y);

// inventory / s_slot
t_slot		*get_slot(t_core *core, int s);
int			detect_pointed_slot(t_core *core, int x, int y);
void		set_pos_by_id(t_slot *slot, int id);
void		reset_slot(t_core *core, t_slot *slot);
void		change_item_number(t_core *core, t_slot *src, short n);

//player_utils
void		set_player(int x, int y, t_player *player, float angle);

#endif
