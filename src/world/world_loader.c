/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagmur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:35:56 by ayagmur           #+#    #+#             */
/*   Updated: 2023/08/02 12:35:57 by ayagmur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	world_malloc(int height, int width, char ***map)
{
	int	i;

	i = 0;
	(*map) = malloc(sizeof(char *) * (height + 1));
	if (!*map)
		return (false);
	(*map)[height] = 0;
	while (i < height)
	{
		(*map)[i] = malloc(sizeof(char) * width + 1);
		if (!(*map)[i])
			return (false);
		(*map)[i][width] = 0;
		i++;
	}
	return (true);
}

static void	world_generator(t_world *world)
{
	int	i;

	i = -1;
	while (i++ < 8)
		chunk_generator(world, i);
}

static t_biome	**world_get_biomes(int biome_number, ...)
{
	t_biome	**biomes;
	va_list	va_biomes;

	va_start(va_biomes, biome_number);
	biomes = malloc(sizeof(t_biome *) * (biome_number + 1));
	biomes[biome_number] = 0;
	while (biome_number-- > 0)
		biomes[biome_number] = va_arg(va_biomes, t_biome *);
	va_end(va_biomes);
	return (biomes);
}

/* Create new World with specified properties
 * Before call this function, add the name of your
 * World in the Enum World
 *
 * @param world_name	The Enum value of your world
 * @param biomes		The biomes compositions of your world (optional)
 * @param ambient_sound	The ambient_sound of your world (optional)
 * @param height		The height of your world. Do not set too high value
 * @param width			The width of your world. Do not set too high value
 * @param bt_color		The color of ceil and floor if there is no image are define for them (optional)
 * @param ceil			The ceil image
 * @param floor			The floor image
 * @param difficulty	The difficulty of the world;
 * @param is_active		By default you have to set this boolean to false
 * @param skybox		Set the mode of ceil (skybox or default)
 * */

bool	world_creator(World world_name, t_biome **biomes, t_sounds *ambient_sound, int height, int width, const uint32_t bt_color[2], mlx_image_t *ceil, mlx_image_t *floor, Difficulty difficulty, bool is_active, bool skybox)
{
	int		i;
	t_world	world;

	i = 0;
	world_name = world_name;
	world.biome = biomes;
	world.ambiant_sound = ambient_sound;
	world.height = height;
	world.width = width;
	world.bt_color[0] = bt_color[0];
	world.bt_color[1] = bt_color[1];
	world.ceil = ceil;
	world.floor = floor;
	world.difficulty = difficulty;
	world.world = malloc(sizeof(char **) * 9);
	world.is_active = is_active;
	world.skybox = skybox;
	world.sprites = NULL;
	while (i < 9)
		world_malloc(height * 3, width * 3, &world.world[i++]);
	world_generator(&world);
	set_world(world, world_name);
	return (true);
}

void	world_loader(t_core *core)
{
	biome_loader();
	world_creator(WORLD_NETHER, world_get_biomes(3, get_biome(BIOME_DARK), get_biome(BIOME_DRAGON), get_biome(BIOME_RED)), get_sound(NETHER_AMBIANT_SOUND), 32, 32, (uint32_t []){0, 0}, core->imgs.skybox_nether, get_block_image(NETHERRACK), HARD, false, true);
	world_creator(WORLD_END, world_get_biomes(2, get_biome(BIOME_END), get_biome(BIOME_CHORUS)), get_sound(END_AMBIANT_SOUND), 32, 32, (uint32_t []){0, 0}, core->imgs.skybox_end, get_block_image(BLOCK_END_STONE), NORMAL, false, true);
	world_creator(WORLD_BACKROOM, world_get_biomes(1, get_biome(BIOME_BACKROOM)), get_sound(BACKROOM_AMBIANT_SOUND), 32, 32, (uint32_t []){0, 0}, core->imgs.backrooms_ceil, get_block_image(BACKROOM_FLOOR), HARD, false, false);
}
