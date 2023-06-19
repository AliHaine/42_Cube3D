#include "../../includes/includes.h"

static void	item_loader(mlx_t *mlx, t_imgs *imgs)
{
	if (!set_image_from_path(mlx, "assets/icons/icon_sword_nether.png", &imgs->icon_sword_nether))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/sword_nether1.png", &imgs->sword_nether[0]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/sword_nether2.png", &imgs->sword_nether[1]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/sword_nether3.png", &imgs->sword_nether[2]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/sword_nether4.png", &imgs->sword_nether[3]))
		msg_write(2, 2, ERROR_FATAL);
	imgs->sword_nether[4] = 0;

	if (!set_image_from_path(mlx, "assets/items/hand1.png", &imgs->hand[0]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand2.png", &imgs->hand[1]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand3.png", &imgs->hand[2]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand4.png", &imgs->hand[3]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand5.png", &imgs->hand[4]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand6.png", &imgs->hand[5]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand7.png", &imgs->hand[6]))
		msg_write(2, 2, ERROR_FATAL);
	if (!set_image_from_path(mlx, "assets/items/hand8.png", &imgs->hand[7]))
		msg_write(2, 2, ERROR_FATAL);
	imgs->hand[8] = 0;
}

void	texture_loader(mlx_t *mlx, t_imgs *imgs)
{
	item_loader(mlx, imgs);
}
