
#include "../../includes/includes.h"

static void	init_vars(t_sprite *sp, t_player *player, mlx_image_t *img)
{
	sp->dist = sqrtf(powf(player->player_pos_xy[0] - sp->sp_xy[0], 2)
			+ powf(player->player_pos_xy[1] - sp->sp_xy[1], 2));
	sp->s_pos[2] = SCREEN_HEIGHT / 2;
	sp->s_pos[0] = (sp->sp_xy[0] - player->player_pos_xy[0]);
	sp->s_pos[1] = (sp->sp_xy[1] - player->player_pos_xy[1]);
	sp->tmp[0] = sp->s_pos[1] * -player->cos + sp->s_pos[0] * player->sin;
	sp->tmp[1] = sp->s_pos[0] * player->cos + sp->s_pos[1] * player->sin;
	sp->s_pos[0] = sp->tmp[0];
	sp->s_pos[1] = sp->tmp[1];
	sp->s_pos[0] = (sp->s_pos[0] * -1280 / sp->s_pos[1]) + (SCREEN_WIDTH / 2);
	sp->s_pos[1] = (sp->s_pos[2] * 70 / sp->s_pos[1]) + (SCREEN_HEIGHT / 2);
	sp->size[0] = img->width * sp->scale / sp->tmp[1];
	sp->size[1] = img->height * sp->scale / sp->tmp[1];
	if (sp->size[0] < 0)
		sp->size[0] = 0;
	if (sp->size[1] < 0)
		sp->size[1] = 0;
	sp->t_pos[0] = img->width;
	sp->offset[0] = img->width / (float)sp->size[0];
	sp->offset[1] = img->height / (float)sp->size[1];
	sp->x = 0;
}

static void	draw_sp_pixel(t_sprite *sp, mlx_image_t *img_3d, mlx_image_t *img, const float *dists)
{
	uint32_t	color;
	int			value;

	color = 0;
	value = ((int)sp->t_pos[1] * (int)img->width
			- (int)sp->t_pos[0]) * 4;
	if (value > 0 && value < ((img->height * img->width) * 4) - 4)
		color = (img->pixels[value] << 24) | (img->pixels[value + 1]
				<< 16) | (img->pixels[value + 2] << 8) | img->pixels[value + 3];
	if (color != 0 && dists[sp->sc_xy[0]] > sp->dist)
		mlx_put_pixel(img_3d, sp->sc_xy[0], sp->sc_xy[1], color);
}

static void	draw_sprite(t_sprite *sp, mlx_image_t *img_3d, mlx_image_t *img, const float *dists)
{
	while (sp->x++ < sp->size[0])
	{
		sp->sc_xy[0] = (sp->s_pos[0] - sp->x) + (sp->size[0] / 2);
		sp->t_pos[1] = img->height;
		sp->y = 0;
		while (sp->y++ < sp->size[1] && ((int)sp->t_pos[1] * img->width
				- (int)sp->t_pos[0] >= 0))
		{
			sp->sc_xy[1] = (sp->s_pos[1] - sp->y);
			if (sp->sc_xy[0] < SCREEN_WIDTH && sp->sc_xy[1] < SCREEN_HEIGHT
				&& sp->sc_xy[0] >= 0 && sp->sc_xy[1] >= 0)
			{
				draw_sp_pixel(sp, img_3d, img, dists);
			}
			sp->t_pos[1] -= sp->offset[1];
		}
		sp->t_pos[0] -= sp->offset[0];
	}
}

void	enemy_attack_move(t_sprite *sp, t_player *player)
{
	const t_world	*world = get_world_active();
	const float		step = 2.f;

	if ((int)sp->sp_xy[0] > (int)player->player_pos_xy[0] && (world->world[get_chunk_from_pos((int)(sp->sp_xy[0] - step) / 64, (int)sp->sp_xy[1] / 64)][(int)(sp->sp_xy[1] / 64) % world->height][(int)((sp->sp_xy[0] - step) / 64) % world->width] == '0'))
		sp->sp_xy[0] -= step;
	else if ((int)sp->sp_xy[0] < (int)player->player_pos_xy[0] && (world->world[get_chunk_from_pos((int)(sp->sp_xy[0] / 64 + step), (int)sp->sp_xy[1] / 64)][(int)(sp->sp_xy[1] / 64) % world->height][(int)((sp->sp_xy[0] + step) / 64) % world->width] == '0'))
		sp->sp_xy[0] += step;
	if ((int)sp->sp_xy[1] > (int)player->player_pos_xy[1] && (world->world[get_chunk_from_pos((int)sp->sp_xy[0] / 64, (int)(sp->sp_xy[1] - step) / 64)][(int)((sp->sp_xy[1] - step) / 64) % world->height][(int)(sp->sp_xy[0] / 64) % world->width] == '0'))
		sp->sp_xy[1] -= step;
	else if ((int)sp->sp_xy[1] < (int)player->player_pos_xy[1] && (world->world[get_chunk_from_pos((int)sp->sp_xy[0] / 64, (int)(sp->sp_xy[1] + step) / 64)][(int)((sp->sp_xy[1] + step) / 64) % world->height][(int)(sp->sp_xy[0] / 64) % world->width] == '0'))
		sp->sp_xy[1] += step;
}

void	draw_sprites(t_player *player, t_sprite **sprites, t_imgs *imgs, const float *dists)
{
	int		s;

	s = -1;
	player->cos = cosf(player->playerangle);
	player->sin = sinf(player->playerangle);
	while (sprites[++s])
	{
		init_vars(sprites[s], player, imgs->monster);
		draw_sprite(sprites[s], imgs->img_3d, imgs->monster, dists);
		enemy_attack_move(sprites[s], player);
	}
}
