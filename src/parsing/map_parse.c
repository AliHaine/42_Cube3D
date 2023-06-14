#include "../../includes/includes.h"

static bool	set_player(int x, int y, t_player *player)
{
	player->playerpos[0] = (y * 64) + 32;
	player->playerpos[1] = (x * 64) + 32;
	player->playerangle = 0;
	return (true);
}

static bool	fill_map_tab(char *line, char *tab, t_t_i ti, t_player *player)
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
			set_player(ti.a, i, player);
		}
		tab[i] = line[i];
		i++;
	}
	while (i < ti.b)
		tab[i++] = ' ';
	tab[i] = '\0';
	return (true);
}

bool	parse_main(t_t_i ti, t_file *file, t_core *core)
{
	while (ti.a <= ti.c)
	{
		core->consts.map[ti.a] = malloc(sizeof(char) * (ti.b + 1));
		//free ici si error
		if (!fill_map_tab(file->line, core->consts.map[ti.a], ti, &core->player))
		{
			msg_write(2, 2, ERROR_MAP_CHAR);
			return (false);
		}
		ti.a++;
		get_next_line(file);
	}
	if (!core->player.have_player)
		msg_write(2, 2, ERROR_PLAYER);
	return (true);
}