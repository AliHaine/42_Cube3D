#include "../../includes/includes.h"

static bool	init_map(int fd_map)
{
	(void) fd_map;



	return (true);
}

void	parse_main(char *str)
{
	int		fd;
	char	*map;

	if (!is_cub(str))
		msg_write(2, 1, ERROR_MAP_NAME);
	map = convert_to_path(str);
	fd = open(map, O_RDONLY);
	free(map);
	if (fd == -1)
		msg_write(2, 1, ERROR_MAP_EXIST);
	init_map(fd);
}