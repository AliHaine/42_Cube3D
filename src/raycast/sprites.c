
#include "../../includes/includes.h"

static void	init_vars(t_sprite *sp, t_player *player, mlx_image_t *img)
{
	const float	dx = player->player_pos_xy[0] - sp->sp_xy[0];
	const float	dy = player->player_pos_xy[1] - sp->sp_xy[1];

	sp->dist = sqrtf(dx * dx + dy * dy);
	sp->fog = sp->dist / FOG_DISTANCE;
	if (sp->fog > 1)
		return ;
	sp->s_pos[2] = SCREEN_HEIGHT / 2.f;
	sp->s_pos[0] = (sp->sp_xy[0] - player->player_pos_xy[0]);
	sp->s_pos[1] = (sp->sp_xy[1] - player->player_pos_xy[1]);
	sp->tmp[0] = sp->s_pos[1] * -player->cos + sp->s_pos[0] * player->sin;
	sp->tmp[1] = sp->s_pos[0] * player->cos + sp->s_pos[1] * player->sin;
	sp->s_pos[0] = sp->tmp[0];
	sp->s_pos[1] = sp->tmp[1];
	sp->s_pos[0] = (sp->s_pos[0] * -1280 / sp->s_pos[1]) + (SCREEN_WIDTH / 2.f);
	sp->s_pos[1] = (sp->s_pos[2] * 70 / sp->s_pos[1]) + (SCREEN_HEIGHT / 2.f);
	sp->size[0] = (int)((float)(img->width * sp->scale) / sp->tmp[1]);
	sp->size[1] = (int)((float)(img->height * sp->scale) / sp->tmp[1]);
	if (sp->size[0] < 0)
		sp->size[0] = 0;
	if (sp->size[1] < 0)
		sp->size[1] = 0;
	sp->t_pos[0] = (float)img->width;
	sp->offset[0] = (float)img->width / (float)sp->size[0];
	sp->offset[1] = (float)img->height / (float)sp->size[1];
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
	{
		color = apply_fog(color, sp->fog);
		mlx_put_pixel(img_3d, sp->sc_xy[0], sp->sc_xy[1], color);
	}
}

static void	draw_sprite(t_sprite *sp, mlx_image_t *img_3d, mlx_image_t *img, const float *dists)
{
	while (sp->x++ < sp->size[0])
	{
		sp->sc_xy[0] = (int)(sp->s_pos[0] - (float)sp->x) + (sp->size[0] / 2);
		if (sp->sc_xy[0] >= SCREEN_WIDTH || sp->sc_xy[0] < 0)
		{
			sp->t_pos[0] -= sp->offset[0];
			continue ;
		}
		sp->t_pos[1] = (float)img->height;
		sp->y = 0;
		while (sp->y++ < sp->size[1] && ((int)sp->t_pos[1] * img->width
				- (int)sp->t_pos[0] >= 0))
		{
			sp->sc_xy[1] = (int)(sp->s_pos[1] - (float)sp->y);
			if (sp->sc_xy[1] >= 0 && sp->sc_xy[1] < SCREEN_HEIGHT)
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
	t_world			*world;
	float			step;
	float			angle;
	float			dx;
	float			dy;

	if (sp->dist < 50 || sp->dist > 1000)
		return ;
	step = 5.f;
	world = get_world_active();
	angle = atan2f(player->player_pos_xy[1]
			- sp->sp_xy[1], player->player_pos_xy[0] - sp->sp_xy[0]);
	dx = cosf(angle) * step;
	dy = sinf(angle) * step;
	if (world->world[get_chunk_from_pos((int)(sp->sp_xy[0] + dx) / 64,
			(int)sp->sp_xy[1] / 64)][(int)(sp->sp_xy[1] / 64) % world->height]
			[(int)((sp->sp_xy[0] + dx) / 64) % world->width] == '0')
		sp->sp_xy[0] += dx;
	if (world->world[get_chunk_from_pos((int)sp->sp_xy[0] / 64,
				(int)(sp->sp_xy[1] + dy) / 64)][(int)((sp->sp_xy[1] + dy) / 64)
			% world->height][(int)(sp->sp_xy[0] / 64) % world->width] == '0')
		sp->sp_xy[1] += dy;
}

void	draw_sprites(t_player *player, t_imgs *imgs, const float *dists)
{
	t_world	*world;
	int		s;

	s = -1;
	world = get_world_active();
	if (!world->sprites)
		return ;
	player->cos = cosf(player->playerangle);
	player->sin = sinf(player->playerangle);
	while (world->sprites[++s])
	{
		init_vars(world->sprites[s], player, imgs->monster);
		if (world->sprites[s]->fog > 1 || world->sprites[s]->dist < 15)
			continue ;
		draw_sprite(world->sprites[s], imgs->img_3d, imgs->monster, dists);
		if (world->sprites[s]->hostile)
			enemy_attack_move(world->sprites[s], player);
	}
}
