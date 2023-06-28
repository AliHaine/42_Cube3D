/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:43:11 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/17 13:05:55 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{	
	void	*ptr;
	size_t	i;
	size_t	finalsize;

	i = 0;
	finalsize = count * size;
	ptr = malloc(finalsize);
	if (!ptr)
		return (0);
	while (i < finalsize)
	{
		*((char *)(ptr + i)) = 0;
		i++;
	}
	return (ptr);
}
