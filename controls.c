
char handle_event (SDL_Event * p_event, Player_t * p_player)
{
	if (p_event->type == SDL_QUIT)
		return 0;
	else if (p_event->type == SDL_KEYDOWN)
	{
		
	}
	return 1;
}




void init_controls
(Controls_t* p_controls)
{
	// zero out controls
	unsigned char* p = (unsigned char*) p_controls;
	for (int i = 0; i < sizeof(p_controls); ++i)
	{
		//p_controls->dir_held [i] = 0;
		//p_controls->dir_dur  [i] = 0;
		p[i] = 0;
	}
}

void update_control
(Uint8 state, unsigned char * p_control_state, unsigned char * p_control_duration)
{
	if (state != *p_control_state)
	{
		*p_control_state = state;
		*p_control_duration = 0;
	}
}

void update_controls_duration
(Controls_t * p_controls)
{
	int i;
	for (i = 0; i < 4; ++i)
	{
		++p_controls->dir_dur[i];
	}
}

void update_controls
(const Uint8 * keystates, Controls_t * p_controls)
{
	update_control (keystates [SDL_SCANCODE_F], &p_controls->dir_held[0], &p_controls->dir_dur[0]);
	update_control (keystates [SDL_SCANCODE_D], &p_controls->dir_held[1], &p_controls->dir_dur[1]);
	update_control (keystates [SDL_SCANCODE_S], &p_controls->dir_held[2], &p_controls->dir_dur[2]);
	update_control (keystates [SDL_SCANCODE_A], &p_controls->dir_held[3], &p_controls->dir_dur[3]);
	update_control (keystates [SDL_SCANCODE_J], &p_controls->jump_held, &p_controls->jump_dur);
}



