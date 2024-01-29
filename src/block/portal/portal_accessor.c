/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_accessor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:22:06 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 19:22:07 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/concepts/portal.h"

static t_portal	g_portals[PORTAL_NUMBER];

t_portal	*get_portal(Portal portal)
{
	return (&g_portals[portal]);
}

t_portal	*get_portal_from_char(char c)
{
	int	i;

	i = -1;
	while (++i < PORTAL_NUMBER)
		if (get_portal(i)->block_portal->block_char == c)
			return (get_portal(i));
	return (0);
}

void	set_portal(t_portal portal)
{
	g_portals[portal.portal_name] = portal;
}
