#include "../../includes/includes.h"

void print_entire_world(t_map *map)
{
	int wi = 0;
	int y = -1;
	int x = -1;
	int tabnum = 0;

	while (wi < 8) {
		while (y++ < map->height - 1) {
			while (x++ < map->width - 1)
				printf("%c", map->world[wi][y][x]);
			if (tabnum++ < 2) {
				printf(" ");
				y -= 1;
				wi++;
			} else {
				wi -= 2;
				tabnum = 0;
				printf("\n");
			}
			x = -1;
		}
		printf("\n");
		wi += 3;
		y = -1;
	}
}
