#include "Map.h"


int board[8][8] =
{
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
	{0,1,0,1,0,1,0,1},
	{1,0,1,0,1,0,1,0},
};

Map::Map()
{
	black_square = TextureManager::LoadTexture("Assets/black_square.png", Program::renderer);
	white_square = TextureManager::LoadTexture("Assets/white_square.png", Program::renderer);
	brown_texture = TextureManager::LoadTexture("Assets/brown_texture.png", Program::renderer);
	LoadMap(board);
	src.x = src.y = 0;
	src.w = src.h = 115;
	dest.w = dest.h = windowHeight / 8;
	dest.x = dest.y = 0;
	
	brown_src.x = brown_src.y = 0;
	brown_src.w = 120;
	brown_dest.w = windowWidth-windowHeight;
	brown_src.h = brown_dest.h = windowHeight;
	brown_dest.x = windowHeight;
	brown_dest.y = 0;
}

void Map::LoadMap(int arr[8][8])
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			type = map[row][column];

			dest.x = column * windowHeight/8;
			dest.y = row * windowHeight/8;

			switch (type)
			{
			case 0:
				TextureManager::Draw(white_square, src, dest, Program::renderer);
				break;
			case 1:
				TextureManager::Draw(black_square, src, dest, Program::renderer);
				break;
			default:
				break;
			}
		}
	}

	TextureManager::Draw(brown_texture, brown_src, brown_dest, Program::renderer);
}