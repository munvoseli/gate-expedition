all:
	gcc `pkg-config --cflags sdl2 SDL2_image` client.c `pkg-config --libs sdl2 SDL2_image`
#	gcc -o server server.c
