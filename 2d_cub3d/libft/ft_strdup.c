/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:23:04 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/04 11:06:14 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{	
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s1);
	ptr = malloc((len * sizeof(char)) + 1);
	if (!ptr)
		return (0);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
