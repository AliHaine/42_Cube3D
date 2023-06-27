/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:45:33 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/08 16:11:12 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		res;
	t_list	*tmp;

	if (!lst)
		return (0);
	res = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		res++;
	}
	return (res);
}
