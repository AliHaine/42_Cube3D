/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:02:00 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/11 17:29:13 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstneww(void *content, void (*del)(void *))
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
	{
		(*del)(content);
		return (0);
	}
	ptr->content = content;
	ptr->next = 0;
	return (ptr);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*indice;

	if (!lst || !(*f) || !(*del))
		return (0);
	ptr = ft_lstneww((*f)(lst->content), (*del));
	if (!ptr)
		return (0);
	indice = ptr->next;
	while (lst->next)
	{
		lst = lst->next;
		indice = ft_lstneww((*f)(lst->content), (*del));
		if (!indice)
		{
			ft_lstclear(&ptr, (*del));
			break ;
		}
		ft_lstadd_back(&ptr, indice);
	}
	return (ptr);
}
