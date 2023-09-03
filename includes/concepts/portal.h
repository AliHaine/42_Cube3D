/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:35:42 by ayagmur           #+#    #+#             */
/*   Updated: 2023/09/03 18:35:43 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PORTAL_H
#define PORTAL_H

#include "../includes.h"

typedef enum {
	PORTAL_NETHER,
	PORTAL_END,
	PORTAL_BACKROOM,
	PORTAL_NUMBER,
}	Portal;

typedef struct s_portal {
	Portal portal_name;
	t_world *world_destination;
	t_block *block_portal;
}	t_portal;

//laoder
void portal_loader();

//accessor
t_portal *get_portal(Portal portal);
t_portal *get_portal_from_char(char c);
void	set_portal(t_portal portal);

void	portal_listener(t_player *player, t_world *world);
void	portal_open(t_player *player);

#endif
