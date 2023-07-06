#include "../../includes/includes.h"


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

void	ft_strcpy(char *s1, const char *s2)
{
	if (!s1 || !s2)
		return ;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
}

void	ft_strcat(char *s1, const char *s2)
{
	if (!s1 || !s2)
		return ;
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
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
