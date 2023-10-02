
#ifndef SPRITES_H
# define SPRITES_H

# include "../includes.h"

typedef enum {
	EMMA,
	MUSHROOM,
	RED_FLOWER,
	PINK_FLOWER,
	WEEDS,
	CRIMSON_FUNGUS,
	FIRE_CORAL,
	WARPD_FUNFUS,
	WITHER_ROSE,
	SPRITES_NUMBER,
}	Sprite;

static const char		*g_sprites_name[] = {
	"e_0",
	"brown_mushroom",
	"poppy",
	"pink_tulip",
	"carrots_stage1",
	"crimson_fungus",
	"fire_coral",
	"warped_fungus",
	"wither_rose"
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
	int				scale;
	float			dist;
	int				x_origin;
	int				y_origin;
	float			sp_xy[2];
	float			chunk_sp_xy[2];
	int				chunk_save;
	int				cell_xy[2];
	float			fog;
	mlx_texture_t	*texture;
	t_sprite_calc	vars;
}					t_sprite;

void		draw_sprites(t_player *player, t_imgs *imgs, const float *dists);

void		sprites_place(t_world *world, int chunk);
void		add_sprite(t_world *world, int chunk, char c, int xy[2]);

void		sprites_generator(t_world *world);
void		select_sprite(t_sprite *sp, char c);
void		init_sprite_vars(t_sprite *sp, t_player *player, mlx_texture_t *img);
void		free_all_sprites(t_world *world);
void		realloc_sprites(t_sprite ***sprites, int len);
void		reload_sprite_pos(t_world *world);
void		move_multiple_sprites(t_world *world, int dir);

char		get_rand_sprite_char(t_world *world);

#endif