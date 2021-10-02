

void init_client
(Player_t * p_player)
{
	init_player( p_player );
}


void loop_client
(const Uint8 * keystates, Player_t * p_player, Room_t * p_room)
{
	update_controls (keystates, &p_player->controls);
	/*if (p_player->controls.jump_dur < 5 && p_player->is_on_ground)
	{
		p_player->vel.y -= 400;
		}*/
	if (p_player->controls.dir_held[0])
		p_player->vel.y -= 40;
	if (p_player->controls.dir_held[1])
		p_player->vel.x += 40;
	if (p_player->controls.dir_held[2])
		p_player->vel.y += 40;
	if (p_player->controls.dir_held[3])
		p_player->vel.x -= 40;
	update_controls_duration (&p_player->controls);
	p_player->is_on_ground = 0;
	player_move (p_player, p_room);
}
