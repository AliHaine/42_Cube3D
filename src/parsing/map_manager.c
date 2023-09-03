/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:57:43 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 18:57:44 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	set_map_size_value(t_file *file, int map_hw[2])
{
	int		current_line_size;

	map_hw[1] = 0;
	map_hw[0] = 0;
	while (file->line && !is_str_blank(file->line))
	{
		current_line_size = ft_strlen(file->line);
		if (current_line_size > map_hw[1])
			map_hw[1] = current_line_size - 1;
		get_next_line(file);
		map_hw[0]++;
	}
	if (map_hw[1] <= 2 || map_hw[0] <= 1 || map_hw[1] > 60 || map_hw[0] > 30)
		return (false);
	return (true);
}

static bool	map_value_init(int map_hw[2], t_file *file, int start)
{
	if (!set_map_size_value(file, map_hw))
	{
		close_file(file);
		msg_write(2, 1, ERROR_MAP_SIZE);
		return (0);
	}
	reopen_file(file, start, O_RDONLY);
	return (1);
}

void	map_manager(char *map_name, t_imgs *imgs, t_player *player)
{
	t_file			file;
	int				save;
	uint32_t		bt_color[2];
	int				map_hw[2];

	msg_write(2, -1, CHECK_MAP);
	usleep(500000 * LOAD);
	basical_map_check(&map_name);
	open_file(&file, map_name, O_RDONLY);
	msg_write(1, -1, NO_ERROR);
	texture_main(&file, imgs, bt_color);
	save = file.line_num;
	map_value_init(map_hw, &file, save);
	world_creator(WORLD_DEFAULT, 0, get_sound(NORMAL_AMBIANT_SOUND), map_hw[0], map_hw[1], bt_color, imgs->skybox, imgs->floor_texture, EASY, true, true);
	play_sound(get_world_active()->ambiant_sound);
	parse_main(&file, player, get_world(WORLD_DEFAULT));
}
