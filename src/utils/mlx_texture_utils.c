#include "../../includes/includes.h"

bool	set_texture_from_path(char *path, mlx_texture_t **texture)
{
	msg_write_multiple(1, Messages[TRY_LOAD_TEXTURE], path);
	if (path[ft_strlen(path) - 1] == '\n') {
		path[ft_strlen(path) - 1] = '\0';
		*texture = mlx_load_png(path);
	}
	else
		*texture = mlx_load_png(path);
	if (!*texture)
		return (false);
	return (true);
}

bool	set_image_from_path(mlx_t *mlx, char *path, mlx_image_t **image)
{
	mlx_texture_t *texture;

	if (!set_texture_from_path(path, &texture))
		return (false);
	*image = mlx_texture_to_image(mlx, texture);
	return (true);
}

void	delete_image_from_struct(mlx_t *mlx, t_imgs *imgs)
{
	mlx_delete_image(mlx, imgs->img_3d);
	mlx_delete_image(mlx, imgs->img_player);
	mlx_delete_image(mlx, imgs->img_map);
	mlx_delete_image(mlx, imgs->crosshair);
}

uint32_t	get_rgb_color(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
	return ((r << 24) | (g << 16) | (b  << 8) | a);
}

uint32_t	get_pixel(mlx_texture_t *texture, int x, int y)
{
	uint32_t					color;
	int							step;

	step = (x + y * texture->width) * 4;
	color = (texture->pixels[step] << 24)
			+ (texture->pixels[step + 1] << 16)
			+ (texture->pixels[step + 2] << 8)
			+ (texture->pixels[step + 3]);
	return (color);
}

static void	rotate_util(mlx_image_t *img, mlx_texture_t *txt, int src_xy[2], int xy[2])
{
	int	dst_offset;
	int	src_offset;

	if (src_xy[0] >= 0 && src_xy[0] < txt->width
		&& src_xy[1] >= 0 && src_xy[1] < txt->height)
	{
		dst_offset = (src_xy[1] * (int)txt->width + src_xy[0]) * 4;
		src_offset = (xy[1] * (int)txt->width + xy[0]) * 4;
		img->pixels[dst_offset] = txt->pixels[src_offset];
		img->pixels[dst_offset + 1] = txt->pixels[src_offset + 1];
		img->pixels[dst_offset + 2] = txt->pixels[src_offset + 2];
		img->pixels[dst_offset + 3] = txt->pixels[src_offset + 3];
	}
}

mlx_image_t	*rotate_image(mlx_t *mlx, mlx_texture_t *texture, float angle)
{
	const float	cost = cosf(angle);
	const float	sint = sinf(angle);
	mlx_image_t	*new_img;
	int			xy[2];
	int			src_xy[2];

	new_img = mlx_new_image(mlx, (int)texture->width, (int)texture->height);
	xy[1] = -1;
	while (++xy[1] < (int)texture->height)
	{
		xy[0] = -1;
		while (++xy[0] < (int)texture->width)
		{
			src_xy[0] = (int)(((float)xy[0] - (float)texture->width / 2)
					* cost - ((float)xy[1] - (float)texture->height / 2)
					* sint + ((float)texture->width / 2));
			src_xy[1] = (int)(((float)xy[0] - (float)texture->width / 2)
					* sint + ((float)xy[1] - (float)texture->height / 2)
					* cost + ((float)texture->height / 2));
			if (src_xy[0] >= 0 && src_xy[0] < texture->width
				&& src_xy[1] >= 0 && src_xy[1] < texture->height)
				rotate_util(new_img, texture, src_xy, xy);
		}
	}
	return (new_img);
}
