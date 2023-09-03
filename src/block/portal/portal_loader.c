/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:35:32 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 18:35:34 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/concepts/portal.h"

/* Create a new portal
 *
 * @param portal	The enum value of the portal
 * @param world		The enum value of the world destination
 * @param block		The enum value of the block who is the portal */

void	create_portal(Portal portal, World world, Block block)
{
	t_portal new_portal;

	new_portal.portal_name = portal;
	new_portal.world_destination = get_world(world);
	new_portal.block_portal = get_block(block);
	set_portal(new_portal);
}

void portal_loader()
{
	create_portal(PORTAL_NETHER, WORLD_NETHER, NETHERPORTAL);
	create_portal(PORTAL_END, WORLD_END, BLOCK_END_PORTAL);
	create_portal(PORTAL_BACKROOM, WORLD_BACKROOM, BUG);
}
