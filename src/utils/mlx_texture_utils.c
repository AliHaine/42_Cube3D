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