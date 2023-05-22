#include "../../includes/includes.h"

static bool	set_map_size_value(t_t_i *ti, int fd_map)
{
	char	*line;
	int		size;

	line = get_next_line(fd_map);
	while (line)
	{
		line = get_next_line(fd_map);
		size = ft_strlen(line);
		if (size > ti->b)
			ti->b = size;
		ti->c++;
	}
	if (ti->b <= 0 || ti->c <= 0)
		return (false);
	return (true);
}

/*static bool	check_map_validity(char **map)
{


	return (true);
}*/

void	map_manager(char *str, t_core *core)
{
	int		fd;
	char	*map;
	t_t_i	ti;

	if (!is_cub(str))
		msg_write(2, 1, ERROR_MAP_NAME);
	map = convert_to_path(str);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		msg_write(2, 1, ERROR_MAP_EXIST);
	//texture_main(fd, core);

	init_tti_struct(&ti, 0, 0, 0);
	if (!set_map_size_value(&ti, fd))
	{
		free(map);
		close(fd);
		msg_write(2, 1, ERROR_MAP_CHAR);
	}
	fd = open(map, O_RDONLY);
	free(map);
	core->consts.map = malloc(sizeof(char *) * (ti.c + 1));
	core->consts.map[ti.c] = 0;
	parse_main(ti, fd, core);

}
