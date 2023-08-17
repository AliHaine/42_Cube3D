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
    (*map) = malloc(sizeof(char *) * (height + 1));
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

bool world_creator(t_map *map, uint32_t anbiant_sound, int height, int width, Difficulty difficulty, const uint32_t bt_color[2], bool is_active)
{
    int i;

    i = 0;
	map->height = height;
	map->width = width;
	map->abiant_sound = anbiant_sound;
    map->bt_color[0] = 0;
	map->bt_color[1] = 0;
	map->difficulty = difficulty;
    map->world = malloc(sizeof(char **) * 9);
	map->is_active = is_active;
	world_malloc(height, width, &map->chunk);
    while (i < 9)
	    world_malloc(height * 3, width * 3, &map->world[i++]);
    return (true);
}

static void world_generator(t_map *map) {
    int y;
	int x;

    y = 0;
	x = 0;
    while (y < map->height) {
		while (x < map->width) {
			map->chunk[y][x++] = get_rand_num(2) + '0';
		}
		x = 0;
		y++;
    }

	y = 0;
	x = 0;
	while (y < map->height) {
		while (x < map->width)
			printf("%c", map->chunk[y][x++]);
		printf("\n");
		x = 0;
		y++;
	}
}

static void world_copy_from_chunk(t_map *world)
{
    int chunk_yx[2];
    int world_iterator;

    chunk_yx[0] = -1;
    chunk_yx[1] = -1;
    world_iterator = -1;
    while (world_iterator++ < 8)
    {
        while (chunk_yx[0]++ < world->height - 1)
        {
            while (chunk_yx[1]++ < world->width - 1) {
                world->world[world_iterator][chunk_yx[0]][chunk_yx[1]] = world->chunk[chunk_yx[0]][chunk_yx[1]];
            }
            chunk_yx[1] = -1;
        }
        chunk_yx[0] = -1;
    }
    int wi = 0;
    int y = -1;
    int x = -1;
    int tabnum = 0;

    while (wi < 8) {
        while (y++ < world->height - 1) {
            while (x++ < world->width - 1)
                printf("%c", world->world[wi][y][x]);
            if (tabnum++ < 2) {
                y -= 1;
                wi++;
            } else {
                wi -= 2;
                tabnum = 0;
                printf("\n");
            }
            x = -1;
        }
        wi += 3;
        y = -1;
    }
    printf("close2\n");
}

void	world_loader(t_core *core)
{
	world_copy_from_chunk(&core->maps[0]);

	world_creator(&core->maps[1], core->sounds.ambiant, 32, 32, HARD, 0, false);
    world_generator(&core->maps[1]);
    world_copy_from_chunk(&core->maps[1]);
}