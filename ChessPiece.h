#pragma once
#include <string>
#include "TextureManager.h"
#include "program.h"

class Pieces
{
private:
	std::string color = "none";						// Kolor jaki ma figura
	std::string name = "figura";					// Nazwa figury
	SDL_Texture* chessTex;							// Utorzenie Tekstury chessTex
	SDL_Rect srcR, destR;							// Dodanie rozmiaru i polozenia poczatkowego i koncowego

public:
	bool firstA = false;							// Czy pionek wykonal juz ruch
	SDL_Rect positionBeforeMove;					// Pozycja pionka przed zamiana (ustawiana przy kliknieciu na niego)
	// Wysokosc pola ktore zajmuje figura
	// int height = 115;
	// int width = 115;

	void setColor(std::string col);																					// Ustawia kolor figury
	void setName(std::string naz);																					// Ustawia nazwe figury
	std::string checkName()	{ return name; }																		// Zwraca nazwe figury
	std::string checkColor(){ return color; };																		// Zwraca kolor figury

	void set_srcR_x_y	(int x, int y)				{ srcR.x = x;	srcR.y  = y;}									// Ustawia grafike figury ktora chcemy
	void set_destR_x_y	(int x, int y)				{ destR.x = x;	destR.y = y;}									// Polozenie figury na planszy
	void set_srcR_w_h	(int w = 140, int h = 230)	{ srcR.w = w;	srcR.h  = h;}									// Poczatkowa wielkosc figury
	void set_destR_w_h	(int w = ((windowHeight/8)* 0.61),  int h = windowHeight/8)	{ destR.w = w;	destR.h = h;}	// Koncowa wielkosc figury
	void set_PositionBeforeMove_x_y	(int x, int y)	{ positionBeforeMove.x = x;	  positionBeforeMove.y = y;}		// Ustawia pozycje przed ruchem

	auto grab_chessTex(){ return chessTex; }										// Zwraca chessTex
	auto grab_srcR()	{ return &srcR; }											// Zwraca &srcR
	auto grab_destR()	{ return &destR; }											// Zwraca &destR
	auto grab_destR_x() { return destR.x; }											// Zwraca destR.x
	auto grab_destR_y() { return destR.y; }											// Zwraca destR.y
	auto grab_srcR_y()	{ return srcR.y; }											// Return srcR.y
	auto grab_PositionBeforeMove() { return positionBeforeMove.x + positionBeforeMove.y; }

	void setTex(){chessTex = TextureManager::LoadTexture("Assets/chess5.png", Program::renderer);}		// Dodanie calej palety tekstur do chessTex
	void centerPiece();																// srodkuje figure
	Pieces();

	void setSourcePositionAndSizeAndDestinationSize();
};


void handlingPieceMovement(Pieces& Pic, Pieces AllPic[32], int toka = 0);