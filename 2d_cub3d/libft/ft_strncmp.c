/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:49:24 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/03 16:05:27 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1[i] && s2[i])
	{
		if (*((unsigned char *)(s1 + i)) != *((unsigned char *)(s2 + i)))
			return (*((unsigned char *)(s1 + i))
				- *((unsigned char *)(s2 + i)));
		i++;
	}
	return (*((unsigned char *)(s1 + i)) - *((unsigned char *)(s2 + i)));
}
