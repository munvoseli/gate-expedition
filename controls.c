
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

#define UP_CL(code, cont) update_control(keystates[SDL_SCANCODE_##code], &p_controls->cont.held, &p_controls->cont.dur);

void update_controls
(const Uint8* keystates, Controls_t* p_controls)
{
	update_controls_duration(p_controls);
	UP_CL( F , dir[0] );
	UP_CL( D , dir[1] );
	UP_CL( S , dir[2] );
	UP_CL( A , dir[3] );
	UP_CL( K , inr[0] );
	UP_CL( L , inr[1] );
	UP_CL( J , inr[2] );
	UP_CL( H , inr[3] );
	UP_CL( SPACE , jump );
	UP_CL( P , inv[0] );
	UP_CL( N , inv[1] );
}



