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

mlx_image_t *rotate_image(mlx_t *mlx, mlx_image_t *image, int img_width, int img_height, int angle)
{
	double angle_rad = angle * 3.14159265358979323846 / 180.0; // Conversion de l'angle en radians
	double cos_theta = cos(angle_rad);
	double sin_theta = sin(angle_rad);

	int new_width = fabs(img_width * cos_theta) + fabs(img_height * sin_theta);
	int new_height = fabs(img_width * sin_theta) + fabs(img_height * cos_theta);

	mlx_image_t *new_image = mlx_new_image(mlx, new_width, new_height);
	uint8_t *img_data = image->pixels;
	uint8_t *new_img_data = new_image->pixels;

	int x0 = img_width / 2; // Coordonnées du centre de l'image d'origine
	int y0 = img_height / 2;
	int x, y;

	for (y = 0; y < new_height; y++)
	{
		for (x = 0; x < new_width; x++)
		{
			int src_x = (x - new_width / 2) * cos_theta + (y - new_height / 2) * sin_theta + x0;
			int src_y = -(x - new_width / 2) * sin_theta + (y - new_height / 2) * cos_theta + y0;

			if (src_x >= 0 && src_x < img_width && src_y >= 0 && src_y < img_height)
			{
				int src_offset = (src_y * img_width + src_x) * 4;
				int dst_offset = (y * new_width + x) * 4;

				new_img_data[dst_offset] = img_data[src_offset];
				new_img_data[dst_offset + 1] = img_data[src_offset + 1];
				new_img_data[dst_offset + 2] = img_data[src_offset + 2];
				new_img_data[dst_offset + 3] = img_data[src_offset + 3];
			}
		}
	}
	return (new_image);
}
