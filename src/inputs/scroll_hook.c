#include "../../includes/includes.h"

static void	right_move(t_player *player, mlx_image_t *img)
{
	if (player->slot->slot_id >= 6)
		return ;
	img->instances->x += 80;
	player->slot = player->slot->next;
}

static void	left_move(t_player *player, mlx_image_t *img)
{
	if (player->slot->slot_id <= 1)
		return ;
	img->instances->x -= 80;
	player->slot = player->slot->prev;
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
