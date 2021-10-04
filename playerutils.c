// This file contains stuff like inventory, but not movement
// less the player character and more the other parts of the player state

void save_pldata( Player_t* p_player )
{
	FILE* fp = fopen( "player.data", "w" );
	fwrite( &p_player->pldata, sizeof(Pldata), 1, fp );
	fclose(fp);
}

void load_pldata( Player_t* p_player )
{
	FILE* fp = fopen( "player.data", "r" );
	if (fp)
	{
		fread( &p_player->pldata, sizeof(Pldata), 1, fp );
		p_player->pldata.selected_item = 0;
	}
	else
	{
		for (int i = 0; i < 3; ++i)
			p_player->pldata.inventory[i].amount = 10;
	}
}
