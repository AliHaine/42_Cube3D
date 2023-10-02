/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:49:11 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 12:49:14 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

static void	select_sprite_ter(t_sprite *sp, char c)
{
	if (c == ';')
	{
		if (!set_texture_from_path("assets/sprites/fire_coral.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 312 + get_rand_num(412, 2);
	}
	else if (c == '?')
	{
		if (!set_texture_from_path("assets/sprites/warped_fungus.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 196;
	}
	else if (c == '/')
	{
		if (!set_texture_from_path("assets/sprites/wither_rose.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 196;
	}
}

static bool	select_sprite_bis(t_sprite *sp, char c)
{
	if (c == '^')
	{
		if (!set_texture_from_path("assets/sprites/carrots_stage1.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 312 + get_rand_num(412, 2);
		return (true);
	}
	else if (c == ':')
	{
		if (!set_texture_from_path("assets/sprites/crimson_fungus.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 196;
		return (true);
	}
	return (false);
}

void	select_sprite(t_sprite *sp, char c)
{
	if (c == '>')
	{
		if (!set_texture_from_path("assets/sprites/pink_tulip.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 228;
	}
	else if (c == '<')
	{
		if (!set_texture_from_path("assets/sprites/poppy.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 228;
	}
	else if (c == 'v')
	{
		if (!set_texture_from_path("assets/sprites/brown_mushroom.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->scale = 196;
	}
	else if (!select_sprite_bis(sp, c))
		select_sprite_ter(sp, c);
}

void	free_all_sprites(t_world *world)
{
	int	s;
	int	chunk;

	chunk = -1;
	if (!world->sprites)
		return ;
	while (++chunk < 9)
	{
		s = -1;
		if (!world->sprites[chunk])
			continue ;
		while (world->sprites[chunk][++s])
			free(world->sprites[chunk][s]);
		free(world->sprites[chunk]);
	}
	free(world->sprites);
}
