#include "../../includes/includes.h"

static void	right_move(t_player *player, mlx_image_t *img)
{
	if (player->toolbar_slot >= 5)
		return ;
	img->instances->x += 80;
	player->toolbar_slot++;
}

static void	left_move(t_player *player, mlx_image_t *img)
{
	if (player->toolbar_slot <= 0)
		return ;
	img->instances->x -= 80;
	player->toolbar_slot--;
}

void	scroll_hook(double x, double y, void *param)
{
	(void)x;
	t_core	*core;

	core = param;
	if (y > 0)
		right_move(&core->player, core->imgs.invbar_selector);
	else
		left_move(&core->player, core->imgs.invbar_selector);
}
