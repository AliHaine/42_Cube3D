/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_func_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:09:14 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/04 19:09:15 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	get_rand_num(int max_val, int sleeper)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
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
