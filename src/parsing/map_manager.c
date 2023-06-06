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
			ti->b = size - 1;
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
		close(fd);
		msg_write(2, 1, ERROR_MAP_CHAR);
		return (-1);
	}
	close(fd);
	fd = open(map, O_RDONLY);
	consts->map = malloc(sizeof(char *) * (ti->c + 2));
	consts->map[ti->c + 1] = 0;
	return (fd);
}

void	map_manager(char *map_name, t_core *core)
{
	int		fd;
	t_t_i	ti;
	int		m_start_line;

	if (!is_cub(map_name))
		msg_write(2, 1, ERROR_MAP_NAME);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		msg_write(2, 1, ERROR_MAP_EXIST);
	init_tti_struct(&ti, 0, 0, 0);
	m_start_line = texture_main(fd, core);
	fd = map_value_init(&ti, fd, map_name, &core->consts);
	while (m_start_line-- > 0)
		get_next_line(fd);
	parse_main(ti, fd, core);
	core->consts.map_width = ti.b;
	core->consts.map_height = ti.c;
}
