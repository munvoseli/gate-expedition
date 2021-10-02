

#define Lx_tile_room 40
#define Ly_tile_room 40


#define TILE_COLL 1

typedef unsigned char Tileinfo;

typedef unsigned char Tileid;

int relu( int a ) {return a <= 0 ? 0 : a;};
int cap( int a, int b, int c ) {return a <= b ? b : a >= c ? c : a;};
void move_towards_zero( int* p, int amount )
{
	if ( *p <= -amount )
		*p += amount;
	else if ( *p >= amount )
		*p -= amount;
	else
		*p = 0;
}
void cap_and_reduce( int* p, int bound, int amount )
{
	move_towards_zero( p, amount );
	if ( *p <= -bound )
		*p = -bound;
	else if ( *p >= bound )
		*p = bound;
}

typedef struct Pos_struct // in 1/256 of a tile
{
	int x;
	int y;
} Pos;



typedef struct Room_struct
{
	unsigned int id;
	Tileid tiles [Lx_tile_room] [Ly_tile_room];
} Room_t;

typedef struct Controls_struct
{
	unsigned char dir_held [4]; // use breadquest directions, 0N 1E 2S 3W
	unsigned char dir_dur [4];
	unsigned char jump_held;
	unsigned char jump_dur;
} Controls_t;

typedef struct Player_struct
{
	Pos pos;
	Pos vel;
	Pos size;
	char is_on_ground;
	char has_jumped;
	Controls_t controls;
} Player_t;


