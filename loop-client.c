

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
	if (p_player->controls.inr[0].held
	    && p_player->controls.inr[0].dur == 0)
		player_break_in_dir( p_room, p_player, 0 );
	if (p_player->controls.inr[1].held
	    && p_player->controls.inr[1].dur == 0)
		player_break_in_dir( p_room, p_player, 1 );
	if (p_player->controls.inr[2].held
	    && p_player->controls.inr[2].dur == 0)
		player_break_in_dir( p_room, p_player, 2 );
	if (p_player->controls.inr[3].held
	    && p_player->controls.inr[3].dur == 0)
		player_break_in_dir( p_room, p_player, 3 );
	
	if (p_player->controls.inv[0].held
	    && p_player->controls.inv[0].dur == 0)
		--p_player->pldata.selected_item;
	if (p_player->controls.inv[1].held
	    && p_player->controls.inv[1].dur == 0)
		++p_player->pldata.selected_item;
	p_player->is_on_ground = 0;
	player_move (p_player, p_room);
	player_test_portal( p_room, p_player );
}
