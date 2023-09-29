
#include "../../includes/includes.h"

void realloc_sprites(t_sprite ***sprites, int len)
{
	t_sprite	**new_tab;
	int			s;

	s = -1;
	new_tab = (t_sprite **)malloc(sizeof(t_sprite *) * (len + 2));
	while (++s < len)
		new_tab[s] = (*sprites)[s];
	new_tab[s] = (t_sprite *)malloc(sizeof(t_sprite));
	new_tab[s + 1] = NULL;
	if (*sprites)
	{
		free(*sprites);
		*sprites = NULL;
	}
	*sprites = new_tab;
}

static void	select_options(t_sprite *sp, char c)
{
	if (c == '>')
	{
		if (!set_texture_from_path("assets/sprites/pink_tulip.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 228;
	}
	else if (c == '<')
	{
		if (!set_texture_from_path("assets/sprites/poppy.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 228;
	}
	else if (c == 'v')
	{
		if (!set_texture_from_path("assets/sprites/brown_mushroom.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 196;
	}
	else if (c == '^')
	{
		if (!set_texture_from_path("assets/sprites/carrots_stage1.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 312 + get_rand_num(412, 2);
	}
	else if (c == '*')
	{
		if (!set_texture_from_path("assets/trash_do_not_remove/e_0.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = true;
		sp->scale = 576;
	}
	else if (c == ':')
	{
		if (!set_texture_from_path("assets/sprites/crimson_fungus.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 196;
	}
	else if (c == ';')
	{
		if (!set_texture_from_path("assets/sprites/fire_coral.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 312 + get_rand_num(412, 2);
	}
	else if (c == '?')
	{
		if (!set_texture_from_path("assets/sprites/warped_fungus.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 196;
	}
	else if (c == '/')
	{
		if (!set_texture_from_path("assets/sprites/wither_rose.png", &sp->texture))
			msg_write(2, 2, ERROR_FATAL);
		sp->hostile = false;
		sp->scale = 196;
	}
}

void	free_all_sprites(t_world *world)
{
	int	s;
	int	chunk;

	chunk = -1;
	while (++chunk < 9)
	{
		s = -1;
		if (!world->sprites[chunk])
			continue ;
		while (world->sprites[chunk][++s])
			free(world->sprites[chunk][s]);
		free(world->sprites[chunk]);
	}
}

//void	delete_sprite(t_sprite **sprites, int s)
//{
//	int	len;
//	int	i;
//
//	len = 0;
//	while (sprites && sprites[s])
//		len++;
//	if (!sprites || len < s)
//		return ;
//	free(sprites[s]);
//	i = s;
//	while (i++ < len)
//		sprites[s] = sprites[s + 1];
//	sprites = realloc_sprites(sprites, len - 1);
//}

void	reload_sprite_pos(t_world *world)
{
	int	chunk;
	int	s;

	chunk = -1;
	while (++chunk < 9)
	{
		s = -1;
		while (world->sprites[chunk][++s])
		{
			world->sprites[chunk][s]->cell_xy[0] = (int)(world->sprites
				[chunk][s]->x_origin + (world->width * (chunk % 3)));
			world->sprites[chunk][s]->cell_xy[1] = (int)(world->sprites
				[chunk][s]->y_origin + (world->height * (int)
						lround(((float)chunk - 1.f) / 3.f)));
			world->sprites[chunk][s]->sp_xy[0] = ((float)
					(world->sprites[chunk][s]->cell_xy[0]) + 0.5f) * 64;
			world->sprites[chunk][s]->sp_xy[1] = ((float)
					(world->sprites[chunk][s]->cell_xy[1]) + 0.5f) * 64;
			world->sprites[chunk][s]->chunk_sp_xy[0] = world->sprites
			[chunk][s]->sp_xy[0];
			world->sprites[chunk][s]->chunk_sp_xy[1] = world->sprites
			[chunk][s]->sp_xy[1];
		}
	}
}

void	move_multiple_sprites_bis(t_world *world, int dir)
{
	t_sprite	**chunk1;
	t_sprite	**chunk2;
	t_sprite	**chunk3;

	if (dir == 5)
	{
		chunk1 = world->sprites[0];
		chunk2 = world->sprites[3];
		chunk3 = world->sprites[6];
		world->sprites[0] = world->sprites[1];
		world->sprites[3] = world->sprites[4];
		world->sprites[6] = world->sprites[7];
		world->sprites[1] = world->sprites[2];
		world->sprites[4] = world->sprites[5];
		world->sprites[7] = world->sprites[8];
		world->sprites[2] = chunk1;
		world->sprites[5] = chunk2;
		world->sprites[8] = chunk3;
	}
	else if (dir == 7)
	{
		chunk1 = world->sprites[0];
		chunk2 = world->sprites[1];
		chunk3 = world->sprites[2];
		world->sprites[0] = world->sprites[3];
		world->sprites[1] = world->sprites[4];
		world->sprites[2] = world->sprites[5];
		world->sprites[3] = world->sprites[6];
		world->sprites[4] = world->sprites[7];
		world->sprites[5] = world->sprites[8];
		world->sprites[6] = chunk1;
		world->sprites[7] = chunk2;
		world->sprites[8] = chunk3;
	}
}

void	move_multiple_sprites(t_world *world, int dir)
{
	t_sprite	**chunk1;
	t_sprite	**chunk2;
	t_sprite	**chunk3;

	if (dir == 1)
	{
		chunk1 = world->sprites[6];
		chunk2 = world->sprites[7];
		chunk3 = world->sprites[8];
		world->sprites[6] = world->sprites[3];
		world->sprites[7] = world->sprites[4];
		world->sprites[8] = world->sprites[5];
		world->sprites[3] = world->sprites[0];
		world->sprites[4] = world->sprites[1];
		world->sprites[5] = world->sprites[2];
		world->sprites[0] = chunk1;
		world->sprites[1] = chunk2;
		world->sprites[2] = chunk3;
	}
	else if (dir == 3)
	{
		chunk1 = world->sprites[2];
		chunk2 = world->sprites[5];
		chunk3 = world->sprites[8];
		world->sprites[2] = world->sprites[1];
		world->sprites[5] = world->sprites[4];
		world->sprites[8] = world->sprites[7];
		world->sprites[1] = world->sprites[0];
		world->sprites[4] = world->sprites[3];
		world->sprites[7] = world->sprites[6];
		world->sprites[0] = chunk1;
		world->sprites[3] = chunk2;
		world->sprites[6] = chunk3;
	}
	else
		move_multiple_sprites_bis(world, dir);
}

char	get_rand_sprite_char(t_world *world)
{
	static const char	tab_default[] = {'>', '<', '^', 'v'};
	static const char	tab_nether[] = {':', ';', '?', '/'};

	if (world->world_name == WORLD_DEFAULT)
		return (tab_default[get_rand_num(4, 1)]);
	else
		return (tab_nether[get_rand_num(4, 1)]);
}

void	sprites_place(t_world *world, int chunk)
{
	move_multiple_sprites(world, chunk);
	reload_sprite_pos(world);
}

void	add_sprite(t_world *world, int chunk, char c, int y, int x)
{
	int	len;

	len = 0;
	while (world->sprites[chunk] != NULL && world->sprites[chunk][len])
		len++;
	if (world->sprites[chunk] == NULL)
	{
		world->sprites[chunk] = (t_sprite **)malloc(sizeof(t_sprite *) * 2);
		world->sprites[chunk][0] = (t_sprite *)malloc(sizeof(t_sprite));
		world->sprites[chunk][1] = NULL;
	}
	else
		realloc_sprites(&world->sprites[chunk], len);
	world->sprites[chunk][len]->c = c;
	world->sprites[chunk][len]->x_origin = x;
	world->sprites[chunk][len]->y_origin = y;
	world->sprites[chunk][len]->cell_xy[0] = (int)(world->sprites
		[chunk][len]->x_origin + (world->width * (chunk % 3)));
	world->sprites[chunk][len]->cell_xy[1] = (int)(world->sprites
		[chunk][len]->y_origin + (world->height
				* lround(((float)chunk - 1.f) / 3.f)));
	world->sprites[chunk][len]->sp_xy[0] = ((float)
			(world->sprites[chunk][len]->cell_xy[0]) + ((get_rand_num(9, 1) / 10) + 0.2f)) * 64;
	world->sprites[chunk][len]->sp_xy[1] = ((float)
			(world->sprites[chunk][len]->cell_xy[1]) + ((get_rand_num(9, 1) / 10) + 0.2f)) * 64;
	world->sprites[chunk][len]->chunk_sp_xy[0] = world->sprites[chunk][len]->sp_xy[0];
	world->sprites[chunk][len]->chunk_sp_xy[1] = world->sprites[chunk][len]->sp_xy[1];
	select_options(world->sprites[chunk][len], c);
}
