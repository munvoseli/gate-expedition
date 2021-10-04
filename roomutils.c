
void apply_n_fractal( unsigned int n, Room_t* p_room )
{
	int x, y, r, x0, y0, x1, y1, x2, y2, sum;
	for (int i = 0; i < n; ++i)
	{
		x = rand() % 38;
		y = rand() % 38;
		r = rand();
		x0 = x + ((r     ) & 1) + ((r >> 1) & 1);
		y0 = y + ((r >> 2) & 1) + ((r >> 3) & 1);
		x1 = x + ((r >> 4) & 1) + ((r >> 5) & 1);
		y1 = y + ((r >> 6) & 1) + ((r >> 7) & 1);
		x2 = x + ((r >> 8) & 1) + ((r >> 9) & 1);
		y2 = y + ((r >> 10) & 1) + ((r >> 11) & 1);
		++x;
		++y;
		sum  = p_room->tiles[x0][y0];
		sum += p_room->tiles[x1][y1];
		sum += p_room->tiles[x2][y2];
		// sum is 0, 1, 2, 3
		p_room->tiles[x][y] = sum >> 1;
		//if (p_room->tiles[x0][y0] == p_room->tiles[x1][y1])
		//	p_room->tiles[x][y] = p_room->tiles[x0][y0];
		//else
		//	p_room->tiles[x][y] = p_room->tiles[x0][y0];
	}
}

char generate_room( unsigned int id, Room_t* p_room )
{
	int i, j;
	for (i = 0; i < Lx_room_tile; ++i)
		for (j = 0; j < Ly_room_tile; ++j)
			p_room->tiles[i][j] = (rand() & 1) ? 0 : 1;
	for (i = 0; i < Lx_room_tile; ++i)
	{
		p_room->tiles[i][0] = 1;
		p_room->tiles[i][Ly_room_tile - 1] = 1;
		p_room->tiles[0][i] = 1;
		p_room->tiles[Lx_room_tile - 1][i] = 1;
	}
	/*for (i = 9; i < 31; ++i)
		for (j = 9; j < 31; ++j)
		p_room->tiles[i][j] = 0;*/
	apply_n_fractal( 1600, p_room );
	p_room->id = id;
	j = rand() % 2 + 2;
	for (i = 0; i < j; ++i)
		p_room->tiles[rand() % 38 + 1][rand() % 38 + 1] = 2;
	//p_room->tiles[20][15] = 1;
	return 0;
}

void save_room( Room_t* p_room )
{
	// to do: more complex stuff
	char file_name [64];
	sprintf( file_name, "%d.data", p_room->id );
	FILE* fp = fopen( file_name, "w" );
	fwrite( &p_room->tiles, 1, Lx_room_tile * Ly_room_tile, fp );
	fclose( fp );
}

char load_room( unsigned int id, Room_t* p_room )
{
	p_room->id = id;
	char file_name [64];
	sprintf( file_name, "%d.data", id );
	FILE* fp = fopen( file_name, "r" );
	size_t desired = Lx_room_tile * Ly_room_tile;
	size_t loaded;
	if (fp)
	{
		loaded = fread( &p_room->tiles, 1, desired, fp );
		fclose( fp );
		return loaded != desired;
	}
	else
		return 1;
}


void init_room( unsigned int id, Room_t* p_room )
{
	load_room( id, p_room ) && generate_room( id, p_room );
}

void switch_to_room_id( unsigned int id, Room_t* p_room )
{
	save_room( p_room );
	load_room( id, p_room ) && generate_room( id, p_room );
}
