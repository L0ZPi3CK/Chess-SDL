#pragma once
#include "Promotion.h"

class WindowTex
{
public:
	WindowTex();
	~WindowTex();

	void LoadWindow(int number = 0);
	void DrawWindow();

private:
	SDL_Rect src, dest;
	SDL_Texture* promotionWindow;
};

