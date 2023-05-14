#ifndef UTILS_H
#define UTILS_H

#include "includes.h"
#include "../src/utils/get_next_line/get_next_line.h"

bool	is_cub(const char *str);

void	msg_write(int fd, int exitVal, MsgType msg);

//map_utils//

bool	is_player_char(char c);
bool	is_allowed_char(char c);
char	*convert_to_path(char *name);

//std_func_utils//

void	ft_strcpy(char *s1, const char *s2);
void	ft_strcat(char *s1, const char *s2);
int		ft_strlen(const char *s);

//struct//

void	init_tti_struct(t_t_i *ti, int a, int b, int c);


#endif
