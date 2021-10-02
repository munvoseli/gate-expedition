

void pos_addeq (Pos * a, Pos * b)
{
	a->x += b->x;
	a->y += b->y;
}

void pos_addeqdiv (Pos * a, Pos * b, int scale)
{
	a->x += b->x / scale;
	a->y += b->y / scale;
}

void pos_seteq (Pos * a, Pos * b)
{
	a->x = b->x;
	a->y = b->y;
}



char are_colliding
(Pos pos_a, Pos pos_b, Pos size)
{
	return abs (pos_a.x - pos_b.x) < size.x && abs (pos_a.y - pos_b.y) < size.y;
}
