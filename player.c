

// variable reuse could happen here, but what performance would it save?
// better to be readable for now?

// returns desired vector of force
// and stores length-ish of vector for finding the earliest vector
Pos mv_player_box
(Player_t * p_player, Pos pos_box, Pos size_box, int * lengthish)
{
	char useVertical;
	int Dhx, Dvy, Dhy, Dvx;
	Pos result;
	if (p_player->vel.x == 0 && p_player->vel.y == 0)
	{
		result.x = 0;
		result.y = 0;
		*lengthish = 0;
		return result;
	}
	Dhx = pos_box.x - p_player->pos.x + (p_player->vel.x > 0 ? -size_box.x : size_box.x);
	Dvy = pos_box.y - p_player->pos.y + (p_player->vel.y > 0 ? -size_box.y : size_box.y);
	if (p_player->vel.x == 0)
	{
		result.x = 0;
		result.y = Dvy;
		*lengthish = abs(Dvy * p_player->vel.x * p_player->vel.y);
		return result;
	}
	else if (p_player->vel.y == 0)
	{
		result.x = Dhx;
		result.y = 0;
		*lengthish = abs(Dhx * p_player->vel.x * p_player->vel.y);
		return result;
	}
	useVertical = Dhx * p_player->vel.y < Dvy * p_player->vel.x;
	useVertical ^= p_player->vel.x <= 0;
	useVertical ^= p_player->vel.y <= 0;
	if (useVertical)
	{
		result.x = 0;
		result.y = Dvy;
		//Dvx = Dvy * p_player->vel.x / p_player->vel.y;
		//*lengthish = abs (Dvx) + abs (Dvy);
		*lengthish = abs (Dvy * p_player->vel.x * p_player->vel.x) + abs (Dvy * p_player->vel.x * p_player->vel.y);
	}
	else
	{
		result.x = Dhx;
		result.y = 0;
		//Dhy = Dhx * p_player->vel.y / p_player->vel.x;
		//*lengthish = abs (Dhx) + abs (Dhy);
		*lengthish = abs (Dhx * p_player->vel.y * p_player->vel.y) + abs (Dhx * p_player->vel.x * p_player->vel.y);
	}
	//printf ("using vertical? %d\n", useVertical);
	//printf ("mv box : %d %d %d\n", result.x, result.y, *lengthish);
	return result;
}


// translates for mv_player_box
Pos mv_player_tile
(Player_t * p_player, Pos index_pos_tile, int * lengthish)
{
	Pos size_tile, pos_tile;
	// center of the tile -> use half of 256 for apothem
	size_tile.x = 128;
	size_tile.y = 128;
	// and then add the player size
	pos_addeq (&size_tile, &p_player->size);
	// center of tile -> offset half of 256
	pos_tile.x = (index_pos_tile.x << 8) | 128;
	pos_tile.y = (index_pos_tile.y << 8) | 128;
	return mv_player_box (p_player, pos_tile, size_tile, lengthish);
}

Pos mv_player_room
(Player_t * p_player, Room_t * p_room)
{
	Pos tile_bgn, tile_end, tile_cur;
	Pos cur_diff;
	int cur_diff_l;
	Pos max_diff;
	int max_diff_l = 0;
	char coll = 0;
	max_diff.x = 0;
	max_diff.y = 0;
	max_diff_l = 0;
	tile_bgn.x = cap((p_player->pos.x - p_player->size.x    ) >> 8, 0, Lx_room_tile);
	tile_bgn.y = cap((p_player->pos.y - p_player->size.y    ) >> 8, 0, Ly_room_tile);
	tile_end.x = cap((p_player->pos.x + p_player->size.x - 1) >> 8, 0, Lx_room_tile);
	tile_end.y = cap((p_player->pos.y + p_player->size.y - 1) >> 8, 0, Ly_room_tile);
	for (tile_cur.x = tile_bgn.x; tile_cur.x <= tile_end.x; ++tile_cur.x)
	{
		for (tile_cur.y = tile_bgn.y; tile_cur.y <= tile_end.y; ++tile_cur.y)
		{
			if (!p_room->tiles [tile_cur.x] [tile_cur.y])
				continue;
			p_player->is_on_ground = 1;
			if (!coll)
			{
				coll = 1;
				//printf ("~~new collision~~\n");
				//printf ("vel: %d %d\n", p_player->vel.x, p_player->vel.y);
			}
			cur_diff = mv_player_tile (p_player, tile_cur, &cur_diff_l);
			if (cur_diff_l >= max_diff_l)
			{
				max_diff_l = cur_diff_l;
				pos_seteq (&max_diff, &cur_diff);
			}
		}
	}
	//if (max_diff.x != 0 || max_diff.y != 0)
	//	printf ("%d  %d\n", max_diff.x, max_diff.y);
	return max_diff;
}

void player_move
(Player_t * p_player, Room_t * p_room)
{
	const int c_step = 4;
	int n_step = 0;
	int d;
	Pos mv_back;
	Pos pos_initial;
	pos_seteq (&pos_initial, &p_player->pos);
	for (; n_step < c_step; ++n_step)
	{
		pos_addeqdiv (&p_player->pos, &p_player->vel, c_step);
		mv_back = mv_player_room (p_player, p_room);
		pos_addeq (&p_player->pos, &mv_back);
	}
	p_player->vel.x = p_player->pos.x - pos_initial.x;
	p_player->vel.y = p_player->pos.y - pos_initial.y;
	cap_and_reduce( &p_player->vel.x, 120, 20 );
	cap_and_reduce( &p_player->vel.y, 120, 20 );
}

void init_player
(Player_t* p_player)
{
	p_player->pos.x = 256 * 20;
	p_player->pos.y = 256 * 20;
	p_player->vel.x = 0;
	p_player->vel.y = 0;
	p_player->size.x = 6*16;
	p_player->size.y = 6*16;
}




void player_break_in_dir( Room_t* p_room, Player_t* p_player, int dir )
{
	int xo = 0;
	int yo = 0;
	if (dir == 0)
		yo = -(96 + 256);
	else if (dir == 2)
		yo = 96 + 255;
	else if (dir == 1)
		xo = 96 + 255;
	else
		xo = -(96 + 256);
	int tile_x = (p_player->pos.x + xo) >> 8;
	int tile_y = (p_player->pos.y + yo) >> 8;
	if (p_player->pldata.inventory[p_player->pldata.selected_item].amount == 0 && p_player->pldata.selected_item)
		return;
	if (p_room->tiles[tile_x][tile_y])
		++p_player->pldata.inventory[p_room->tiles[tile_x][tile_y]].amount;
	if (p_player->pldata.selected_item)
		--p_player->pldata.inventory[p_player->pldata.selected_item].amount;
	p_room->tiles[tile_x][tile_y] = p_player->pldata.selected_item;
}
