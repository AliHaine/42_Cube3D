#include "../../includes/includes.h"

int	get_chunk_from_pos(int x, int y, int m_height, int m_width)
{
	int i;

	i = 0;
	if (y < m_height)
	{
		while (i++ < 4)
		{
			if (x < m_width * i)
				return (i - 1);
		}
	}
	else if (y < m_height * 2)
	{
		while (i++ < 4)
		{
			if (x < m_width * i)
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
}