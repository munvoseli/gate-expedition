


#define Lx_pix_tile 16
#define Ly_pix_tile 16

#define Lx_pix_win 640
#define Ly_pix_win 640

void drawing_init
(SDL_Window ** p_winp, SDL_Renderer ** p_renp, SDL_Texture ** p_texp_bg)
{
	SDL_Init (SDL_INIT_EVERYTHING);
	IMG_Init (IMG_INIT_PNG);
	*p_winp = SDL_CreateWindow ("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Lx_pix_win, Ly_pix_win, 0);
	*p_renp = SDL_CreateRenderer (*p_winp, -1, 0);
	*p_texp_bg = SDL_CreateTexture (*p_renp, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, Lx_pix_win, Ly_pix_win);
}

void load_spritesheet
(SDL_Renderer * renp, SDL_Texture ** p_texp)
{
	SDL_Surface * surp;
	surp = IMG_Load ("sprites.png");
	*p_texp = SDL_CreateTextureFromSurface (renp, surp);
	SDL_FreeSurface (surp);
}

void set_rect_from_adj
( SDL_Rect * rect, Tileid h, Tileid v, Tileid d, Tileid s )
{
	rect->x = Lx_pix_tile * (v | (h << 1));
	rect->y = Ly_pix_tile * d;
	rect->y += 32 * s;
	if (s == 0)
	{
		rect->x = rect->x < 48 ? 0 : 48;
		rect->y = 0;
	}
}

void update_tiles_corner
( Room_t * p_room, SDL_Renderer * renp,
  SDL_Texture * texp_sprite,
  char xInTile, char yInTile )
{
	Tileid h, v, d;
	SDL_Rect src, dst;
	int x0, x1, y0, y1, ho, vo, hpo, vpo;
	if (xInTile)
	{
		x0 = 0;
		x1 = Lx_tile_room - 1;
		ho = 1;
		hpo = 8;
	}
	else
	{
		x0 = 1;
		x1 = Lx_tile_room;
		ho = -1;
		hpo = 0;
	}
	if (yInTile)
	{
		y0 = 0;
		y1 = Ly_tile_room - 1;
		vo = 1;
		vpo = 8;
	}
	else
	{
		y0 = 1;
		y1 = Ly_tile_room;
		vo = -1;
		vpo = 0;
	}
	for (int i = x0; i < x1; ++i)
	{
		for (int j = y0; j < y1; ++j)
		{
			h = p_room->tiles[i+ho][j   ];
			d = p_room->tiles[i+ho][j+vo];
			v = p_room->tiles[i   ][j+vo];
			set_rect_from_adj (&src, h,v,d,p_room->tiles[i][j]);
			src.x += hpo;
			src.y += vpo;
			dst.x = i * Lx_pix_tile + hpo;
			dst.y = j * Ly_pix_tile + vpo;
			src.w = dst.w = Lx_pix_tile / 2;
			src.h = dst.h = Ly_pix_tile / 2;
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

void draw_room
(Room_t * p_room, SDL_Renderer * renp, SDL_Texture * texp_sprite, SDL_Texture * texp_bg)
{
	update_room_texture( p_room, renp, texp_sprite, texp_bg );
	SDL_RenderCopy( renp, texp_bg, NULL, NULL );
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
