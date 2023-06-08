
#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

uint32_t	get_color_from_wall_texture(mlx_texture_t *wall_texture, const int texture_xy[2])
{
	static unsigned int			bx = 0;
	static unsigned int			by = 0;
	unsigned int				total;
	static unsigned int			scale;
	uint32_t					color;

	scale = wall_texture->width / 64;
	bx = (texture_xy[0] * scale) % wall_texture->width;
	by = (texture_xy[1] * scale) % wall_texture->height;
	total = (bx + by * wall_texture->width) * 4;
	color = (wall_texture->pixels[total] << 24)
		+ (wall_texture->pixels[total + 1] << 16)
		+ (wall_texture->pixels[total + 2] << 8)
		+ (wall_texture->pixels[total + 3]);
	return (color);
}