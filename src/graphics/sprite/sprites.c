/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:48:42 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 12:48:51 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

static void	draw_sp_pixel(t_sprite *sp, mlx_image_t *img_3d, mlx_texture_t *img, const float *dists)
{
	uint32_t	color;
	int			value;

	color = 0;
	value = ((int)sp->vars.t_pos[1] * (int)img->width
			- (int)sp->vars.t_pos[0]) * 4;
	if (value > 0 && value < ((img->height * img->width) * 4) - 4)
		color = (img->pixels[value] << 24) | (img->pixels[value + 1]
				<< 16) | (img->pixels[value + 2] << 8) | img->pixels[value + 3];
	if (color != 0 && dists[sp->vars.sc_xy[0]] > sp->dist)
	{
		color = apply_fog(color, sp->fog);
		mlx_put_pixel(img_3d, sp->vars.sc_xy[0], sp->vars.sc_xy[1], color);
	}
}

static void	draw_sprite(t_sprite *sp, mlx_image_t *img_3d, mlx_texture_t *img, const float *dists)
{
	while (sp->vars.x++ < sp->vars.size[0])
	{
		sp->vars.sc_xy[0] = (int)(sp->vars.s_pos[0] - (float)sp->vars.x) + (sp->vars.size[0] / 2);
		if (sp->vars.sc_xy[0] >= SCREEN_WIDTH || sp->vars.sc_xy[0] < 0)
		{
			sp->vars.t_pos[0] -= sp->vars.offset[0];
			continue ;
		}
		sp->vars.t_pos[1] = (float)img->height;
		sp->vars.y = 0;
		while (sp->vars.y++ < sp->vars.size[1] && ((int)sp->vars.t_pos[1] * img->width
				- (int)sp->vars.t_pos[0] >= 0))
		{
			sp->vars.sc_xy[1] = (int)(sp->vars.s_pos[1] - (float)sp->vars.y);
			if (sp->vars.sc_xy[1] >= 0 && sp->vars.sc_xy[1] < SCREEN_HEIGHT)
			{
				draw_sp_pixel(sp, img_3d, img, dists);
			}
			sp->vars.t_pos[1] -= sp->vars.offset[1];
		}
		sp->vars.t_pos[0] -= sp->vars.offset[0];
	}
}

bool	sprite_are_sorted(t_sprite **sprite)
{
	int	i;
	int	j;

	i = -1;
	while (sprite[++i])
	{
		j = i;
		while (sprite[++j])
		{
			if (sprite[i]->dist < sprite[j]->dist)
				return (false);
		}
	}
	return (true);
}

void	sort_sprites(t_player *player, t_sprite ***sprites)
{
	int			ij[2];
	t_sprite	*tmp;
	float		dxy[2];

	ij[0] = -1;
	while ((*sprites)[++ij[0]])
	{
		dxy[0] = player->player_pos_xy[0] - (*sprites)[ij[0]]->sp_xy[0];
		dxy[1] = player->player_pos_xy[1] - (*sprites)[ij[0]]->sp_xy[1];
		(*sprites)[ij[0]]->dist = sqrtf(dxy[0] * dxy[0] + dxy[1] * dxy[1]);
	}
	while (!sprite_are_sorted((*sprites)))
	{
		ij[1] = -1;
		while (++ij[1] < ij[0] - 1)
		{
			if ((*sprites)[ij[1]]->dist < (*sprites)[ij[1] + 1]->dist)
			{
				tmp = (*sprites)[ij[1]];
				(*sprites)[ij[1]] = (*sprites)[ij[1] + 1];
				(*sprites)[ij[1] + 1] = tmp;
			}
		}
	}
}

void	draw_sprites(t_player *player, t_imgs *imgs, const float *dists)
{
	t_world	*world;
	int		chunk;
	int		s;

	chunk = -1;
	world = get_world_active();
	if (!world->sprites || !world->sprites[0])
		return ;
	player->cos = cosf(player->playerangle);
	player->sin = sinf(player->playerangle);
	while (++chunk < 9)
	{
		s = -1;
		sort_sprites(player, &world->sprites[chunk]);
		while (world->sprites[chunk][++s])
		{
			init_sprite_vars(world->sprites[chunk][s], player, world->sprites[chunk][s]->texture);
			if (world->sprites[chunk][s]->fog > 1 || world->sprites[chunk][s]->dist < 15)
				continue ;
			draw_sprite(world->sprites[chunk][s], imgs->img_3d, world->sprites[chunk][s]->texture, dists);
		}
	}
}
