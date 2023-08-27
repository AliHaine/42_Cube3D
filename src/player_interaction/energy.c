/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   energy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:39:28 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/27 14:39:29 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

bool	take_energy(t_player *player, int value)
{
	if (player->energy <= 0)
		return (false);
	if (player->energy - value <= 0)
		player->energy = 0;
	else
		player->energy -= value;
	return (true);
}

bool	add_energy(t_player *player, int value)
{
	if (player->energy == 100)
		return (false);
	if (player->energy + value > 100)
		player->energy = 100;
	else
		player->energy += value;
	return (true);
}

bool	player_have_energy(int value)
{
	if (value <= 0)
		return (false);
	return (true);
}

bool	player_have_enough_energy(t_player *player, int value)
{
	if (player->energy < value)
		return (false);
	return (true);
}
