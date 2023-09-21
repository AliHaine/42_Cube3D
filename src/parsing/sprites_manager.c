
#include "../../includes/includes.h"

t_sprite	**realloc_sprites(t_sprite **sprites, int len)
{
	t_sprite	**new_tab;
	int			s;

	s = -1;
	new_tab = (t_sprite **)malloc(sizeof(t_sprite *) * (len + 2));
	while (++s < len)
		new_tab[s] = sprites[s];
	new_tab[s] = (t_sprite *)malloc(sizeof(t_sprite));
	new_tab[s + 1] = NULL;
	if (sprites)
		free(sprites);
	return (new_tab);
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
}

void	free_all_sprites(t_sprite ***sprites)
{
	int	s;

	s = 0;
	if (!*sprites)
		return ;
	while (*sprites[s])
	{
		free(*sprites[s]);
		*sprites[s] = NULL;
	}
	free(*sprites[s]);
	free(*sprites);
}

void	delete_sprite(t_sprite **sprites, int s)
{
	int	len;
	int	i;

	len = 0;
	while (sprites && sprites[s])
		len++;
	if (!sprites || len < s)
		return ;
	free(sprites[s]);
	i = s;
	while (i++ < len)
		sprites[s] = sprites[s + 1];
	sprites = realloc_sprites(sprites, len - 1);
}

t_sprite	*get_sprite_by_int(t_sprite **sprites, int x, int y)
{
	int	s;

	s = 0;
	if (!sprites || !sprites[0])
		return (NULL);
	while (sprites[s])
	{
		if ((int)(sprites[s]->sp_xy[0] / 64) == x
		&& (int)(sprites[s]->sp_xy[1] / 64) == y)
			return (sprites[s]);
	}
	return (NULL);
}

void	add_sprite(t_world *world, char c, int y, int x)
{
	int	len;

	len = 0;
	while (world->sprites != NULL && world->sprites[len])
		len++;
	if (world->sprites == NULL)
	{
		world->sprites = (t_sprite **)malloc(sizeof(t_sprite *) * 2);
		world->sprites[0] = (t_sprite *)malloc(sizeof(t_sprite));
		world->sprites[1] = NULL;
	}
	else
		world->sprites = realloc_sprites(world->sprites, len);
	if (!world->sprites[len])
		return ;
	world->sprites[len]->c = c;
	world->sprites[len]->sp_xy[0] = ((float)(x + world->width) + 0.5f) * 64;
	world->sprites[len]->sp_xy[1] = ((float)(y + world->height) + 0.5f) * 64;
	select_options(world->sprites[len], c);
	world->world[4][y][x] = '0';
}
