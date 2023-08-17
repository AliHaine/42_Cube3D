#include "../../includes/includes.h"

//todo
int	get_chunk_from_pos(int x, int y, int m_height, int m_width)
{
	int i;

	i = 0;
	//printf("start %d %d\n--------------------\n", x , y);
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
	//printf("rien %d %d\n-------------------------\n", x, y);
	return (0);
}

int get_player_chunk_pos_from_pos(int position, int size)
{
	return (((position - 32) - size) / 64);
}


int	get_chunk_from_pos2(int x, int y, int m_height, int m_width)
{
    int i;

    i = 0;
    //printf("start %d %d %d\n--------------------\n", y, x, m_height);
    if (y < (m_height - 1))
    {
        //printf("11\n");
        while (i++ < 4)
        {
            if (x < (m_width - 1) * i)
                return (i - 1);
        }
    }
    else if (y < m_height * 2)
    {
        //printf("22\n");
        while (i++ < 4)
        {
            if (x < m_width * i)
                return ((i - 1) + 3);
        }
    }
    else
    {
        //printf("33\n");
        while (i++ < 4)
        {
            if (x < m_width * i)
                return ((i - 1) + 6);
        }
    }
    //printf("rien %d %d\n-------------------------\n", x, y);
    return (0);
}

bool    is_player_chunk_change(t_player *player, t_map *map)
{
	int	player_x;
	int	player_y;

	player_x = get_player_chunk_pos_from_pos(player->player_pos_xy[0], map->width);
	player_y = get_player_chunk_pos_from_pos(player->player_pos_xy[1], map->height);
	//printf("%d %d %f\n", player_x, player_y, ((player->player_pos_xy[1] - 32) - map->height) / 64);

	if (player_x >= (map->width - 1) && player_x <= ((map->width - 1) * 2)
		&& player_y >= (map->height - 1) && player_y <= ((map->height - 1) * 2))
        return (false);
    return (true);
}

bool    world_dynamic_generator()
{

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