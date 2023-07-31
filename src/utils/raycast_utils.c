
#include "../../includes/includes.h"

uint32_t	apply_fog(uint32_t color, float fog_strength)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	if (fog_strength > 1.0)
		fog_strength = 1.0;
	r = ((color >> 24) & 0xFF) * (1.0 - fog_strength);
	g = ((color >> 16) & 0xFF) * (1.0 - fog_strength);
	b = ((color >> 8) & 0xFF) * (1.0 - fog_strength);
	a = (color & 0xFF);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	get_color_wall_texture(mlx_texture_t *wall_texture, int r, t_col_drawing *tcd)
{
    int			value;

    value = ((r % 64) + ((int)tcd->current_step * (int)wall_texture->width)) * 4;
    if (value >= 16384)
        return ;
    tcd->color = get_rgb_color(wall_texture->pixels[value],wall_texture->pixels[value + 1]
            ,wall_texture->pixels[value + 2],wall_texture->pixels[value + 3]);
}

void	get_color_block_texture(mlx_image_t *wall_texture, t_dda *dda, t_col_drawing *tcd)
{
	int			value;
	int			r;

	if (dda->hit_hv == 1)
		r = (int)dda->r_xy[1];
	else
		r = (int)dda->r_xy[0];
	value = ((r % 64) + ((int)tcd->current_step * (int)wall_texture->width)) * 4;
	if (value >= 16384)
		return ;
	tcd->color = get_rgb_color(wall_texture->pixels[value],wall_texture->pixels[value + 1]
			,wall_texture->pixels[value + 2],wall_texture->pixels[value + 3]);
}

void	fisheyes_fixor(t_dda *dda, float player_angle)
{
	float two_pi;

	dda->current_angle_fix = player_angle - dda->current_angle;
	two_pi = 2 * PI;
	if (dda->current_angle_fix < 0)
        dda->current_angle_fix += two_pi;
	if (dda->current_angle_fix > two_pi)
        dda->current_angle_fix -= two_pi;
	dda->dist_hv[0] = dda->dist_hv[0] * cosf(dda->current_angle_fix);
}