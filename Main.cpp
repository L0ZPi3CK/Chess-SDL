#include "program.h"
#include "Promotion.h"

Program* program = nullptr;
Promotion* promotion = nullptr;

int main(int argc, char* argv[])
{
	// Define program refresh
	const int FPS = 144;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Creating window
	program = new Program();
	program->init("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);
	promotion = new Promotion();

	// Update the data displayed in the window until the program end
	while (program->running())
	{
		frameStart = SDL_GetTicks();

		program->handleEvents();
		program->update();
		program->render();

		// Window for pawnPromotion and program end
		if (program->promotionWindow == true)
		{
			promotion->init("ChoosePromotion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, promotionWindowWidth, promotionWindowHeight, false);
			while (promotion->running())
			{
				frameStart = SDL_GetTicks();

				promotion->handleEvents();
				promotion->update();
				promotion->render();

				frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime)
				{
					SDL_Delay(frameDelay - frameTime);
				}
				if (promotion->clickedPiece != 0)
				{
					program->clickedPiece = promotion->clickedPiece;
				}
			}
			program->promotionWindow = false;
			promotion->clean();
		}

		frameTime = SDL_GetTicks() - frameStart;
		
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	program->clean();
	return 0;
}