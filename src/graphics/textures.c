
#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"

uint32_t	wall_texture(t_core *core, int x, int y)
{
	static unsigned int			bx = 0; //byte x
	static unsigned int			by = 0; // byte y
	unsigned int				total;
	unsigned int				scale;
	uint32_t					color;

	scale = core->consts.wall_texture->width / 64; // J'essayai de mettre a la bonne echelle mais c'est bof
	bx = (x * scale) % core->consts.wall_texture->width;
	by = (y * scale) % core->consts.wall_texture->height;
	total = (bx + by * core->consts.wall_texture->width) * 4;
	color = (core->consts.wall_texture->pixels[total] << 24) //cette ligne est juste, on recupere rgba
		+ (core->consts.wall_texture->pixels[total + 1] << 16)
		+ (core->consts.wall_texture->pixels[total + 2] << 8)
		+ (core->consts.wall_texture->pixels[total + 3]);
	return (color);
}

// En gros, dans un mlx_texture_t on a un tableau uint8_t *pixels;
// qui se presente dans cette forme: [r,g,b,a,r,g,b,a,r,g,b,a,r,g,b,a....]
// Donc 1 pixel correspond a 4 variabes, r,g,b,a
// Donc pour se balader de pixels en pixels on avance de 4
// Moi je fais des calculs bizarres pour afficher correctement la texture mais bon
// c'est une fonction en beta, on est loin du resultat attendu