
#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"


static uint32_t	get_color_from_wall_texture(mlx_texture_t *wall_texture, const int texture_xy[2])
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

static uint32_t	apply_fog(float fog_strength)
{
	static uint32_t	black = ((0 << 24) | (0 << 16) | (0 << 8) | 255);

	if (fog_strength > 1.0)
		fog_strength = 1.0;
	if (fog_strength == 1.0)
		return (black);
	return (0);
}

uint32_t	get_color(mlx_texture_t *wall_texture, float fog_strength, int texture_xy[2])
{
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;

	color = apply_fog(fog_strength);
	if (color != 0)
		return (color);
	color = get_color_from_wall_texture(wall_texture, texture_xy);
	r = ((color >> 24) & 0xFF) * (1.0 - fog_strength);
	g = ((color >> 16) & 0xFF) * (1.0 - fog_strength);
	b = ((color >> 8) & 0xFF) * (1.0 - fog_strength);
	return ((r << 24) | (g << 16) | (b << 8) | (color & 0xFF));
}

void	draw_energy_bar(mlx_image_t *img, short energy)
{
	t_t_i		ti;
	uint32_t	full_color;
	uint32_t	empty_color;

	init_tti_struct(&ti, ((energy * 4.3)), 3, 2);
	full_color = get_rgb_color(192, 19, 186, 255);
	empty_color = get_rgb_color(100, 80, 190, 255);
	while (ti.c != 10)
	{
		if (ti.c == 9 || ti.c == 2)
		{
			ti.b++;
			ti.a -= 2;
		}
		draw_pixel_to_img(img, ti, full_color);
		if (energy < 100)
		{
			if (ti.c == 9 || ti.c == 2)
				ti.a += 4;
			ti.a -= 100 * 4.3;
			ti.a = abs(ti.a);
			ti.b += energy * 4.3;
			draw_pixel_to_img(img, ti, empty_color);
		}
		ti.b = 3;
		ti.c++;
		ti.a = energy * 4.3;
	}
}
