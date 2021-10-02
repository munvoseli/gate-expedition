


void init_room
(Room_t * p_room)
{
	int i, j;
	for (i = 0; i < Lx_tile_room; ++i)
		for (j = 0; j < Ly_tile_room; ++j)
			p_room->tiles[i][j] = 1;//rand() & 1;
	for (i = 9; i < 31; ++i)
		for (j = 9; j < 31; ++j)
		p_room->tiles[i][j] = 0;
	//p_room->tiles[20][15] = 1;
}
