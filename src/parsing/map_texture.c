/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:47:37 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/27 14:47:39 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

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
	while (*line && *line == ' ')
		line++;
	while (*line)
	{
		if (*line == ',')
		{
			value[i][b] = '\0';
			i++;
			b = 0;
			line++;
		}
		if (b > 3 || i > 3)
		{
			msg_write(1, -1, FAILURE);
			break ;
		}
		value[i][b++] = *line++;
	}
	value[i][b - 1] = '\0';
	*target_color = (ft_atoi_for_texture(value[0]) << 24) + (ft_atoi_for_texture(value[1]) << 16) + (ft_atoi_for_texture(value[2]) << 8) + 255;
	free(value);
	msg_write(1, -1, SUCCESS);
}

static void	get_color_from_map(t_file *file, uint32_t bt_color[2])
{
	char	first_key;

	first_key = 'F';
	if (!file->line || file->line[0] != 'F' && file->line[0] != 'C' || file->line[1] != ' ')
		msg_write(2, 2, ERROR_PARSING_CHAR);
	msg_write_multiple(1, Messages[TRY_LOAD_COLOR], file->line);
	usleep(300000 * LOAD);
	if (file->line[0] != 'F')
	{
		first_key = 'C';
		set_color_value(file->line + 2, &bt_color[1]);
	}
	else
		set_color_value(file->line + 2, &bt_color[0]);
	get_next_line(file);
	if (!file->line && file->line[0] != 'F' && file->line[0] != 'C' || file->line[1] != ' ')
		msg_write(2, 2, ERROR_PARSING_CHAR);
	msg_write_multiple(1, Messages[TRY_LOAD_COLOR], file->line);
	usleep(300000 * LOAD);
	if (file->line[0] == first_key)
		msg_write(2, 2, ERROR_KEY_ALREADY);
	if (file->line[0] != 'F')
		set_color_value(file->line + 2, &bt_color[1]);
	else
		set_color_value(file->line + 2, &bt_color[0]);
	get_next_line(file);
	while (file->line && file->line[0] == '\n')
		get_next_line(file);
}

static void	get_image_from_map(t_file *file, t_imgs *imgs)
{
	int	direction;
	int	space;

	space = 3;
	while (file->line)
	{
		if (file->line[0] == '\n')
			break ;
		direction = get_direction_code(file->line);
		if (direction >= 4)
			msg_write(2, 1, ERROR_PARSING_CHAR);
		if (!imgs->wall_texture[direction])
		{
			while (file->line[space] == ' ')
				space++;
			if (!set_texture_from_path((file->line + space), &imgs->wall_texture[direction]))
				msg_write(2, 2, ERROR_FATAL);
			space = 3;
		}
		else
			msg_write(2, 1, ERROR_KEY_ALREADY);
		get_next_line(file);
	}
	if (is_wall_empty(imgs))
		set_default_wall_texture(imgs);
	while (file->line && file->line[0] == '\n')
		get_next_line(file);
}

void	texture_main(t_file *file, t_imgs *imgs, uint32_t bt_color[2])
{
	msg_write(1, -1, GET_MAP_CONTENT);
	usleep(500000 * LOAD);
	get_next_line(file);
	get_image_from_map(file, imgs);
	get_color_from_map(file, bt_color);
	msg_write(1, -1, SUCCESS);
}
