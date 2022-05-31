#include "program.h"
#include "TextureManager.h"
#include "Map.h"
#include "ChessPiece.h"

// Mouse handling
SDL_Rect MousePos;
SDL_MouseButtonEvent Mouse;

// Adding figures
Pieces Piece[32];

// Adding map
Map* map;

// Renderer and Event
SDL_Renderer* Program::renderer = nullptr;
SDL_Event Program::event;

Program::Program()
{
}

Program::~Program()
{
}

void Program::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)\
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	setPiecesPositionOnBoard();
	setPiece_Name_and_Color_and_Tex_and_SourcePositionAndSize_and_DestinationSize_ForAllPieces();

	// Centers position for all pieces
	for (numberOfTheClickedPiece = 0; numberOfTheClickedPiece < 32; numberOfTheClickedPiece++)
	{
		centerPiecePosition();
	}

	map = new Map();
}

void Program::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		mousedown = 1;
		centerMousePosition();
		numberOfTheClickedPiece = getClickedPieceNumber();
		if (numberOfTheClickedPiece >= 0 && numberOfTheClickedPiece < 32)
		{
			// Sets the initial piece position
			Piece[numberOfTheClickedPiece].set_PositionBeforeMove_x_y(Piece[numberOfTheClickedPiece].grab_destR_x(), Piece[numberOfTheClickedPiece].grab_destR_y());
		}
		break;

	case SDL_MOUSEBUTTONUP:
		mousedown = 0;
		if (numberOfTheClickedPiece >= 0 && numberOfTheClickedPiece < 32)
		{
			// Centers piece position and handles the executed movement
			centerPiecePosition();
			handlingPieceMovement(Piece[numberOfTheClickedPiece], Piece);
			checkPawnPromotion();
		}
		numberOfTheClickedPiece = -1;	// Reset, there is no piece with number -1

	}
}

void Program::update()
{
	setPiecePositionOnMousePosition();
	SDL_GetMouseState(&Mouse.x, &Mouse.y);
	MousePos.x = Mouse.x;
	MousePos.y = Mouse.y;

	if (clickedPiece != 0)
	{
		//std::cout << "Clicked Piece: " << clickedPiece << std::endl;
		switch (clickedPiece)
		{
		case 1:
			Piece[clickedPiecenumber].setName("Rook");
			Piece[clickedPiecenumber].set_srcR_x_y(140, Piece[clickedPiecenumber].grab_srcR_y());
			break;
		case 2:
			Piece[clickedPiecenumber].setName("Knight");
			Piece[clickedPiecenumber].set_srcR_x_y(280, Piece[clickedPiecenumber].grab_srcR_y());
			break;
		case 3:
			Piece[clickedPiecenumber].setName("Bishop");
			Piece[clickedPiecenumber].set_srcR_x_y(420, Piece[clickedPiecenumber].grab_srcR_y());
			break;
		case 4:
			Piece[clickedPiecenumber].setName("Queen");
			Piece[clickedPiecenumber].set_srcR_x_y(560, Piece[clickedPiecenumber].grab_srcR_y());
			break;
		default:
			break;
		}

		clickedPiece = 0;
	}
}

void Program::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	// Render copy for all pieces
	for (int i = 0; i < 32; i++)
	{
		SDL_RenderCopy(renderer, Piece[i].grab_chessTex(), Piece[i].grab_srcR(), Piece[i].grab_destR());
	}


	SDL_RenderPresent(renderer);
}

void Program::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	//std::cout << "Chess Cleaned" << std::endl;
}

bool Program::running()
{
	return isRunning;
}

void Program::centerMousePosition()
{
	const int base = int(windowHeight / 8);

	if (Mouse.x >= 0 && Mouse.x <= base)
		Mouse.x = int(base * 0.22);
	else if (Mouse.x > base && Mouse.x <= base * 2)
		Mouse.x = int(base * 1.22);
	else if (Mouse.x > base * 2 && Mouse.x <= base * 3)
		Mouse.x = int((base * 2) + base * 0.22);
	else if (Mouse.x > base * 3 && Mouse.x <= base * 4)
		Mouse.x = int((base * 3) + base * 0.22);
	else if (Mouse.x > base * 4 && Mouse.x <= base * 5)
		Mouse.x = int((base * 4) + base * 0.22);
	else if (Mouse.x > base * 5 && Mouse.x <= base * 6)
		Mouse.x = int((base * 5) + base * 0.22);
	else if (Mouse.x > base * 6 && Mouse.x <= base * 7)
		Mouse.x = int((base * 6) + base * 0.22);
	else if (Mouse.x > base * 7 && Mouse.x <= base * 8)
		Mouse.x = int((base * 7) + base * 0.22);
	else if (Mouse.x > base * 8)						// Protection against taking pieces out of the board
	{
		Mouse.x = windowHeight+1;
		Mouse.y = 0;
	}

	if (Mouse.y >= 0 && Mouse.y <= base)
		Mouse.y = 0;
	else if (Mouse.y > base && Mouse.y <= base * 2)
		Mouse.y = base;
	else if (Mouse.y > base * 2 && Mouse.y <= base * 3)
		Mouse.y = base * 2;
	else if (Mouse.y > base * 3 && Mouse.y <= base * 4)
		Mouse.y = base * 3;
	else if (Mouse.y > base * 4 && Mouse.y <= base * 5)
		Mouse.y = base * 4;
	else if (Mouse.y > base * 5 && Mouse.y <= base * 6)
		Mouse.y = base * 5;
	else if (Mouse.y > base * 6 && Mouse.y <= base * 7)
		Mouse.y = base * 6;
	else if (Mouse.y > base * 7 && Mouse.y <= base * 8)
		Mouse.y = base * 7;
}
void Program::centerPiecePosition()
{
	Piece[numberOfTheClickedPiece].centerPiece();
}
void Program::setPiecePositionOnMousePosition()
{
	// Centers piece on mouse
	Piece[numberOfTheClickedPiece].set_destR_x_y(Mouse.x - (int)(((windowHeight / 8) * 0.61)/2), Mouse.y - (int)((windowHeight/8) / 2));
}
void Program::setPiecesPositionOnBoard()
{
	for (int i = 0, cc = 25; i < 8; i++, cc += windowHeight/8)
	{
		Piece[i].set_destR_x_y(cc, 0);
		Piece[i + 8].set_destR_x_y(cc, windowHeight / 8);
		Piece[i + 16].set_destR_x_y(cc, windowHeight - ((windowHeight/8) * 2));
		Piece[i + 24].set_destR_x_y(cc, windowHeight - (windowHeight/8));
	}
}
void Program::setPiece_Name_and_Color_and_Tex_and_SourcePositionAndSize_and_DestinationSize_ForAllPieces()
{
	// For every Piece set Name,Color,Tex and Source Position and Size and Destination Size
	for (int i = 0; i < 32; i++)
	{
		Piece[i].setName(figureName[i]);

		if (i < 16)
			Piece[i].setColor("White");
		else if (i >= 16 && i < 32)
			Piece[i].setColor("Black");

		Piece[i].setTex();
		Piece[i].setSourcePositionAndSizeAndDestinationSize();
	}
}
void Program::checkPawnPromotion()
{
	// Pawn Promotion !!!
	if (Piece[numberOfTheClickedPiece].checkName() == "Pawn" &&
		(
			Piece[numberOfTheClickedPiece].grab_destR_y() == 0 && Piece[numberOfTheClickedPiece].checkColor() == "Black" ||
			Piece[numberOfTheClickedPiece].grab_destR_y() == 630 && Piece[numberOfTheClickedPiece].checkColor() == "White"
			))
	{
		promotionWindow = true;
		clickedPiecenumber = numberOfTheClickedPiece;
	}
}

int Program::getClickedPieceNumber()
{
	if (mousedown == 1)
	{
		for (int i = 0; i < 32; i++)
		{
			if (Mouse.x == Piece[i].grab_destR_x() && Mouse.y == Piece[i].grab_destR_y())
			{
				return i;
			}
		}
	}

	return -1;
}