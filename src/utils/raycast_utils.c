
#include "../../includes/includes.h"

void	get_color_from_wall_texture(mlx_texture_t *wall_texture, int r, t_col_drawing *twd)
{
    int			value;

    value = ((r % 64) + ((int)twd->current_step * (int)wall_texture->width)) * 4;
    if (value >= 16384)
        return ;
    twd->color = get_rgb_color(wall_texture->pixels[value],wall_texture->pixels[value + 1]
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
	dda->dist_hv[0] = dda->dist_hv[0] * cos(dda->current_angle_fix);
}