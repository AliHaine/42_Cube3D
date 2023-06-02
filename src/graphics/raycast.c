/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:47:58 by ngalzand          #+#    #+#             */
/*   Updated: 2023/05/11 16:48:01 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"
#include "../../includes/defines.h"
#include "../../includes/structs.h"



// Ca c'est pas ptite feature personnelle, attention epilepsie, a mettre dans un variable color
//static uint32_t	fade(void)
//{
//	static uint8_t	r = 255;
//	static uint8_t	g = 0;
//	static uint8_t	b = 0;
//
//	if (r > 0 && b == 0)
//	{
//		r--;
//		g++;
//	}
//	else if (g > 0 && r == 0)
//	{
//		g--;
//		b++;
//	}
//	else if (b > 0 && g == 0)
//	{
//		b--;
//		r++;
//	}
//	return (((uint32_t)r << 24) | ((uint32_t)g << 16)
//		| ((uint32_t)b << 8) | 0xFF);
//}


static uint32_t	apply_fog(t_core *core, float fog_strength, int x, int y)
{
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	static uint32_t	black = ((0 << 24) | (0 << 16) | (0 << 8) | 255);

	if (fog_strength > 1.0)
		fog_strength = 1.0;
	if (fog_strength == 1.0)
		return (black); // Renvoi noir si le mur est trop loin
	color = wall_texture(core, x, y); // Sinon see fait chier a chercher la bonne couleur
	// Je comprend pas ces calculs, on les refera plus tard pour mieux les comprendre
	r = ((color >> 24) & 0xFF) * (1.0 - fog_strength);
	g = ((color >> 16) & 0xFF) * (1.0 - fog_strength);
	b = ((color >> 8) & 0xFF) * (1.0 - fog_strength);
	return ((r << 24) | (g << 16) | (b << 8) | (color & 0xFF));
}

static int  get_offset(t_core *core, t_ray ray)
{
    (void)core;
    (void)ray;
    if (ray.ray_angle > ((3 * PI) / 4) && ray.ray_angle < ((5 * PI) / 4))
    {
        printf("Ouest\n");
        return (((int)ray.ray_y % 64));
    }
    if (ray.ray_angle > (PI / 4) && ray.ray_angle < ((3 * PI) / 4))
    {
        printf("Sud\n");
        return (64 - ((int)ray.ray_x % 64));
    }
    if (ray.ray_angle > ((5 * PI) / 4) && ray.ray_angle < ((7 * PI) / 4))
    {
        printf("Nord\n");
        return (((int)ray.ray_x % 64));
    }
    if (ray.ray_angle < (PI / 4) || ray.ray_angle > ((7 * PI) / 4))
    {
        printf("Est\n");
        return (((int)ray.ray_y % 64));
    }
    return (0);
}

static void	draw_columns(t_core *core, t_ray ray, int r)
{
	float		wall_height;
	int			py;
	uint32_t	color;
	int			texture_offset;
	int			texture_y;

	// Connaitre la position x de la texture pour l'affichage 3D
    texture_offset = get_offset(core, ray);
//	if ((int)ray.ray_y % 64 == 0)
//		texture_offset = (int)ray.ray_y % 64;
//	else
//        texture_offset = (int)ray.ray_x % 64;
	// Savoir la hauteur du mur
	wall_height = (SCREEN_HEIGHT * 64) / ray.ray_distance;
	py = 0;
	// On dessine la colonne a partir du haut
	// Ciel
	while (py < (SCREEN_HEIGHT - wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		mlx_put_pixel(core->consts.img_3d, r, py, core->consts.top_color);
		py++;
	}
	// Murs
	while (py < (SCREEN_HEIGHT + wall_height) / 2 && py < SCREEN_HEIGHT)
	{
		texture_y = ((py * 2 - SCREEN_HEIGHT + wall_height) * TEXTURE_SIZE) / wall_height / 2;

		// Fonction qui va permettre d'avoir le pixel correspondant a la texture et qui
		// appliquera du brouillard selon la distance (ca devient juste noir quoi)
		// Ca va economiser des calculs, car a partir d'une certaine distance
		// plus besoin de chercher le pixel qui correspond a la texture, juste on met un pixel noir par defaut
		color = apply_fog(core, ray.ray_distance / FOG_DISTANCE, texture_offset, texture_y);
		mlx_put_pixel(core->consts.img_3d, r, py, color);
		py++;
	}
	// Sols
	while (py < SCREEN_HEIGHT)
	{
		mlx_put_pixel(core->consts.img_3d, r, py, core->consts.bot_color);
		py++;
	}
}

float	calc_ray_distance(t_core *core, t_ray ray)
{
	float	ray_distance;

	// calcul que j'ai trouvé sur internet
	// voir "calcul distance euclidienne dans un espace en 2 dimensions"
	ray_distance = sqrtf(((ray.ray_x - core->player.playerpos[0]) * (
					ray.ray_x - core->player.playerpos[0]) + ((ray.ray_y
						- core->player.playerpos[1]) * (ray.ray_y
						- core->player.playerpos[1]))));
	// calcul pour corriger l'effet fisheye (murs courbés)
	ray_distance *= cos(ray.ray_angle - core->player.playerangle);
	return (ray_distance);
}

void	raycast(t_core *core)
{
	int		r; // indice du rayon actuel
	t_ray	ray; // Donnees du rayon actuel
	float	thales[2]; // Stocker le cosinus[0] et le sinus[1], ca evite de recalculer h24

	r = -1;
	// Donne l'angle du tout premier rayon sachant que core->player.playerangle est le milieu du FOV (logik)
	ray.start_angle = core->player.playerangle - (core->consts.fov / 2);
	while (++r < RAY_NUMBER)
	{
		ray.ray_x = core->player.playerpos[0]; // Les rayons partent de la position du joueur
		ray.ray_y = core->player.playerpos[1];
		ray.ray_angle = ray.start_angle + (r * core->consts.dist_between_ray); // Savoir l'angle du rayon actuel
		thales[0] = cosf(ray.ray_angle); // Savoir dans quelle direction et combien distance le rayon va avancer a chaque iteration
		thales[1] = sin(ray.ray_angle);
		while (ray.ray_x >= 0 && ray.ray_y >= 0
			&& core->consts.map[(int)ray.ray_y / 64]
			[(int)ray.ray_x / 64] != '1') // Tant que c'est pas un mur en gros
		{
			ray.ray_x += thales[0]; // On fait avancer le rayon
			ray.ray_y += thales[1];
			// On dessiner le rayon sur la minimap
			mlx_put_pixel(core->consts.img_map, (ray.ray_x / MINIMAP_SIZE),(ray.ray_y / MINIMAP_SIZE), core->consts.ray_color);
		}
		// Calcul de la distance du point final du rayon par rapport au joueur pour ensuite voir comment afficher les murs
		ray.ray_distance = calc_ray_distance(core, ray);
		// Dessiner la 3d par colonnes vu que chaque rayon correspond a 1 pixel x de l'ecran,
		// chaque rayon permet donc de dessiner 1 colonne de pixel, ca fait beaucoup de calculs tout ca
		draw_columns(core, ray, r);
	}
}
