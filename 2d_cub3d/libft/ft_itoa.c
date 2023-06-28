/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:08:54 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/07 16:37:03 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
