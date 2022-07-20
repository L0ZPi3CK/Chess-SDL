#pragma once
#include "program.h"
#include "TextureManager.h"

class Map
{
public:
	Map();
	~Map();
	
	void LoadMap(int arr[8][8]);
	void DrawMap();
private:
	SDL_Rect src, dest, brown_src, brown_dest;

	SDL_Texture* black_square;
	SDL_Texture* white_square;
	SDL_Texture* brown_texture;

	int map[8][8];
};

