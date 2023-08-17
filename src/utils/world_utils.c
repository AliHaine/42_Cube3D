#include "../../includes/includes.h"

//todo
int	get_chunk_from_pos(int x, int y, int m_height, int m_width)
{
	int i;

	i = 0;
	if (y < (m_height - 1))
	{
		while (i++ < 4)
		{
			if (x < (m_width - 1) * i)
				return (i - 1);
		}
	}
	else if (y < m_height * 2)
	{
		while (i++ < 4)
		{
			if (x < (m_width - 1) * i)
				return ((i - 1) + 3);
		}
	}
	else
	{
		while (i++ < 4)
		{
			if (x < m_width * i)
				return ((i - 1) + 6);
		}
	}
	return (0);
}

bool    is_player_chunk_change(t_player *player, t_map *map)
{
	if (player->player_cell_xy[0] >= map->width && player->player_cell_xy[0] <= (map->width * 2)
		&& player->player_cell_xy[1] >= map->height && player->player_cell_xy[1] <= (map->height * 2))
        return (false);
    return (true);
}

void	set_side_from_int(int *side_hw[2], int num)
{
	if (num == 0)
	{
		*side_hw[0] = -1;
		*side_hw[1] = 0;
	}
	else if (num == 1)
	{
		*side_hw[0] = 1;
		*side_hw[1] = 0;
	}
	else if (num == 2)
	{
		*side_hw[0] = 0;
		*side_hw[1] = 0;
	}
	else if (num == 3)
	{
		*side_hw[0] = -1;
		*side_hw[1] = 1;
	}
}

void	world_free_side(t_map *map, const int side_hw[2])
{
	int i;
	int incrementation;
	int chunk;

	i = 0;
	incrementation = 1;
	chunk = 0;
	if (side_hw[0] >= 0)
		incrementation = 3;
	if (side_hw[0] == 1)
		chunk = 2;
	if (side_hw[1] == 1)
		chunk = 6;
	while (i++ < 3)
	{
		free_tab(map->world[chunk + incrementation], map->width);
	}
}

bool    world_dynamic_generator(t_map *map, int side)
{
	int side_hw[2];

	set_side_from_int((int **) &side_hw, side);
	world_free_side(map, side_hw);
	return (0);
}

int	get_active_world(t_map maps[2])
{
	int	i;

	i = 2;
	while (i-- >= 0)
		if (maps[i].is_active)
			return (i);
	return (0);
}