#include "../../includes/includes.h"

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_allowed_char(char c)
{
	if (c == '0' || c == '1' || is_player_char(c)
		||  c == 'Z' || c == 'V' || c == 'D' || c == ' ')
		return (true);
	return (false);
}

bool	is_cub(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i < 2)
		return (false);
	i--;
	if (str[i] != 'b' && str[i - 1] != 'u' && str[i - 2] != 'c'
		&& str[i - 3] != '.')
		return (false);
	return (true);
}

short	get_direction_code(char *s)
{
	if (ft_strlen(s) < 1)
		return (4);
	if (s[0] == 'N' && s[1] == 'O')
		return (0);
	if (s[0] == 'S' && s[1] == 'O')
		return (2);
	if (s[0] == 'W' && s[1] == 'E')
		return (3);
	if (s[0] == 'E' && s[1] == 'A')
		return (1);
	return (4);
}