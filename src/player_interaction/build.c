#include "../../includes/includes.h"

void	set_char_at_forward(char c, t_player *player)
{
	int		x;
	int		y;
	t_world	*world;

	world = get_world_active();
	x = player->player_pos_xy[0] + cosf(player->playerangle) * 55;
	y = player->player_pos_xy[1] + sinf(player->playerangle) * 55;
	world->world[get_chunk_from_pos(x / 64, y / 64)][(y / 64) % world->height][(x / 64) % world->width] = c;
}

static void	process_build(t_player *player, Block block, t_item *item)
{


	set_char_at_forward('0', player);
}

void	player_build(t_player *player, t_options options)
{
	char	c;

	c = get_hit_char(player);
	if (c == '0' || options.break_blocks != true || player->is_in_inventory)
		return ;
	player->slot->item->animation.is_playing = true;
	process_build(player, get_block_name_from_char(c), player->slot->item);
}
