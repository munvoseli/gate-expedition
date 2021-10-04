#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "shared.c"

#include "roomutils.c"
#include "posutils.c"
#include "controls.c" // also events
#include "player.c"
#include "playerutils.c"
#include "drawing.c"
#include "loop-client.c"


int main
(void)
{
	SDL_Event event;
	SDL_Window * winp;
	SDL_Renderer * renp;
	SDL_Texture * texp_sprite; // intermediate
	SDL_Texture * texp_bg; // for display
	SDL_Texture* texp_font; // intermediate
	SDL_Texture* texp_inventory; // for display

	Player_t player;

	Room_t room;
	char keepGoing = 1;
	const Uint8 * keystates = SDL_GetKeyboardState (NULL);

	srand((unsigned int) time(NULL));
	drawing_init (&winp, &renp, &texp_bg, &texp_font, &texp_inventory);
	load_spritesheet (renp, &texp_sprite, &texp_font);

	init_room( 0, &room );
	init_client (&player);
	init_controls (&player.controls);
	load_pldata( &player );
	while (keepGoing)
	{
		while (SDL_PollEvent (&event))
			keepGoing &= handle_event (&event, &player);
		loop_client (keystates, &player, &room);
		draw_room (&room, renp, texp_sprite, texp_bg);
		draw_player (&player, renp, texp_sprite);
		draw_inventory( renp, texp_font, texp_sprite,
				texp_inventory, &player );
		SDL_RenderPresent (renp);
		SDL_Delay (65);
	}
	SDL_DestroyTexture (texp_sprite);
	SDL_DestroyTexture (texp_bg);
	SDL_DestroyRenderer (renp);
	SDL_DestroyWindow (winp);
	IMG_Quit ();
	SDL_Quit ();
	save_room( &room );
	save_pldata( &player );
	return 0;
}
