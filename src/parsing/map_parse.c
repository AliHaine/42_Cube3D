#include "../../includes/includes.h"

static bool set_player(int pos, char direction, char *tab, t_player *player)
{
	static bool havePlayer = false;

	if (havePlayer)
		return (false);
	havePlayer = true;
	tab[pos] = direction;
	player->playerpos[0] = 5 * 64;
	player->playerpos[1] = 5 * 64;
	player->playerangle = 0;
	return (true);
}

static bool	fill_map_tab(char *line, char *tab, int max, t_player *player)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_allowed_char(line[i]))
			return (false);
		tab[i] = line[i];
		if (is_player_char(line[i]))
			if (!set_player(i, line[i], tab, player))
				return (false);
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

	while (ti.a <= ti.c)
	{
		core->consts.map[ti.a] = malloc(sizeof(char) * (ti.b + 1));
		line = get_next_line(fd_map);
		if (!fill_map_tab(line, core->consts.map[ti.a], ti.b, &core->player))
			continue;
		ti.a++;
	}
	int i = 0; int a = 0;
	while (core->consts.map[i])
	{
		printf("%c", core->consts.map[i][a]);
		a++;
		if (!core->consts.map[i][a]) {
			i++;
			a = 0;
			printf("\n");
		}
	}

}