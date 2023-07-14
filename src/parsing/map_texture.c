#include "../../includes/includes.h"
#include "../../includes/defines.h"

static void	set_color_value(const char *line, uint32_t *target_color)
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
		if (b > 3 || i > 3) {
			msg_write(1, -1, FAILURE);
			break ;
		}
		value[i][b++] = *line++;
	}
	value[i][b-1] = '\0';
	*target_color = (ft_atoi_for_texture(value[0]) << 24) + (ft_atoi_for_texture(value[1]) << 16) + (ft_atoi_for_texture(value[2]) << 8) + 255;
	free(value);
	msg_write(1, -1, SUCCESS);
}

static void	get_color_from_map(t_file *file, t_const *consts)
{
	while (file->line)
	{
		if (file->line[0] && file->line[0] != 'F' && file->line[0] != 'C') {
			if (file->line[0] == '\n')
				break ;
			get_next_line(file);
			continue ;
		}
		msg_write_multiple(1, Messages[TRY_LOAD_COLOR], file->line);
		usleep(300000 * LOAD);
		if (file->line[0] != 'F')
			set_color_value(file->line + 2, &consts->bt_color[1]);
		else
			set_color_value(file->line + 2, &consts->bt_color[0]);
		get_next_line(file);
	}
	while (file->line && file->line[0] && file->line[0] == '\n')
		get_next_line(file);
}

static void	get_image_from_map(t_file *file, t_imgs *imgs)
{
	short	direction;

	while (file->line)
	{
		direction = get_direction_code(file->line);
		if (direction >= 4) {
			if (file->line[0] == '\n')
				break ;
			get_next_line(file);
			continue ;
		}
		usleep(500000 * LOAD);
		if (set_texture_from_path((file->line + 3), &imgs->wall_texture[direction]))
			msg_write(1, -1, SUCCESS);
		else
			msg_write(2, -1, FAILURE);
		get_next_line(file);
	}
	if (is_wall_empty(imgs) == true)
		set_default_wall_texture(imgs);
	while (file->line && file->line[0] == '\n')
		get_next_line(file);
}

void	texture_main(t_file *file, t_core *core)
{
	msg_write(1, -1, GET_MAP_CONTENT);
	usleep(500000 * LOAD);
	get_next_line(file);
	get_image_from_map(file, &core->imgs);
	get_color_from_map(file, &core->consts);
	msg_write(1, -1, SUCCESS);
}
