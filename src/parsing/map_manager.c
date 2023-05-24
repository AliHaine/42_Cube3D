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

static int	map_value_init(t_t_i *ti, int fd, char *map, t_const *consts)
{
	if (!set_map_size_value(ti, fd))
	{
		free(map);
		close(fd);
		msg_write(2, 1, ERROR_MAP_CHAR);
		return (-1);
	}
	close(fd);
	fd = open(map, O_RDONLY);
	free(map);
	printf("%d\n", ti->c);
	consts->map = malloc(sizeof(char *) * (ti->c + 2));
	consts->map[ti->c + 1] = 0;
	return (fd);
}

static void	map_go_to_line(int line, int fd)
{
	while (line-- > 0)
		get_next_line(fd);
}

void	map_manager(char *str, t_core *core)
{
	int		fd;
	char	*map;
	t_t_i	ti;
	int		m_start_line;

	if (!is_cub(str))
		msg_write(2, 1, ERROR_MAP_NAME);
	map = convert_to_path(str);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		msg_write(2, 1, ERROR_MAP_EXIST);
	init_tti_struct(&ti, 0, 0, 0);
	m_start_line = texture_main(fd, core);
	fd = map_value_init(&ti, fd, map, &core->consts);
	map_go_to_line(m_start_line, fd);
	parse_main(ti, fd, core);
}
