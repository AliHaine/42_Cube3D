/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:35:04 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/07 11:52:02 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*ptr;

	if (!s1)
		return (0);
	i = 0;
	j = (unsigned int)(ft_strlen(s1) - 1);
	k = 0;
	while (s1[i] && ft_isset(s1[i], set))
		i++;
	while (s1[i] && ft_isset(s1[j], set))
		j--;
	if (ft_strlen(s1) == 0)
		return (ft_calloc(1, sizeof(char)));
	ptr = (char *)malloc((j - (i - 1)) + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, (s1 + i), (j - i + 2));
	return (ptr);
}
