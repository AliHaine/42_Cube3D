/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:56:07 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/09 13:09:26 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;
	size_t	i;
	size_t	j;

	if (!lst || !(*f))
		return ;
	i = 0;
	j = ft_lstsize(lst);
	tmp = lst;
	while (i < j)
	{
		(*f)(tmp->content);
		tmp = tmp->next;
		i++;
	}
}
