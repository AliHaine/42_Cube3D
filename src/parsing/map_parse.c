/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:06:36 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 19:06:37 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//todo
static bool	fill_map_tab(char *line, t_player *player, t_world *world, int iterator)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_allowed_char(line[i]))
			return (false);
		else if (is_sprite_char(line[i]))
			add_sprite(world, 4, line[i], iterator, i);
		else if (is_player_char(line[i]))
		{
			player->have_player = true;
			set_player(i, iterator, player, 0);
			world->world[4][iterator][i] = '0';
		}
		else if (line[i] == ' ')
			world->world[4][iterator][i] = '0';
		else
			world->world[4][iterator][i] = line[i];
		i++;
	}
	while (i < world->width)
		world->world[4][iterator][i++] = '0';
	world->world[4][iterator][i] = '\0';
	return (true);
}

bool	parse_main(t_file *file, t_player *player, t_world *world)
{
	int	iterator;

	iterator = 0;
	while (iterator < world->height)
	{
		if (!fill_map_tab(file->line, player, world, iterator))
		{
			msg_write(2, 2, ERROR_MAP_CHAR);
			return (false);
		}
		iterator++;
		get_next_line(file);
	}
	if (!player->have_player)
	{
		msg_write(2, 2, ERROR_PLAYER);
	}
	return (true);
}
