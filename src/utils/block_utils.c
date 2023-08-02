/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:05:11 by ayagmur           #+#    #+#             */
/*   Updated: 2023/07/31 17:05:13 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

t_block *get_block_from_char(t_block **block, char block_char)
{
	while (*block)
	{
		if ((*block)->block_char == block_char)
			return (*block);
		block++;
	}
	return (0);
}
