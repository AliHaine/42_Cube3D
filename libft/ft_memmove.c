/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:47:00 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/03 09:48:33 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{	
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	if ((unsigned char *)(dst) > (unsigned char *)(src))
	{	
		while (len-- > 0)
		{
			*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
		}
		return (dst);
	}
	else
	{	
		while (i < len)
		{	
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
		return (dst);
	}
}
