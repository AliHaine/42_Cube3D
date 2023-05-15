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
		||  c == 'Z' || c == 'V' || c == ' ')
		return (true);
	return (false);
}

char	*convert_to_path(char *name)
{
	char	*path;

	path = malloc(sizeof(char) * (ft_strlen(name) + 6));
	ft_strcpy(path, "maps/");
	ft_strcat(path, name);
	return (path);
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
