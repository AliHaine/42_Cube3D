#include "../../includes/includes.h"

static void	set_player(int x, int y, t_player *player, t_map *map)
{
	player->player_pos_yx[0] = ((y + map->width) * 64) + 32;
	player->player_pos_yx[1] = ((x + map->height)  * 64) + 32;
	player->player_coords_xy[0] = (y  * 64) + 32;
	player->player_coords_xy[1] = (x  * 64) + 32;
	player->playerangle = 0;
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
			set_player(iterator, i, player, map);
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