/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:32:45 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/08 09:52:01 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	o;

	i = 0;
	o = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			o = i;
		i++;
	}
	if (s[i] == (char)c)
		o = i;
	if (o != -1)
		return ((char *)(s + o));
	return (0);
}
