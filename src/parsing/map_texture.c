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

static bool	set_color_value(const char *line, t_t_i *ti)
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
	ti->a = ft_atoi_for_texture(value[0]);
	ti->b = ft_atoi_for_texture(value[1]);
	ti->c = ft_atoi_for_texture(value[2]);
	return (true);
}

static void get_texture_from_map(int fd_map, t_const *consts)
{
	char	*line;

	line = get_next_line(fd_map);
	while (line)
	{
		if (!is_direction_code(line))
			break ;
		line = get_next_line(fd_map);
	}
	while (line)
	{
		if (line[0] && line[0] != 'F' && line[0] != 'C')
			break;
		if (line[0] != 'F')
			set_color_value(line + 2, &consts->top);
		else
			set_color_value(line + 2, &consts->bot);
		line = get_next_line(fd_map);
	}
}

void texture_main(int fd_map, t_core *core)
{
	get_texture_from_map(fd_map, &core->consts);
	printf("%d, %d, %d\n", core->consts.bot.a, core->consts.bot.b, core->consts.bot.c);
	printf("%d, %d, %d\n", core->consts.top.a, core->consts.top.b, core->consts.top.c);
}
