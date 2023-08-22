#include "../../includes/includes.h"

static size_t	calc_malloc(char const *s, char c)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			res++;
		}
	}
	return (res + 1);
}

static char	*get_tab(char const *s, char c, size_t indice)
{
	char	*tab;
	size_t	len;
	size_t	i;
	size_t	j;

	j = 0;
	len = 0;
	i = indice;
	while (i < ft_strlen(s) && s[i] != c)
	{
		len++;
		i++;
	}
	tab = (char *)malloc((sizeof(char) * (len + 1)));
	if (!tab)
		return (0);
	i = indice;
	while (s[i] && s[i] != c)
	{
		tab[j] = s[i];
		j++;
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

static void	*freestrtab(char **str, size_t indice)
{
	size_t	i;

	i = 0;
	while (i < indice)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**setzero(char **s, size_t i)
{
	s[i] = 0;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * calc_malloc(s, c));
	if (!result)
		return (0);
	i = 0;
	j = -1;
	while (++j < calc_malloc(s, c) - 1)
	{
		while (s[i] && s[i] == c)
			i++;
		if (i < ft_strlen(s) && s[i] != c)
		{
			result[j] = get_tab(s, c, i);
			if (!result[j])
				return (freestrtab(result, j));
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (setzero(result, j));
}