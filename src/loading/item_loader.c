#include "../../includes/includes.h"

static void	put_two_string(char *dst, const char *s1, const char *s2, int num)
{
	int	i;

	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	if (num > 0)
		dst[i++] = num + '0';
	dst[i++] = '.';
	dst[i++] = 'p';
	dst[i++] = 'n';
	dst[i++] = 'g';
	dst[i] = '\0';
}

static void	create_item(t_item *item, mlx_t *mlx, Item item_name, int anim_size, double anim_speed)
{
	char *path;
	int	i;

	i = 0;
	item->name = item_name;
	path = malloc(sizeof(char) * (ft_strlen(ItemName[item_name]) + 18));
	put_two_string(path, "assets/items/", ItemName[item_name], 0);
	if (!set_image_from_path(mlx, path, &item->image))
		msg_write(2, 2, ERROR_FATAL);
	put_two_string(path, "assets/icons/", ItemName[item_name], 0);
	if (!set_image_from_path(mlx, path, &item->icon))
		msg_write(2, 2, ERROR_FATAL);
	free(path);
	path = malloc(sizeof(char) * (ft_strlen(ItemName[item_name]) + 19));
	mlx_image_to_window(mlx, item->image, SCREEN_WIDTH / 1.4, SCREEN_HEIGHT - item->image->height);
	mlx_image_to_window(mlx, item->icon, SCREEN_WIDTH / 3.05,SCREEN_HEIGHT - 80);
	item->image->instances[0].enabled = false;
	item->icon->instances[0].enabled = false;
	item->animation.is_playing = false;
	item->animation.speed = anim_speed;
	item->animation.image = malloc(sizeof(mlx_image_t) * (anim_size + 1));
	while (i++ < anim_size)
	{
		put_two_string(path, "assets/items/", ItemName[item_name], i);
		if (!set_image_from_path(mlx, path, &item->animation.image[i - 1]))
			msg_write(2, 2, ERROR_FATAL);
		mlx_image_to_window(mlx, item->animation.image[i - 1], SCREEN_WIDTH / 1.4, SCREEN_HEIGHT - 290);
		item->animation.image[i - 1]->instances[0].enabled = false;
		free(path);
		path = malloc(sizeof(char) * (ft_strlen(ItemName[item_name]) + 19));
	}
	item->animation.image[i - 1] = 0;
	free(path);
}

static void	create_item_stats(t_item *item, int dura, int damage, int strength, int range)
{
	item->durability = dura;
	item->damage = damage;
	item->strength = strength;
	item->range = range;
}

void	item_loader(t_core *core)
{
	create_item(&core->items[HAND], core->mlx, HAND, 4, -0.001);
	create_item_stats(&core->items[HAND], -1, 2, 10, 3);
	create_item(&core->items[SWORD_NETHER], core->mlx, SWORD_NETHER, 3, -0.01);
	create_item_stats(&core->items[SWORD_NETHER], 10, 5, 1, 3);
}