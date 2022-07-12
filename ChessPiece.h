#pragma once
#include <string>
#include "TextureManager.h"
#include "program.h"

class Pieces
{
private:
	std::string color = "none";						// Piece color
	std::string name = "figura";					// Piece name
	SDL_Texture* chessTex;							// Creating Piece texture
	SDL_Rect srcR, destR;							// Creating start and end size and position
	int number = 0;										// Piece number

public:
	bool firstA = false;							// Check if the pawn has already made a move
	SDL_Rect positionBeforeMove;					// Pawn's position before the swap (set by clicking on it)

	void setColor(std::string col);					// Sets the color of the Piece
	void setName(std::string naz);					// Sets the Piece name
	std::string checkName()	{ return name; }		// Returns a Piece name
	std::string checkColor(){ return color; };		// Returns the color of the Piece

	void set_srcR_x_y	(int x, int y)												{ srcR.x = x;	srcR.y  = y;}	// Sets the graphic of the Piece
	void set_destR_x_y	(int x, int y)												{ destR.x = x;	destR.y = y;}	// sets the Piece Position on the board
	void set_srcR_w_h	(int w = 140, int h = 230)									{ srcR.w = w;	srcR.h  = h;}	// Initial Size of Piece
	void set_destR_w_h	(int w = ((windowHeight/8)* 0.61),  int h = windowHeight/8)	{ destR.w = w;	destR.h = h;}	// Final size of the Piece
	void set_PositionBeforeMove_x_y	(int x, int y)	{ positionBeforeMove.x = x;	  positionBeforeMove.y = y;}		// Sets position before movement
	void set_PieceNumber(int pieceNumber) { number = pieceNumber; }

	auto grab_chessTex(){ return chessTex; }		// Returns a chessTex
	auto grab_srcR()	{ return &srcR; }			// Returns &srcR
	auto grab_destR()	{ return &destR; }			// Returns &destR
	auto grab_destR_x() { return destR.x; }			// Returns destR.x
	auto grab_destR_y() { return destR.y; }			// Returns destR.y
	auto grab_srcR_y()	{ return srcR.y; }			// Returns srcR.y
	auto grab_PositionBeforeMove_x() { return positionBeforeMove.x; }
	auto grab_PositionBeforeMove_y() { return positionBeforeMove.y; }

	void setTex(){chessTex = TextureManager::LoadTexture("Assets/chess.png", Program::renderer);}		// Adding an entire texture palette to chessTex
	void centerPiece();								// centering Piece
	Pieces();

	void setSourcePositionAndSizeAndDestinationSize();

	/*		FOR HANDLING PIECE MOVEMENT		*/
	void restoreOldPosition() { set_destR_x_y(positionBeforeMove.x, positionBeforeMove.y); };

	int grab_throw_x_White() { return (int)(windowHeight + windowHeight * 0.022); };
	int grab_throw_x_Black() { return (int)(windowHeight + windowHeight * 0.066); };
	int grab_PieceNumber()   { return number; }

	bool movement_Pawn	(Pieces AllPic[32], int& throw_y);
	bool movement_Rook	(Pieces AllPic[32], int& throw_y);
	bool movement_Knight(Pieces AllPic[32], int& throw_y);
	bool movement_Bishop(Pieces AllPic[32], int& throw_y);
	bool movement_Queen	(Pieces AllPic[32], int& throw_y);
	bool movement_King	(Pieces AllPic[32], int& throw_y);

};


void handlingPieceMovement(Pieces& Pic, Pieces AllPic[32]);			// It does a looot of things
