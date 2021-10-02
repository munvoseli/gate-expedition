


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

void set_rect_from_adj (SDL_Rect * rect, Tileid h, Tileid v, Tileid d, Tileid s)
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

void update_room_texture
(Room_t * p_room, SDL_Renderer * renp, SDL_Texture * texp_sprite, SDL_Texture * texp_room)
{
	Tileid h, v, d;
	int i, j;
	SDL_Rect src, dst;
	SDL_SetRenderTarget (renp, texp_room);
	// top left
	for (i = 1; i < Lx_tile_room; ++i)
	{
		for (j = 1; j < Ly_tile_room; ++j)
		{
			h = p_room->tiles[i-1][j];
			d = p_room->tiles[i-1][j-1];
			v = p_room->tiles[i][j-1];
			set_rect_from_adj (&src, h,v,d,p_room->tiles[i][j]);
			dst.x = i * Lx_pix_tile;
			dst.y = j * Ly_pix_tile;
			src.w = dst.w = Lx_pix_tile / 2;
			src.h = dst.h = Ly_pix_tile / 2;
			SDL_RenderCopy (renp, texp_sprite, &src, &dst);
		}
	}
	// top right
	for (i = 0; i < Lx_tile_room - 1; ++i)
	{
		for (j = 1; j < Ly_tile_room; ++j)
		{
			h = p_room->tiles[i+1][j];
			d = p_room->tiles[i+1][j-1];
			v = p_room->tiles[i][j-1];
			set_rect_from_adj (&src, h,v,d,p_room->tiles[i][j]);
			src.x += 8;
			dst.x = i * Lx_pix_tile + 8;
			dst.y = j * Ly_pix_tile;
			src.w = dst.w = Lx_pix_tile / 2;
			src.h = dst.h = Ly_pix_tile / 2;
			SDL_RenderCopy (renp, texp_sprite, &src, &dst);
		}
	}
	// bottom right
	for (i = 0; i < Lx_tile_room - 1; ++i)
	{
		for (j = 0; j < Ly_tile_room - 1; ++j)
		{
			h = p_room->tiles[i+1][j];
			d = p_room->tiles[i+1][j+1];
			v = p_room->tiles[i][j+1];
			set_rect_from_adj (&src, h,v,d,p_room->tiles[i][j]);
			src.x += 8;
			src.y += 8;
			dst.x = i * Lx_pix_tile + 8;
			dst.y = j * Ly_pix_tile + 8;
			src.w = dst.w = Lx_pix_tile / 2;
			src.h = dst.h = Ly_pix_tile / 2;
			SDL_RenderCopy (renp, texp_sprite, &src, &dst);
		}
	}
	// bottom left
	for (i = 1; i < Lx_tile_room; ++i)
	{
		for (j = 0; j < Ly_tile_room - 1; ++j)
		{
			h = p_room->tiles[i-1][j];
			d = p_room->tiles[i-1][j+1];
			v = p_room->tiles[i][j+1];
			set_rect_from_adj (&src, h,v,d,p_room->tiles[i][j]);
			src.y += 8;
			dst.x = i * Lx_pix_tile;
			dst.y = j * Ly_pix_tile + 8;
			src.w = dst.w = Lx_pix_tile / 2;
			src.h = dst.h = Ly_pix_tile / 2;
			SDL_RenderCopy (renp, texp_sprite, &src, &dst);
		}
	}
	SDL_RenderPresent (renp);
	SDL_SetRenderTarget (renp, NULL); // set back to window rendering
}

void draw_room
(Room_t * p_room, SDL_Renderer * renp, SDL_Texture * texp_sprite, SDL_Texture * texp_bg)
{
	update_room_texture (p_room, renp, texp_sprite, texp_bg);
	SDL_RenderCopy (renp, texp_bg, NULL, NULL);
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
