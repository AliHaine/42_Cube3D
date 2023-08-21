#include "../../includes/includes.h"

void print_entire_world()
{
	int wi = 0;
	int y = -1;
	int x = -1;
	int tabnum = 0;
	t_world	*world;

	world = get_active_world();
	while (wi < 8) {
		while (y++ < world->height - 1) {
			while (x++ < world->width - 1)
				printf("%c", world->world[wi][y][x]);
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
