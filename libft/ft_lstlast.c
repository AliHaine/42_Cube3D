/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:05:59 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/08 16:12:26 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;

	if (!lst)
		return (0);
	i = 0;
	j = ft_lstsize(lst);
	tmp = lst;
	while (i < j - 1)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}
