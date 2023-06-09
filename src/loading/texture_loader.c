#include "../../includes/includes.h"

static void	other_loader(mlx_t *mlx, t_imgs *imgs)
{
	if (!set_texture_from_path("assets/trans.png", &imgs->trans))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/e_0.png", &imgs->enemy))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/invbar.png", &imgs->invbar))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/engbar.png", &imgs->engbar))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/door.png", &imgs->door_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/grass.png", &imgs->grass_texture))
		msg_write(2, 2, ERROR_FATAL);
    if (!set_texture_from_path("assets/inventory_gui2.png", &imgs->inventory_gui_texture))
        msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/cursor.png", &imgs->cursor))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/map_background.png", &imgs->map_texture))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_texture_from_path("assets/player_dot.png", &imgs->img_player_texture))
		msg_write(2, 2, ERROR_FATAL);
}

static void	icon_loader(mlx_t *mlx, t_imgs *imgs)
{
	if (!set_image_from_path(mlx, "assets/icons/crosshair.png", &imgs->crosshair))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/icons/invbar_selector.png", &imgs->invbar_selector))
		msg_write(2, 2, ERROR_FATAL);
	mlx_resize_image(imgs->invbar_selector, imgs->invbar_selector->width / 1.5,
		imgs->invbar_selector->height / 1.5);
	if (!set_image_from_path(mlx, "assets/icons/hearth_full.png", &imgs->hearth[1]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/icons/hearth_empty.png", &imgs->hearth[0]))
		msg_write(2, 2, ERROR_FATAL);
}

void	texture_loader(t_core *core)
{
	icon_loader(core->mlx, &core->imgs);
	other_loader(core->mlx, &core->imgs);
}
