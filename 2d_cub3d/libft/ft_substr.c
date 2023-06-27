/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:10:46 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/07 14:42:05 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{	
	size_t			i;
	char			*ptr;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	else if (len > ft_strlen(s + start))
		ptr = (char *)malloc((sizeof(char) * (ft_strlen(s + start))) + 1);
	else
		ptr = (char *)malloc((sizeof(char) * len) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s[start] && i < len)
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
