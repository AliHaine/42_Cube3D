/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:11:53 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/10 12:58:38 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack && !len)
		return (0);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{	
		j = 0;
		while (needle[j] && haystack[i] == needle[j] && i < len)
		{
			i++;
			j++;
		}
		if (j < ft_strlen(needle))
		{
			i -= j;
			i++;
		}
		else
			return ((char *)(haystack + i - ft_strlen(needle)));
	}
	return (0);
}
