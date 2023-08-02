/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:35:56 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/02 12:35:57 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool world_malloc(int height, int width, char ***map)
{
	int	i;

	i = 0;
    (*map) = malloc(sizeof(char *) * height + 1);
	if (!*map)
		return (false);
    (*map)[height] = 0;
	while (i < height)
	{
        (*map)[i] = malloc(sizeof(char) * width + 1);
		if (!(*map)[i])
			return (false);
		(*map)[i][width] = 0;
		i++;
	}
	return (true);
}

static bool world_creator(t_map *map, uint32_t anbiant_sound, int height, int width, Difficulty difficulty, const uint32_t bt_color[2])
{
	map->height = height;
	map->width = width;
	map->abiant_sound = anbiant_sound;
    map->bt_color[0] = 0;
	map->bt_color[1] = 0;
	map->difficulty = difficulty;
	world_malloc(height, width, &map->chunk);
	world_malloc(height * 4, width * 4, &map->world);
    return (true);
}

static void world_generator(t_map *map) {
    int y;
	int x;

    y = 0;
	x = 0;
    while (y < map->height) {
		while (x < map->width) {
			map->chunk[y][x++] = get_rand_num(2);
		}
		x = 0;
		y++;
    }

	y = 0;
	x = 0;
	while (y < map->height) {
		while (x < map->width)
			printf("%d", map->chunk[y][x++]);
		printf("\n");
		x = 0;
		y++;
	}
}

void	world_loader(t_core *core)
{
	world_creator(&core->maps[1], core->sounds.ambiant, 32, 32, HARD, 0);
    world_generator(&core->maps[1]);
}