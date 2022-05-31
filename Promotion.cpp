#include "Promotion.h"

// Mouse handling
SDL_Rect pPos;
SDL_MouseButtonEvent promMouse;

// Renderer and Event
SDL_Renderer* Promotion::renderer = nullptr;
SDL_Event Promotion::event;

// Window
WindowTex* window_tex;

Promotion::Promotion()
{

}

Promotion::~Promotion()
{

}

void Promotion::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		Promotion::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Promotion::renderer)
		{
			SDL_SetRenderDrawColor(Promotion::renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	window_tex = new WindowTex();
}

void Promotion::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		checkClickedPiece();
		break;
	}

}

void Promotion::update()
{
	SDL_GetMouseState(&promMouse.x, &promMouse.y);
	pPos.x = promMouse.x;
	pPos.y = promMouse.y;
}

void Promotion::render()
{
	SDL_RenderClear(Promotion::renderer);
	window_tex->LoadWindow(0);
	window_tex->DrawWindow();
	SDL_RenderPresent(Promotion::renderer);
}

void Promotion::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//std::cout << "promotion Cleaned" << std::endl;
}

bool Promotion::running()
{
	return isRunning;
}


void Promotion::checkClickedPiece()
{
	if (pPos.x <= promotionWindowWidth / 4)
	{
		clickedPiece = 1;
		isRunning = false;
	}
	else if (pPos.x > promotionWindowWidth / 4 && pPos.x <= (promotionWindowWidth / 4) * 2)
	{
		clickedPiece = 2;
		isRunning = false;
	}
	else if (pPos.x > (promotionWindowWidth / 4) * 2 && pPos.x <= (promotionWindowWidth / 4) * 3)
	{
		clickedPiece = 3;
		isRunning = false;
	}
	else if (pPos.x > (promotionWindowWidth / 4) * 3 && pPos.x < promotionWindowWidth)
	{
		clickedPiece = 4;
		isRunning = false;
	}
}