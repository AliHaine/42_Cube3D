
#include "../../includes/includes.h"

mlx_texture_t	*get_sprite_texture(t_imgs *imgs, t_sprite *sprite, t_world *world)
{
	mlx_texture_t	*texture;
	char			c;

	c = world->world[get_chunk_from_pos(sprite->c_xy[0], sprite->c_xy[1])]
	[sprite->c_xy[1] % world->height][sprite->c_xy[0] % world->width];
	if (c == '1')
		texture = imgs->wall_texture[0];
	else
		texture = NULL;
	return (texture);
}

void	init_sprite_vars(t_sprite *sprite, t_player *player)
{

}

void	sprites_drawing(t_imgs *imgs, t_sprite *sprites, t_player *player)
{
//	int			s;
//	int			value;
//	uint32_t	color;
//	int			texture_size = 8; //temporaire
//	int			scale = 1; // temporaire
//	int			boundSize = texture_size*1.5;
//
//	s = 0;
//	while (s++ < 1)
//	{
//		float scaleWidth = texture_size * scale;
//		float scaleHeight = texture_size * scale;
//
//		for (int i = -boundSize / 2; i < boundSize/2; i++)
//		{
//			for (int j = -boundSize / 2; j < boundSize / 2; j++)
//			{
//				int texX = (int)round((i * cosf(player->playerangle - j * sinf(player->playerangle))) / scale + texture_size/2.0-0.5);
//				int texY = (int)round((i * sinf(player->playerangle + j * cosf(player->playerangle)) / scale + texture_size/2.0-0.5));
//				int pixX = (int)((sprites[0].r_xy[0] + i) + cosf(player->playerangle)) % SCREEN_WIDTH;
//				int pixY = (int)((sprites[0].r_xy[1] + j) - sinf(player->playerangle)) % SCREEN_HEIGHT;
//				printf("%d %d\n", pixX, pixY);
//				if (pixX < 0 || pixY < 0 || pixX > SCREEN_WIDTH || pixY > SCREEN_HEIGHT)
//					continue ;
//				color = get_rgb_color(255, 0, 0, 255);
//				mlx_put_pixel(imgs->img_3d, pixX, pixY, color);
//			}
//		}
//	}
}
