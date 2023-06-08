#include "../../includes/includes.h"

static bool	set_color_value(const char *line, uint32_t *target_color)
{
	int		i;
	int		b;
	char	**value;

	i = 0;
	b = 0;
	value = malloc(sizeof(char *) * 3);
	value[0] = malloc(sizeof(char) * 4);
	value[1] = malloc(sizeof(char) * 4);
	value[2] = malloc(sizeof(char) * 4);
	while (*line)
	{
		if (*line == ',') {
			value[i][b] = '\0';
			i++;
			b = 0;
			line++;
		}
		if (b > 3 || i > 3)
			return (false);
		value[i][b++] = *line++;
	}
	value[i][b-1] = '\0';
	*target_color = (ft_atoi_for_texture(value[0]) << 24) + (ft_atoi_for_texture(value[1]) << 16) + (ft_atoi_for_texture(value[2]) << 8) + 255;
	free(value);
	return (true);
}

static bool	set_texture_from_path(char *line, mlx_texture_t **texture)
{
	while (*line && *line == ' ')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	*texture = mlx_load_png(line);
	if (!*texture)
		return (false);
	return (true);
}

static int	get_color_from_map(char *line, int fd_map, t_const *consts)
{
	int size;

	size = 0;
	while (line)
	{
		if (line[0] && line[0] != 'F' && line[0] != 'C')
			break;
		if (line[0] != 'F')
			set_color_value(line + 2, &consts->top_color);
		else
			set_color_value(line + 2, &consts->bot_color);
		line = get_next_line(fd_map);
		size++;
	}
	while (line && line[0] && line[0] == '\n') {
		size++;
		line = get_next_line(fd_map);
	}
	return (size);
}

static int	get_image_from_map(char **line, int fd_map, t_const *consts)
{
	int		size;
	short	direction;

	size = 0;
	consts->wall_texture[0] = 0;
	while (line)
	{
		direction = get_direction_code(*line);
		if (direction >= 4)
			break ;
		set_texture_from_path(*line + 2, &consts->wall_texture[direction]);
		*line = get_next_line(fd_map);
		size++;
	}
	while (line && *line[0] == '\n')
	{
		*line = get_next_line(fd_map);
		size++;
	}
	return (size);
}

int	texture_main(int fd_map, t_core *core)
{
	int		size;
	char	*line;

	line = get_next_line(fd_map);
	size = get_image_from_map(&line, fd_map, &core->consts);
	size += get_color_from_map(line, fd_map, &core->consts);
	free(line);
	return (size);
}
