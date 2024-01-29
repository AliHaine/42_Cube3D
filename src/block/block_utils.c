/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 00:17:09 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/25 00:17:10 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/concepts/block.h"

bool	is_rigid_block(Block block)
{
	return (get_block(block)->is_rigid);
}

bool	is_char_block(char c)
{
	if (!get_block_from_char(c))
		return (false);
	return (true);
}
