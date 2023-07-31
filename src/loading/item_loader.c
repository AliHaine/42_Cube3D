/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:13 by ayagmur           #+#    #+#             */
/*   Updated: 2023/07/31 17:17:14 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	create_item(t_item *item, mlx_t *mlx, Item item_name)
{
	char	*path;

	item->name = item_name;
	item->animation.image = 0;
	path = malloc(sizeof(char) * (ft_strlen(ItemName[item_name]) + 18));
	printf("ici\n");
	put_two_string(path, "assets/items/", ItemName[item_name], 0);
	printf("ici\n");
	if (!set_image_from_path(mlx, path, &item->image))
		msg_write(2, 2, ERROR_FATAL);
	put_two_string(path, "assets/icons/", ItemName[item_name], 0);
	if (!set_image_from_path(mlx, path, &item->icon))
		msg_write(2, 2, ERROR_FATAL);
	free(path);
	mlx_resize_image(item->icon, 40, 40);
	mlx_image_to_window(mlx, item->image, SCREEN_WIDTH / 1.37, SCREEN_HEIGHT - item->image->height);
	item->instance_number = 0;
	item->image->instances[0].enabled = false;
	item->image->instances[0].z = 8;
}

static void	create_item_stats(t_item *item, int dura, int damage, int strength, int range)
{
	item->durability = dura;
	item->damage = damage;
	item->strength = strength;
	item->range = range;
}

static void create_item_animation(t_item *item, int anim_size, int x_depth, int y_depth, mlx_t *mlx)
{
	int i;
	char *path;

	i = 0;
	item->animation.is_playing = false;
	item->animation.depth_xy[0] = x_depth;
	item->animation.depth_xy[1] = y_depth;
	item->animation.image = malloc(sizeof(mlx_image_t) * (anim_size + 1));
	path = malloc(sizeof(char) * (ft_strlen(ItemName[item->name]) + 19));
	while (i++ < anim_size)
	{
		put_two_string(path, "assets/items/", ItemName[item->name], ft_itoa(i));
		if (!set_image_from_path(mlx, path, &item->animation.image[i - 1]))
		{
			free(path);
			msg_write(2, 2, ERROR_FATAL);
		}
		mlx_image_to_window(mlx, item->animation.image[i - 1], SCREEN_WIDTH / 1.4, SCREEN_HEIGHT - 290);
		item->animation.image[i - 1]->instances[0].enabled = false;
		item->animation.image[i - 1]->instances[0].z = 8;
		free(path);
		path = malloc(sizeof(char) * (ft_strlen(ItemName[item->name]) + 19));
	}
	free(path);
	item->animation.image[i - 1] = 0;
}

void	item_loader(t_core *core)
{
	create_item(&core->items[HAND], core->mlx, HAND);
	create_item_stats(&core->items[HAND], -1, 2, 10, 3);
	create_item_animation(&core->items[HAND], 4, 150, 0, core->mlx);

	create_item(&core->items[SWORD_NETHER], core->mlx, SWORD_NETHER);
	create_item_stats(&core->items[SWORD_NETHER], 10, 5, 1, 3);
	create_item_animation(&core->items[SWORD_NETHER], 3, 150, 0, core->mlx);

	create_item(&core->items[SWORD_DIAMOND], core->mlx, SWORD_DIAMOND);
    create_item_stats(&core->items[SWORD_DIAMOND], 10, 5, 1, 3);
	create_item_animation(&core->items[SWORD_DIAMOND], 5, 150, 0, core->mlx);


	create_item(&core->items[SWORD_RUBY], core->mlx, SWORD_RUBY);
    create_item_stats(&core->items[SWORD_RUBY], 10, 5, 1, 3);
	create_item_animation(&core->items[SWORD_RUBY], 5, 150, 0, core->mlx);

	create_item(&core->items[SWORD_IRON], core->mlx, SWORD_IRON);
	create_item_stats(&core->items[SWORD_IRON], 10, 5, 1, 3);
	create_item_animation(&core->items[SWORD_IRON], 4, 150, 0, core->mlx);

	create_item(&core->items[STICK], core->mlx, STICK);
	create_item_stats(&core->items[STICK], -1, 5, 1, 3);
	create_item_animation(&core->items[STICK], 6, 0, -50, core->mlx);

	create_item(&core->items[DIAMOND], core->mlx, DIAMOND);
	create_item_stats(&core->items[DIAMOND], -1, 5, 1, 3);
}
