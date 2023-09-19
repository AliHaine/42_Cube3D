
#include "../../includes/includes.h"

static void	realloc_sprites(t_world *world, int len)
{
	t_sprite	**new_tab;
	int			s;

	s = -1;
	new_tab = (t_sprite **)malloc(sizeof(t_sprite *) * (len + 2));
	while (++s < len)
		new_tab[s] = world->sprites[s];
	new_tab[s] = (t_sprite *)malloc(sizeof(t_sprite));
	new_tab[s + 1] = NULL;
	if (world->sprites)
		free(world->sprites);
	world->sprites = new_tab;
}

static void	select_options(t_sprite *sp, char c)
{
	if (c == '>')
	{
		sp->hostile = true;
		sp->scale = 576;
	}
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
		realloc_sprites(world, len);
	if (!world->sprites[len])
		return ;
	world->sprites[len]->c = c;
	world->sprites[len]->sp_xy[0] = ((float)(x + world->width) + 0.5f) * 64;
	world->sprites[len]->sp_xy[1] = ((float)(y + world->height) + 0.5f) * 64;
	select_options(world->sprites[len], c);
	world->world[4][y][x] = '0';
}
