#include "../../includes/includes.h"
#include "../../includes/defines.h"

static bool	set_map_size_value(t_t_i *ti, t_file *file)
{
	int		size;

	while (file->line)
	{
		size = ft_strlen(file->line);
		if (size > ti->b)
			ti->b = size - 1;
		get_next_line(file);
		ti->c++;
	}
	if (ti->b <= 0 || ti->c <= 0)
		return (false);
	return (true);
}

static bool	map_value_init(t_t_i *ti, t_file *file, t_const *consts, int start)
{
	if (!set_map_size_value(ti, file))
	{
		close(file->fd);
		msg_write(2, 1, ERROR_MAP_CHAR);
		return (0);
	}
	reopen_file(file, start, O_RDONLY);
	consts->map = malloc(sizeof(char *) * (ti->c + 2));
	consts->map[ti->c + 1] = 0;
	return (1);
}

void	map_manager(char *map_path, t_core *core)
{
	t_file	file;
	t_t_i	ti;
	int		save;

	msg_write(2, -1, CHECK_MAP);
	usleep(500000 * LOAD);
	basical_map_check(map_path);
	init_tti_struct(&ti, 0, 0, -1);
	open_file(&file, map_path, O_RDONLY);
	msg_write(1, -1, NO_ERROR);
	texture_main(&file, core);
	save = file.line_num;
	map_value_init(&ti, &file, &core->consts, save);
	parse_main(ti, &file, core);
	core->consts.map_width = ti.b;
	core->consts.map_height = ti.c;
}
