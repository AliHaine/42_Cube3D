#include "../../includes/includes.h"
#include "../../includes/defines.h"

static bool	set_map_size_value(t_file *file, t_map *map)
{
	int		current_line_size;

	while (file->line && !is_str_blank(file->line))
	{
		current_line_size = ft_strlen(file->line);
		if (current_line_size > map->width)
			map->width = current_line_size - 1;
		get_next_line(file);
		map->height++;
	}
	if (map->width <= 2 || map->height <= 1 || map->width > 84 || map->height > 30)
		return (false);
	return (true);
}

static bool	map_value_init(t_map *map, t_file *file, int start)
{
	if (!set_map_size_value(file, map))
	{
		close_file(file);
		msg_write(2, 1, ERROR_MAP_SIZE);
		return (0);
	}
	reopen_file(file, start, O_RDONLY);
	return (1);
}

void	map_manager(char *map_name, t_map *map, t_imgs *imgs, t_player *player)
{
	t_file	file;
	int		save;

	msg_write(2, -1, CHECK_MAP);
	usleep(500000 * LOAD);
	basical_map_check(&map_name);
	map_struct_init(map);
	open_file(&file, map_name, O_RDONLY);
	msg_write(1, -1, NO_ERROR);
	texture_main(&file, imgs, map);
	save = file.line_num;
	map_value_init(map, &file, save);
    world_creator(map, 0, map->height, map->width, EASY, 0, true);
	parse_main(&file, player, map);
}
