
#ifndef SPRITES_H
# define SPRITES_H

# include "../includes.h"

typedef enum {
	EMMA,
	MUSHROOM,
	RED_FLOWER,
	PINK_FLOWER,
	WEEDS,
	TOTAL_LENGTH,
}	Sprite;

static const char		*g_sprites_name[] = {
	"e_0",
	"brown_mushroom",
	"poppy",
	"pink_tulip",
	"carrots_stage1",
};

typedef struct s_sprite_calc
{
	int				x;
	int				y;
	int				size[2];
	float			t_pos[2];
	float			offset[2];
	float			s_pos[3];
	float			tmp[2];
	int				sc_xy[2];
}					t_sprite_calc;

typedef struct s_sprite
{
	char			c;
	bool			hostile;
	int				scale;
	float			dist;
	float			sp_xy[2];
	float			chunk_sp_xy[2];
	int				chunk_save;
	int				cell_xy[2];
	float			fog;
	mlx_texture_t	*texture;
	t_sprite_calc	vars;
}					t_sprite;

void		draw_sprites(t_player *player, t_imgs *imgs, const float *dists);

void		add_sprite(t_world *world, char c, int y, int x);
void		delete_sprite(t_sprite **sprites, int s);
void		free_all_sprites(t_sprite ***sprites);
t_sprite	*get_sprite_by_int(t_sprite **sprites, int x, int y);

#endif