#include "Window2Tex.h"
#include "TextureManager.h"

WindowTex::WindowTex()
{
	std::cout << "1\n";
	promotionWindow = TextureManager::LoadTexture("Assets/window2.png", Promotion::renderer);
	src.y = 0;
	src.x = 0;
	src.h = 230;
	src.w = 560;


	dest.x = dest.y = 0;
	dest.w = 560;
	dest.h = 230;

}

void WindowTex::LoadWindow(int number)
{
	switch (number)
	{
	case 0:
		src.x = 0;
		break;
	case 1:
		src.x = 560;
		break;
	case 2:
		src.x = 1120;
	default:
		break;
	}
}

void WindowTex::DrawWindow()
{
	TextureManager::Draw(promotionWindow, src, dest, Promotion::renderer);
}