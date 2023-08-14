#include "../../includes/includes.h"

static bool	set_player(int x, int y, t_player *player)
{
	player->playerpos[0] = (y * 64) + 32;
	player->playerpos[1] = (x * 64) + 32;
	player->playerangle = 0;
	return (true);
}

//todo
static bool	fill_map_tab(char *line, char *tab, t_player *player, t_map *map, int iterator)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_allowed_char(line[i]))
			return (false);
		if (is_player_char(line[i]))
		{
			player->have_player = true;
			set_player(iterator + map->width, i + map->height, player);
			tab[i] = '0';
		}
		else
			tab[i] = line[i];
		i++;
	}
	while (i < map->width)
		tab[i++] = ' ';
	tab[i] = '\0';
	return (true);
}

bool	parse_main(t_file *file, t_player *player, t_map *map)
{
	int iterator;

	iterator = 0;
	while (iterator < map->height)
	{
		//map->chunk[iterator] = malloc(sizeof(char) * (map->width + 1));

		if (!fill_map_tab(file->line, map->chunk[iterator], player, map, iterator))
		{
			msg_write(2, 2, ERROR_MAP_CHAR);
			return (false);
		}
		iterator++;
		get_next_line(file);
	}
	if (!player->have_player)
		msg_write(2, 2, ERROR_PLAYER);
	return (true);
}