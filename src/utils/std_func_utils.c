#include "../../includes/includes.h"

int     get_rand_num(int max_val, int sleeper)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);

	usleep(sleeper);
    srand(tv.tv_usec);
    return (rand() % max_val);
}

void	put_two_string(char *dst, const char *s1, const char *s2, char *num)
{
	int	i;

	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	while (num && *num)
		dst[i++] = *num++;
	dst[i++] = '.';
	dst[i++] = 'p';
	dst[i++] = 'n';
	dst[i++] = 'g';
	dst[i] = '\0';
}

static size_t	nbrcount(long int n)
{
    size_t	res;

    res = 0;
    if (n <= 0)
    {
        n = -n;
        res++;
    }
    while (n)
    {
        n /= 10;
        res++;
    }
    return (res);
}

char	*ft_itoa(int n)
{
    size_t		len;
    char		*ptr;
    long int	ln;

    ln = n;
    len = nbrcount(ln) + 1;
    ptr = (char *)malloc(sizeof(char) * len);
    if (!ptr)
        return (0);
    if (ln < 0)
    {
        ptr[0] = '-';
        ln = -ln;
    }
    len--;
    ptr[len] = '\0';
    len--;
    if (ln == 0)
        ptr[0] = '0';
    while (ln > 0)
    {
        ptr[len--] = ln % 10 + '0';
        ln /= 10;
    }
    return (ptr);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi_for_texture(const char *s)
{
	int i;
	int	val;

	i = 0;
	val = 0;
	if (!s)
		return (-1);
	if (s[0] == '0')
		return (0);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (-1);
		val += (s[i++] - '0');
		val *= 10;
	}
	val /= 10;
	if (val > 255 || val < 0)
		return (-1);
	return (val);
}

bool	is_str_blank(const char *s)
{
	while(*s && *s != '\n')
	{
		if (*s != ' ')
			return (false);
		s++;
	}
	return (true);
}

void	free_tab(char **tab, int size)
{
	while (size-- >= 0)
		free(tab[size]);
	free(tab);
}

void	copy_tab(char **tab_src, char **tab_dst, int height, int width)
{
	int	i;

	i = width;
	while (height-- > 0)
	{
		while (i-- > 0)
			tab_dst[height][i] = tab_src[height][i];
		i = width;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!fd || (fd < 0 || fd > 255) || !s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (*((unsigned char *)(s1 + i)) != *((unsigned char *)(s2 + i)))
			return (*((unsigned char *)(s1 + i))
					- *((unsigned char *)(s2 + i)));
		i++;
	}
	return (*((unsigned char *)(s1 + i)) - *((unsigned char *)(s2 + i)));
}
