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

static void	create_item(Item item_name, mlx_t *mlx)
{
	char	*path;
	t_item	*item;

	msg_write_multiple(1, g_messages[TRY_LOAD_ITEM], g_item_name[item_name]);
	item = malloc(sizeof(t_item));
	item->name = item_name;
	item->animation.image = 0;
	path = malloc(sizeof(char) * (ft_strlen(g_item_name[item_name]) + 18));
	put_two_string(path, "assets/items/", g_item_name[item_name], 0);
	if (!set_image_from_path(mlx, path, &item->image))
		msg_write(2, 2, ERROR_FATAL);
	put_two_string(path, "assets/icons/", g_item_name[item_name], 0);
	if (!set_image_from_path(mlx, path, &item->icon))
		msg_write(2, 2, ERROR_FATAL);
	free(path);
	mlx_resize_image(item->icon, 40, 40);
	mlx_image_to_window(mlx, item->image, SCREEN_WIDTH / 1.37, SCREEN_HEIGHT - item->image->height);
	item->instance_number = 0;
	item->image->instances[0].enabled = false;
	item->image->instances[0].z = 8;
	set_item(item);
}

static void	create_item_stats(t_item *item, int dura, int damage, int strength)
{
	item->durability = dura;
	item->damage = damage;
	item->strength = strength;
}

static void	create_item_animation(t_item *item, int anim_size, int x_depth, int y_depth, mlx_t *mlx)
{
	int		i;
	char	*path;

	i = 0;
	item->animation.is_playing = false;
	item->animation.depth_xy[0] = x_depth;
	item->animation.depth_xy[1] = y_depth;
	item->animation.image = malloc(sizeof(mlx_image_t) * (anim_size + 1));
	path = malloc(sizeof(char) * (ft_strlen(g_item_name[item->name]) + 19));
	while (i++ < anim_size)
	{
		put_two_string(path, "assets/items/", g_item_name[item->name], ft_itoa(i));
		if (!set_image_from_path(mlx, path, &item->animation.image[i - 1]))
		{
			free(path);
			msg_write(2, 2, ERROR_FATAL);
		}
		mlx_image_to_window(mlx, item->animation.image[i - 1], SCREEN_WIDTH / 1.4, SCREEN_HEIGHT - 290);
		item->animation.image[i - 1]->instances[0].enabled = false;
		item->animation.image[i - 1]->instances[0].z = 8;
		free(path);
		path = malloc(sizeof(char) * (ft_strlen(g_item_name[item->name]) + 19));
	}
	free(path);
	item->animation.image[i - 1] = 0;
}

void	item_loader(t_core *core)
{
	create_item(HAND, core->mlx);
	create_item_stats(get_item(HAND), -1, 2, 3);
	create_item_animation(get_item(HAND), 4, 150, 0, core->mlx);
	create_item(SWORD_NETHER, core->mlx);
	create_item_stats(get_item(SWORD_NETHER), 10, 5, 1);
	create_item_animation(get_item(SWORD_NETHER), 3, 150, 0, core->mlx);
	create_item(SWORD_DIAMOND, core->mlx);
	create_item_stats(get_item(SWORD_DIAMOND), 10, 5, 1);
	create_item_animation(get_item(SWORD_DIAMOND), 5, 150, 0, core->mlx);
	create_item(SWORD_RUBY, core->mlx);
	create_item_stats(get_item(SWORD_RUBY), 10, 5, 1);
	create_item_animation(get_item(SWORD_RUBY), 5, 150, 0, core->mlx);
	create_item(SWORD_IRON, core->mlx);
	create_item_stats(get_item(SWORD_IRON), 10, 5, 1);
	create_item_animation(get_item(SWORD_IRON), 4, 150, 0, core->mlx);
	create_item(STICK, core->mlx);
	create_item_stats(get_item(STICK), -1, 2, 2);
	create_item_animation(get_item(STICK), 6, 0, -50, core->mlx);
	create_item(DIAMOND, core->mlx);
	create_item_stats(get_item(DIAMOND), -1, 2, 2);
	create_item(IRON, core->mlx);
	create_item_stats(get_item(IRON), -1, 2, 2);
	create_item_animation(get_item(IRON), 4, 0, -50, core->mlx);
	create_item(FLINT, core->mlx);
	create_item_stats(get_item(FLINT), -1, 2, 2);
	create_item_animation(get_item(FLINT), 4, 0, -50, core->mlx);
	create_item(LIGHTER, core->mlx);
	create_item_stats(get_item(LIGHTER), 10, 2, 2);
	create_item_animation(get_item(LIGHTER), 3, 0, 150, core->mlx);
	create_item(DIAMOND_PICKAXE, core->mlx);
	create_item_stats(get_item(DIAMOND_PICKAXE), 10, 2, 5);
	create_item_animation(get_item(DIAMOND_PICKAXE), 4, 0, 150, core->mlx);
	create_item(WATER_BUCKET, core->mlx);
	create_item_stats(get_item(WATER_BUCKET), -1, 2, 1);
	create_item_animation(get_item(WATER_BUCKET), 3, 0, 150, core->mlx);
}
