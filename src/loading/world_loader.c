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

bool world_creator(t_map *map, uint32_t anbiant_sound, int height, int width, Difficulty difficulty, const uint32_t bt_color[2])
{
	map->height = height;
	map->width = width;
	map->abiant_sound = anbiant_sound;
    map->bt_color[0] = 0;
	map->bt_color[1] = 0;
	map->difficulty = difficulty;
	world_malloc(height, width, &map->chunk);
	world_malloc(height * 3, width * 3, &map->world);
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
    int world_yx[2];
    int chunk_yx[2];

    world_yx[0] = 0;
    world_yx[1] = 0;
    chunk_yx[0] = 0;
    chunk_yx[1] = 0;
    while (world_yx[0] < (world->height * 3))
    {
        world->world[world_yx[0]][world_yx[1]++] = world->chunk[chunk_yx[0]][chunk_yx[1]++];
        if (chunk_yx[1] >= world->width) {
            printf("enter first if, %d %d\n", chunk_yx[0], world_yx[0]);
            chunk_yx[1] = 0;


            if (world_yx[1] >= (world->width * 3)) {
                printf("enter if\n");
				chunk_yx[0]++;
				if (chunk_yx[0] >= world->height) {
					printf("enter second if\n");
					chunk_yx[0] = 0;
				}
                world_yx[0]++;
                world_yx[1] = 0;
                //exit(1);
            }
        }
		printf("end\n");
    }
    printf("value = %c\n", world->world[0][0]);
    int y = 0;
    int x = 0;
    while (y < (world->height * 3)) {
        printf("%c", world->world[y][x++]);
        if (x > ((world->width * 3) - 1)) {
            x = 0;
            y++;
            printf("\n");
        }
    }
}

void	world_loader(t_core *core)
{
	world_creator(&core->maps[1], core->sounds.ambiant, 32, 32, HARD, 0);
    world_generator(&core->maps[1]);
    world_copy_from_chunk(&core->maps[1]);

    world_copy_from_chunk(&core->maps[0]);

}