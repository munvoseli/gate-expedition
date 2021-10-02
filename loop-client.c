

void init_client
(Player_t * p_player)
{
	init_player( p_player );
}


void loop_client
(const Uint8 * keystates, Player_t * p_player, Room_t * p_room)
{
	update_controls( keystates, &p_player->controls );
	/*if (p_player->controls.jump_dur < 5 && p_player->is_on_ground)
	{
		p_player->vel.y -= 400;
		}*/
	if (p_player->controls.dir[0].held)
		p_player->vel.y -= 40;
	if (p_player->controls.dir[1].held)
		p_player->vel.x += 40;
	if (p_player->controls.dir[2].held)
		p_player->vel.y += 40;
	if (p_player->controls.dir[3].held)
		p_player->vel.x -= 40;
	if (p_player->controls.inr[0].held && p_player->controls.inr[0].dur == 0)
		p_room->tiles[p_player->pos.x >> 8][(p_player->pos.y - 96 - 256) >> 8] ^= 1;
	if (p_player->controls.inr[1].held && p_player->controls.inr[1].dur == 0)
		p_room->tiles[(p_player->pos.x + 96 + 255) >> 8][p_player->pos.y >> 8] ^= 1;
	if (p_player->controls.inr[2].held && p_player->controls.inr[2].dur == 0)
		p_room->tiles[p_player->pos.x >> 8][(p_player->pos.y + 96 + 255) >> 8] ^= 1;
	if (p_player->controls.inr[3].held && p_player->controls.inr[3].dur == 0)
		p_room->tiles[(p_player->pos.x - 96 - 256) >> 8][p_player->pos.y >> 8] ^= 1;
	p_player->is_on_ground = 0;
	player_move (p_player, p_room);
}
