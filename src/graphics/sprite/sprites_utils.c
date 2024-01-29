/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:49:02 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 12:49:07 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

void	init_sprite_vars(t_sprite *sp, t_player *player, mlx_texture_t *img)
{
	sp->fog = sp->dist / FOG_DISTANCE;
	if (sp->fog > 1)
		return ;
	sp->vars.s_pos[2] = SCREEN_HEIGHT / 2.f;
	sp->vars.s_pos[0] = (sp->sp_xy[0] - player->player_pos_xy[0]);
	sp->vars.s_pos[1] = (sp->sp_xy[1] - player->player_pos_xy[1]);
	sp->vars.tmp[0] = sp->vars.s_pos[1] * -player->cos + sp->vars.s_pos[0] * player->sin;
	sp->vars.tmp[1] = sp->vars.s_pos[0] * player->cos + sp->vars.s_pos[1] * player->sin;
	sp->vars.s_pos[0] = sp->vars.tmp[0];
	sp->vars.s_pos[1] = sp->vars.tmp[1];
	sp->vars.s_pos[0] = (sp->vars.s_pos[0] * -1280 / sp->vars.s_pos[1]) + (SCREEN_WIDTH / 2.f);
	sp->vars.s_pos[1] = (sp->vars.s_pos[2] * 70 / sp->vars.s_pos[1]) + (SCREEN_HEIGHT / 2.f);
	sp->vars.size[0] = (int)((float)(img->width * sp->scale) / sp->vars.tmp[1]);
	sp->vars.size[1] = (int)((float)(img->height * sp->scale) / sp->vars.tmp[1]);
	if (sp->vars.size[0] < 0)
		sp->vars.size[0] = 0;
	if (sp->vars.size[1] < 0)
		sp->vars.size[1] = 0;
	sp->vars.t_pos[0] = (float)img->width;
	sp->vars.offset[0] = (float)img->width / (float)sp->vars.size[0];
	sp->vars.offset[1] = (float)img->height / (float)sp->vars.size[1];
	sp->vars.x = 0;
}

void	realloc_sprites(t_sprite ***sprites, int len)
{
	t_sprite	**new_tab;
	int			s;

	s = -1;
	new_tab = (t_sprite **)malloc(sizeof(t_sprite *) * (len + 2));
	while (++s < len)
		new_tab[s] = (*sprites)[s];
	new_tab[s] = (t_sprite *)malloc(sizeof(t_sprite));
	new_tab[s + 1] = NULL;
	if (*sprites)
	{
		free(*sprites);
		*sprites = NULL;
	}
	*sprites = new_tab;
}

void	reload_sprite_pos(t_world *world)
{
	int	chunk;
	int	s;

	chunk = -1;
	while (++chunk < 9)
	{
		s = -1;
		while (world->sprites[chunk][++s])
		{
			world->sprites[chunk][s]->cell_xy[0] = (int)(world->sprites
				[chunk][s]->x_origin + (world->width * (chunk % 3)));
			world->sprites[chunk][s]->cell_xy[1] = (int)(world->sprites
				[chunk][s]->y_origin + (world->height * (int)
						lround(((float)chunk - 1.f) / 3.f)));
			world->sprites[chunk][s]->sp_xy[0] = ((float)
					(world->sprites[chunk][s]->cell_xy[0]) + 0.5f) * 64;
			world->sprites[chunk][s]->sp_xy[1] = ((float)
					(world->sprites[chunk][s]->cell_xy[1]) + 0.5f) * 64;
			world->sprites[chunk][s]->chunk_sp_xy[0] = world->sprites
			[chunk][s]->sp_xy[0];
			world->sprites[chunk][s]->chunk_sp_xy[1] = world->sprites
			[chunk][s]->sp_xy[1];
		}
	}
}
