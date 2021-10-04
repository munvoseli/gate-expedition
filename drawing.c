


#define Lx_tile_pix 16
#define Ly_tile_pix 16

#define Lx_room_pix 640
#define Ly_room_pix 640
#define Lx_inventory_pix 320
#define Ly_inventory_pix 320

#define Lx_win_pix 960
#define Ly_win_pix 640

#define Lx_font_pix 256
#define Ly_font_pix 128

void drawing_init( SDL_Window** p_winp, SDL_Renderer** p_renp,
		   SDL_Texture** p_texp_roombg,
		   SDL_Texture** p_texp_font,
		   SDL_Texture** p_texp_inventory )
{
	SDL_Init (SDL_INIT_EVERYTHING);
	IMG_Init (IMG_INIT_PNG);
	*p_winp = SDL_CreateWindow ("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Lx_win_pix, Ly_win_pix, 0);
	*p_renp = SDL_CreateRenderer (*p_winp, -1, 0);
	*p_texp_roombg = SDL_CreateTexture (*p_renp, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, Lx_room_pix, Ly_room_pix);
	*p_texp_font = SDL_CreateTexture (*p_renp, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, Lx_font_pix, Ly_font_pix);
	*p_texp_inventory = SDL_CreateTexture (*p_renp, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, Lx_inventory_pix, Ly_inventory_pix);
}

void load_texture_from_image( SDL_Renderer* renp,
			      SDL_Texture** p_texp,
			      char* file_name )
{
	SDL_Surface* surp = IMG_Load( file_name );
	*p_texp = SDL_CreateTextureFromSurface( renp, surp );
	SDL_FreeSurface( surp );
}

void load_spritesheet
(SDL_Renderer * renp, SDL_Texture** p_texp, SDL_Texture** p_texp_font)
{
	SDL_Surface * surp;
	surp = IMG_Load("sprites.png");
	*p_texp = SDL_CreateTextureFromSurface (renp, surp);
	surp = IMG_Load("font.png");
	*p_texp_font = SDL_CreateTextureFromSurface (renp, surp);
	SDL_FreeSurface (surp);
}

void set_rect_from_adj
( SDL_Rect * rect, Tileid h, Tileid v, Tileid d, Tileid s )
{
	rect->x = Lx_tile_pix * (v | (h << 1));
	rect->y = Ly_tile_pix * d;
	rect->y += 32 * s;
	if (s == 0)
	{
		rect->x = rect->x < 48 ? 0 : 48;
		rect->y = 0;
	}
	else if (s == 2)
	{
		rect->x = 0;
		rect->y = 32 * 2;
	}
}

void update_tiles_corner
( Room_t * p_room, SDL_Renderer * renp,
  SDL_Texture * texp_sprite,
  char xInTile, char yInTile )
{
	Tileid h, v, d;
	SDL_Rect src, dst;
	int x0, x1, y0, y1, ho, vo, xpo, ypo;
	x0  =            1 - xInTile;
	x1  = Lx_room_tile - xInTile;
	xpo =            8 * xInTile;
	ho  = xInTile ? 1 : -1;
	
	y0  =            1 - yInTile; // beginning and
	y1  = Ly_room_tile - yInTile; // end for the loops
	ypo =            8 * yInTile; // src/dst pixel offset
	vo  = yInTile ? 1 : -1; // vertical tile offset
	for (int i = x0; i < x1; ++i)
	{
		for (int j = y0; j < y1; ++j)
		{
			h = p_room->tiles[i+ho][j   ];
			d = p_room->tiles[i+ho][j+vo];
			v = p_room->tiles[i   ][j+vo];
			set_rect_from_adj (&src, h,v,d,p_room->tiles[i][j]);
			src.x += xpo;
			src.y += ypo;
			dst.x = i * Lx_tile_pix + xpo;
			dst.y = j * Ly_tile_pix + ypo;
			src.w = dst.w = Lx_tile_pix / 2;
			src.h = dst.h = Ly_tile_pix / 2;
			SDL_RenderCopy (renp, texp_sprite, &src, &dst);
		}
	}
}

void update_room_texture
( Room_t * p_room, SDL_Renderer * renp,
  SDL_Texture * texp_sprite, SDL_Texture * texp_room )
{
	Tileid h, v, d;
	int i, j;
	SDL_Rect src, dst;
	SDL_SetRenderTarget (renp, texp_room);
	update_tiles_corner( p_room, renp, texp_sprite, 0, 0 ); // top left
	update_tiles_corner( p_room, renp, texp_sprite, 1, 0 ); // top right
	update_tiles_corner( p_room, renp, texp_sprite, 1, 1 ); // lower right
	update_tiles_corner( p_room, renp, texp_sprite, 0, 1 ); // lower left
	SDL_RenderPresent (renp);
	SDL_SetRenderTarget (renp, NULL); // set back to window rendering
}

// does not set render target
void draw_text( SDL_Renderer* renp, SDL_Texture* texp_font,
		int pix_x, int pix_y, char* str )
{
	SDL_Rect src, dst;
	src.w = 16;
	src.h = 16;
	dst.x = pix_x;
	dst.y = pix_y;
	dst.w = 16;
	dst.h = 16;
	int i = 0;
	while (str[i] != 0)
	{
		src.x = (str[i] & 15) << 4;
		src.y = str[i] & (15 << 4);
		SDL_RenderCopy( renp, texp_font, &src, &dst );
		dst.x += 16;
		++i;
	}
}

void draw_room
(Room_t * p_room, SDL_Renderer * renp, SDL_Texture * texp_sprite, SDL_Texture * texp_bg)
{
	update_room_texture( p_room, renp, texp_sprite, texp_bg );
	SDL_Rect src, dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = Lx_room_pix;
	dst.h = Ly_room_pix;
	SDL_RenderCopy( renp, texp_bg, NULL, &dst );
}

void draw_player
(Player_t * p_player, SDL_Renderer * renp, SDL_Texture * texp_sprite)
{
	SDL_Rect src, dst;
	src.x = 64;
	src.y = 0;
	src.w = 12;
	src.h = 12;
	dst.x = (p_player->pos.x - p_player->size.x) >> 4; // 16 phy-units per pixel
	dst.y = (p_player->pos.y - p_player->size.y) >> 4;
	dst.w = 12;
	dst.h = 12;
	SDL_RenderCopy (renp, texp_sprite, &src, &dst);
}


void update_inventory_texture( SDL_Renderer* renp, SDL_Texture* texp_font,
			       SDL_Texture* texp_inventory,
			       Player_t* p_player );

void draw_inventory( SDL_Renderer* renp, SDL_Texture* texp_font,
		     SDL_Texture* texp_sprite,
		     SDL_Texture* texp_inventory, Player_t* p_player )
{
	char sz_num [12];
	SDL_Rect src, dst;
	SDL_SetRenderTarget( renp, texp_inventory );
	SDL_SetRenderDrawColor( renp, 0, 0, 0, 255 );
	SDL_RenderClear( renp );
	SDL_SetRenderDrawColor( renp, 170, 170, 170, 255 );
	dst.w = 8;
	dst.h = 8;
	dst.x = 4 + 32;
	dst.y = p_player->pldata.selected_item * 32 + 48 + 4;
	SDL_RenderFillRect( renp, &dst );
	src.w = 16;
	src.h = 16;
	dst.w = 16;
	dst.h = 16;
	src.x = 0;
	src.y = 0;
	dst.x = 16;
	dst.y = 48;
	for (int i = 0; i < 3; ++i)
	{
		SDL_RenderCopy( renp, texp_sprite, &src, &dst );
		sprintf( sz_num, "%d", p_player->pldata.inventory[i].amount );
		draw_text( renp, texp_font, dst.x + 32, dst.y, sz_num );
		dst.y += 32;
		src.y += 32;
	}
	SDL_SetRenderTarget( renp, NULL );
	src.x = 0;
	src.y = 0;
	src.w = Lx_inventory_pix;
	src.h = Ly_inventory_pix;
	dst.x = Lx_room_pix;
	dst.y = 0;
	dst.w = Lx_inventory_pix;
	dst.h = Ly_inventory_pix;
	SDL_RenderCopy( renp, texp_inventory, &src, &dst );
}
