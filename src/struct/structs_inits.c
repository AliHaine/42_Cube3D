#include "../../includes/includes.h"

void	map_struct_init(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->difficulty = 0;
	map->bt_color[1] = get_rgb_color(0, 191, 255, 255);
	map->bt_color[0] = get_rgb_color(32, 139, 34, 255);;
	map->map = 0;
}
