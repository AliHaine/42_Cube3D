#include "../../includes/includes.h"



static bool	fill_map_tab(char *line, char *tab, int max)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_allowed_char(line[i]))
			return (false);
		tab[i] = line[i];
		i++;
	}
	while (i < max)
		tab[i++] = ' ';
	tab[i] = '\0';
	return (true);
}

void	parse_main(t_t_i ti, int fd_map, t_core *core)
{
	char *line;

	while (ti.a < ti.c)
	{
		core->consts->map[ti.a] = malloc(sizeof(char) * (ti.b + 1));
		line = get_next_line(fd_map);
		fill_map_tab(line, core->consts->map[ti.a], ti.b);
		ti.a++;
	}
	ti.a = 0;
	while (ti.a < ti.c)
	{
		printf("%s\n", core->consts->map[ti.a]);
		ti.a++;
	}
}