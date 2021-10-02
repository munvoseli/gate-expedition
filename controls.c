
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
	for (int i = 0; i < sizeof(Controls_t); ++i)
	{
		//p_controls->dir_held [i] = 0;
		//p_controls->dir_dur  [i] = 0;
		p[i] = 0;
	}
	//for (int i = 0; i < sizeof(Controls_t); ++i)
	//printf("%s", controls
}

void update_control
(Uint8 state, unsigned char * p_control_state, unsigned char * p_control_duration)
{
	if (state != *p_control_state)
	{
		*p_control_state = state;
		*p_control_duration = 0;
		//printf( "Updating control to %d\n", state );
	}
}

void update_controls_duration
(Controls_t * p_controls)
{
	int i;
	unsigned char* p = (unsigned char*) p_controls;
	for (i = 1; i < sizeof(Controls_t); i += 2)
		++*(p + i);
}

void update_controls
(const Uint8* keystates, Controls_t* p_controls)
{
	update_controls_duration(p_controls);
	update_control(keystates[SDL_SCANCODE_F], &p_controls->dir[0].held, &p_controls->dir[0].dur);
	update_control(keystates[SDL_SCANCODE_D], &p_controls->dir[1].held, &p_controls->dir[1].dur);
	update_control(keystates[SDL_SCANCODE_S], &p_controls->dir[2].held, &p_controls->dir[2].dur);
	update_control(keystates[SDL_SCANCODE_A], &p_controls->dir[3].held, &p_controls->dir[3].dur);
	update_control(keystates[SDL_SCANCODE_K], &p_controls->inr[0].held, &p_controls->inr[0].dur);
	update_control(keystates[SDL_SCANCODE_L], &p_controls->inr[1].held, &p_controls->inr[1].dur);
	update_control(keystates[SDL_SCANCODE_J], &p_controls->inr[2].held, &p_controls->inr[2].dur);
	update_control(keystates[SDL_SCANCODE_H], &p_controls->inr[3].held, &p_controls->inr[3].dur);
	update_control(keystates[SDL_SCANCODE_SPACE], &p_controls->jump.held, &p_controls->jump.dur);
}



