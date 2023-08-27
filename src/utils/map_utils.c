/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:51:57 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/27 14:51:58 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_allowed_char(char c)
{
	if (c == '0' || c == '1' || is_player_char(c)
		|| is_char_block(c) || c == ' ')
		return (true);
	return (false);
}

static bool	is_cub(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i < 2)
		return (false);
	i--;
	if (str[i] != 'b' && str[i - 1] != 'u' && str[i - 2] != 'c'
		&& str[i - 3] != '.')
		return (false);
	return (true);
}

void	basical_map_check(char **map_name)
{
	int		fd;

	if (!*map_name)
	{
		msg_write(2, -1, ERROR_ARGS);
		msg_write(1, -1, SET_DEFAULT_MAP);
		*map_name = ".d/default.cub";
	}
	if (!is_cub(*map_name))
	{
		msg_write(2, -1, ERROR_MAP_NAME);
		msg_write(1, -1, SET_DEFAULT_MAP);
		*map_name = ".d/default.cub";
	}
	fd = open(*map_name, O_RDONLY);
	if (fd == -1)
	{
		msg_write(2, -1, ERROR_MAP_EXIST);
		msg_write(1, -1, SET_DEFAULT_MAP);
		*map_name = ".d/default.cub";
		fd = open(*map_name, O_RDONLY);
		if (fd == -1)
			msg_write(2, 2, ERROR_FATAL);
	}
	close(fd);
}

short	get_direction_code(char *s)
{
	if (ft_strlen(s) < 1)
		return (4);
	if (s[0] == 'N' && s[1] == 'O')
		return (0);
	if (s[0] == 'S' && s[1] == 'O')
		return (2);
	if (s[0] == 'W' && s[1] == 'E')
		return (3);
	if (s[0] == 'E' && s[1] == 'A')
		return (1);
	return (4);
}

bool	set_default_wall_texture(t_imgs *imgs)
{
	int				max;
	mlx_texture_t	*default_wall;

	max = 0;
	msg_write(1, -1, EMPTY_WALL);
	msg_write_multiple(1, Messages[TRY_LOAD_TEXTURE], DEFAULT_WALL);
	default_wall = mlx_load_png(DEFAULT_WALL);
	if (!default_wall)
		msg_write(2, 1, ERROR_FATAL);
	while (max < 4)
	{
		if (imgs->wall_texture[max] == 0)
			imgs->wall_texture[max] = default_wall;
		max++;
	}
	msg_write(1, -1, SUCCESS);
	return (true);
}

bool	is_wall_empty(const t_imgs *imgs)
{
	int	i ;

	i = 0;
	while (i < 4)
	{
		if (!imgs->wall_texture[i])
			return (true);
		i++;
	}
	return (false);
}

bool	is_color_char(char c)
{
	if (c == 'F' || c == 'C')
		return (true);
	return (false);
}
