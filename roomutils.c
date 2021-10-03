
char generate_room( unsigned int id, Room_t* p_room )
{
	int i, j;
	for (i = 0; i < Lx_room_tile; ++i)
		for (j = 0; j < Ly_room_tile; ++j)
			p_room->tiles[i][j] = 1;//rand() & 1;
	for (i = 9; i < 31; ++i)
		for (j = 9; j < 31; ++j)
		p_room->tiles[i][j] = 0;
	p_room->id = id;
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
