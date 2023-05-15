/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:48:19 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:48:26 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

void	move_right_left(t_core *core, int direction)
{
	if (core->consts->map[(int)((core->playerpos[1]
				- (sinf(core->playerangle - PI / 2) * WALK_SPEED)) / 64)]
				[(int)((core->playerpos[0] -(cosf(core->playerangle - PI / 2)
				* WALK_SPEED)) / 64)] != 1
				&& direction == 1)
	{
		core->playerpos[0] -= cosf(core->playerangle - PI / 2) * WALK_SPEED;
		core->playerpos[1] -= sinf(core->playerangle - PI / 2) * WALK_SPEED;
	}
	else if (core->consts->map[(int)(core->playerpos[1]
			+ (sinf(core->playerangle - PI / 2) * WALK_SPEED)) / 64]
				[(int)((core->playerpos[0] + (cosf(core->playerangle - PI / 2)
				* WALK_SPEED)) / 64)] != 1
				&& direction == 0)
	{
		core->playerpos[0] += cosf(core->playerangle - PI / 2) * WALK_SPEED;
		core->playerpos[1] += sinf(core->playerangle - PI / 2) * WALK_SPEED;
	}
}

void	move_forward_backward(t_core *core, int direction)
{
	if (core->consts->map[(int)((core->playerpos[1]
				- (sinf(core->playerangle) * WALK_SPEED)) / 64)]
				[(int)((core->playerpos[0] - (cosf(core->playerangle)
				* WALK_SPEED)) / 64)] != 1
					&& direction == 1)
	{
		core->playerpos[0] -= cosf(core->playerangle) * WALK_SPEED;
		core->playerpos[1] -= sinf(core->playerangle) * WALK_SPEED;
	}
	else if (core->consts->map[(int)((core->playerpos[1] + (sinf(core->playerangle)
					* WALK_SPEED)) / 64)][(int)((core->playerpos[0] +
					(cosf(core->playerangle) * WALK_SPEED)) / 64)] != 1
					&& direction == 0)
	{
		core->playerpos[0] += cosf(core->playerangle) * WALK_SPEED;
		core->playerpos[1] += sinf(core->playerangle) * WALK_SPEED;
	}
}

void	move_rotate(t_core *core, int direction)
{
	if (direction == 0)
	{
		core->playerangle -= SENSIBILITY;
		if (core->playerangle < 0)
			core->playerangle += 6.28319;
	}
	else if (direction == 1)
	{
		core->playerangle += SENSIBILITY;
		if (core->playerangle > 6.28319)
			core->playerangle -= 6.28319;
	}
}
