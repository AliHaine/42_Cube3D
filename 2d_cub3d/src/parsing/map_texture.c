#include "../../includes/includes.h"

static bool	is_direction_code(char *s)
{
	if (ft_strlen(s) < 1)
		return (false);
	if (s[0] == 'N' && s[1] == 'O')
		return (true);
	if (s[0] == 'S' && s[1] == 'O')
		return (true);
	if (s[0] == 'W' && s[1] == 'E')
		return (true);
	if (s[0] == 'E' && s[1] == 'A')
		return (true);
	return (false);

}

static void get_texture_from_map(int fd_map)
{
	char	*line;

	line = get_next_line(fd_map);
	while (line)
	{
		if (!is_direction_code(line))
			break ;
		//get la texture
		line = get_next_line(fd_map);
	}
	while (line)
	{
		if (line[0] && line[0] != 'F' && line[0] != 'C')
			break;
		//get la texture
		line = get_next_line(fd_map);
	}
}

void texture_main(int fd_map, t_core *core)
{
	(void) core;

	get_texture_from_map(fd_map);
}
