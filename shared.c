

#define Lx_room_tile 40
#define Ly_room_tile 40


#define TILE_COLL 1

#define PMODE_MOVE 0
#define PMODE_TEXT 1

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
	Tileid tiles [Lx_room_tile] [Ly_room_tile];
} Room_t;

typedef struct Control_pair_struct
{
	unsigned char held;
	unsigned char dur;
} Control;

typedef struct Controls_struct
{
	Control dir [4]; // use breadquest directions, 0N 1E 2S 3W
	Control inr [4]; // interaction
	Control jump;
	Control inv [2];
} Controls_t;

typedef unsigned int Item;

typedef struct Inventory_item_struct
{
	Item id;
	unsigned int amount;
} Inventory_item;

// Data that does not relate to the physics character and should be saved
typedef struct Player_data_struct
{
	Inventory_item inventory [256];
	unsigned int selected_item;
} Pldata;

typedef struct Player_struct
{
	Pos pos;
	Pos vel;
	Pos size;
	char is_on_ground;
	char has_jumped;
	char control_mode;
	Controls_t controls;
	Pldata pldata;
} Player_t;
