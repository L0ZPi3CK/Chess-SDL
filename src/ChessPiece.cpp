#include "ChessPiece.h"

const int moveSize = windowHeight / 8;

void Pieces::setColor(std::string col)
{
	color = col;
	if (color == "White" || color == "white")
	{
		srcR.y = 0;
	}
	else if (color == "Black" || color == "black")
	{
		srcR.y = 230;
	}

}
void Pieces::centerPiece()
{			
	int base = (int)(((windowHeight / 8) * 0.61) / 2);		//adjustment for centering pice on mouse position
	int enlarge = (int)(windowHeight/8);
	int value = (int)((windowHeight / 8) * 0.22);

	if (destR.x >= -base && destR.x <= -base + enlarge)
		destR.x = value;
	else if (destR.x > -base + enlarge && destR.x <= -base + enlarge*2)
		destR.x = value + enlarge;
	else if (destR.x > -base + enlarge * 2 && destR.x <= -base + enlarge * 3)
		destR.x = value + enlarge * 2;
	else if (destR.x > -base + enlarge * 3 && destR.x <= -base + enlarge * 4)
		destR.x = value + enlarge * 3;
	else if (destR.x > -base + enlarge * 4 && destR.x <= -base + enlarge * 5)
		destR.x = value + enlarge * 4;
	else if (destR.x > -base + enlarge * 5 && destR.x <= -base + enlarge * 6)
		destR.x = value + enlarge * 5;
	else if (destR.x > -base + enlarge * 6 && destR.x <= -base + enlarge * 7)
		destR.x = value + enlarge * 6;
	else if (destR.x > -base + enlarge * 7 && destR.x <= -base + enlarge * 8)
		destR.x = value + enlarge * 7;

	base = (windowHeight / 8) / 2;

	if (destR.y >= -base && destR.y <= -base + enlarge)
		destR.y = 0;
	else if (destR.y > -base + enlarge && destR.y <= -base + enlarge * 2)
		destR.y = enlarge;
	else if (destR.y > -base + enlarge * 2 && destR.y <= -base + enlarge * 3)
		destR.y = enlarge * 2;
	else if (destR.y > -base + enlarge * 3 && destR.y <= -base + enlarge * 4)
		destR.y = enlarge * 3;
	else if (destR.y > -base + enlarge * 4 && destR.y <= -base + enlarge * 5)	// 518
		destR.y = enlarge * 4;
	else if (destR.y > -base + enlarge * 5 && destR.y <= -base + enlarge * 6)	// 633
		destR.y = enlarge * 5;
	else if (destR.y > -base + enlarge * 6 && destR.y <= -base + enlarge * 7)
		destR.y = enlarge * 6;
	else if (destR.y > -base + enlarge * 7 && destR.y <= -base + enlarge * 8)
		destR.y = enlarge * 7;
}
void Pieces::setName(std::string naz)
{
	name = naz;
}
void Pieces::setSourcePositionAndSizeAndDestinationSize()
{
	if (name == "Pawn")
	{
		srcR.x = 0;
	}
	else if (name == "Rook")
	{
		srcR.x = 140;
	}
	else if (name == "Knight")
	{
		srcR.x = 280;
	}
	else if (name == "Bishop")
	{
		srcR.x = 420;
	}
	else if (name == "Queen")
	{
		srcR.x = 560;
	}
	else if (name == "King")
	{
		srcR.x = 700;
	}
	else
	{
		std::cout << "Zla nazwa\n";
	}
	set_srcR_x_y(srcR.x, srcR.y);
	set_srcR_w_h();
	set_destR_w_h();
}

Pieces::Pieces()
{
	srcR.w = 140;
	srcR.h = 230;
	destR.w = (int)((windowHeight / 8)*0.61);
	destR.h = windowHeight / 8;
	positionBeforeMove.x = 0;
	positionBeforeMove.y = 0;

	chessTex = TextureManager::LoadTexture("none.png", Program::renderer);
}

bool Pieces::movement_Pawn(Pieces AllPic[32], int& throw_y)
{
	int dest_x = 0;
	int dest_y = 0;
	int before_x = 0;
	int before_y = 0;
	int fieldSize = 0;

	if (checkColor() == "White")
	{
		dest_x = grab_destR_x();
		dest_y = grab_destR_y();
		before_x = positionBeforeMove.x;
		before_y = positionBeforeMove.y;
		fieldSize = moveSize;
	}
	else if (checkColor() == "Black")
	{
		dest_x = -grab_destR_x();
		dest_y = -grab_destR_y();
		before_x = -positionBeforeMove.x;
		before_y = -positionBeforeMove.y;
		fieldSize = moveSize;
	}

	// If figure move backward or side -> Restore old position
	// Else if figure move foward
	if (dest_y <= before_y)
	{
		return false;
	}
	else
	{
		// If move foward by one or two but for the first time
		// Else if the diagonal move
		// Else -> Restore old position
		if ((dest_y == before_y + fieldSize && dest_x == before_x) || (dest_y == before_y + fieldSize * 2 && dest_x == before_x && firstA == false))
		{

			// If move foward by one and come across black piece -> Set wrongMove on true		|| FOR WHITE PIECES
			for (int i = 16; i < 32; i++)
			{
				if (dest_x == AllPic[i].grab_destR_x() && dest_y == AllPic[i].grab_destR_y())
				{
					return false;
				}
			}

			// If move foward by one and come across white piece -> Set wrongMove on true		|| FOR BLACK PIECES
			for (int i = 0; i < 16; i++)
			{
				if (dest_x == -AllPic[i].grab_destR_x() && dest_y == -AllPic[i].grab_destR_y() && checkColor() == "Black") 
				{
					return false;
				}
			}

			// If move foward by two and "jumped" over black piece -> Set wrongMove on true		|| FOR WHITE PIECES
			if (dest_y == before_y + fieldSize * 2)
			{
				for (int i = 0; i < 32; i++)
				{
					if (dest_y - fieldSize == AllPic[i].grab_destR_y() && dest_x == AllPic[i].grab_destR_x())
					{
						return false;
					}
				}
			}

			// If move foward by two and "jumped" over white piece -> Set wrongMove on true		|| FOR BLACK PIECES
			if (dest_y == before_y + fieldSize * 2)
			{
				for (int i = 0; i < 32; i++)
				{
					if (dest_y - fieldSize == -AllPic[i].grab_destR_y() && dest_x == -AllPic[i].grab_destR_x() && checkColor() == "Black")
					{
						return false;
					}
				}
			}

			// If the piece hasn't made a wrong move -> set firstA on true, pass token to black pieces
			firstA = true;
			return true;

		}
		else if ((dest_x == before_x + fieldSize && dest_y == before_y + fieldSize) || (dest_x == before_x - fieldSize && dest_y == before_y + fieldSize))
		{
			if (checkColor() == "White")
			{
				// If yes -> Knock down a piece, Pass token to black pieces, Set firstA on true
				for (int i = 16; i < 32; i++)
				{
					if (dest_x == AllPic[i].grab_destR_x() && dest_y == AllPic[i].grab_destR_y())
					{
						firstA = true;
						AllPic[i].set_destR_w_h((int)((windowHeight / 8) * 0.61 / 2), (int)((windowHeight / 8) / 2));
						AllPic[i].set_destR_x_y(grab_throw_x_White(), throw_y);
						throw_y += (int)((windowHeight / 8) * 0.48);
						return true;
					}
				}
				// If piece don't came across black piece -> Restore old position
				return false;
			}
			else if (checkColor() == "Black")
			{
				// If yes -> Knock down a piece, Pass token to black pieces, Set firstA on true
				for (int i = 0; i < 16; i++)
				{
					if (dest_x == -AllPic[i].grab_destR_x() && dest_y == -AllPic[i].grab_destR_y() && checkColor() == "Black")
					{
						firstA = true;
						AllPic[i].set_destR_w_h((int)((windowHeight / 8) * 0.61 / 2), (int)((windowHeight / 8) / 2));
						AllPic[i].set_destR_x_y(grab_throw_x_Black(), throw_y);
						throw_y += (int)((windowHeight / 8) * 0.48);
						return true;
					}
				}
				// If piece don't came across black piece -> Restore old position
				return false;
			}
			else
			{
				return false;
			}

		}
		else
		{
			return false;
		}
	}
}
bool Pieces::movement_Rook(Pieces AllPic[32], int& throw_y)
{
	// If moves horizontally or vertically
			// Else -> Restore old position
	if (grab_destR_x() == positionBeforeMove.x || grab_destR_y() == positionBeforeMove.y)
	{
		int samePos = 100;						// Variable for storing number of one of 32 pieces,
										// 100 for default because it looks nice and piece with number 100 doesn't exist

		// Check if piece don't came across any other piece horizontally or vertically
		for (int i = 0; i < 32; i++)
		{
			// Up and right move
			for (int cnt = moveSize; cnt <= moveSize * 7; cnt += moveSize)
			{
				if ((positionBeforeMove.x + cnt == AllPic[i].grab_destR_x() && positionBeforeMove.y == AllPic[i].grab_destR_y()) && grab_destR_x() > AllPic[i].grab_destR_x())
				{
					return false;
				}

				if ((positionBeforeMove.y + cnt == AllPic[i].grab_destR_y() && positionBeforeMove.x == AllPic[i].grab_destR_x()) && grab_destR_y() > AllPic[i].grab_destR_y())
				{
					return false;
				}
			}

			// Down and left move
			for (int cnt = moveSize * 7; cnt >= 0; cnt -= moveSize)
			{
				if ((positionBeforeMove.x - cnt == AllPic[i].grab_destR_x() && positionBeforeMove.y == AllPic[i].grab_destR_y()) && grab_destR_x() < AllPic[i].grab_destR_x())
				{
					return false;
				}

				if ((positionBeforeMove.y - cnt == AllPic[i].grab_destR_y() && positionBeforeMove.x == AllPic[i].grab_destR_x()) && grab_destR_y() < AllPic[i].grab_destR_y())
				{
					return false;
				}
			}

			// If the player clicked but did not make a move
			if (positionBeforeMove.x == grab_destR_x() && positionBeforeMove.y == grab_destR_y())
			{
				return false;
			}
		}

		if (checkColor() == "White")
		{
			// Check if any black piece have the same position
			for (int i = 16; i < 32; i++)
			{
				if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
				{
					samePos = i;
				}
			}
		}
		else if (checkColor() == "Black")
		{
			// Check if any white piece have the same position
			for (int i = 0; i < 16; i++)
			{
				if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
				{
					samePos = i;
				}
			}
		}


		// If any piece have the same position and no collision is detected -> Knock down a piece, Pass token to black pieces
		// Else if no elements with the same position are detected and no collision has occurred -> Pass token to black pieces
		if (samePos != 100)
		{
			AllPic[samePos].set_destR_w_h((int)(((windowHeight / 8) * 0.61) / 2), (int)((windowHeight / 8) / 2));
			if (checkColor() == "White")
			{
				AllPic[samePos].set_destR_x_y(grab_throw_x_White(), throw_y);
			}
			else if (checkColor() == "Black")
			{
				AllPic[samePos].set_destR_x_y(grab_throw_x_Black(), throw_y);
			}

			throw_y += (int)((windowHeight / 8) * 0.48);
			return true;
		}
		else if (samePos == 100)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}
bool Pieces::movement_Knight(Pieces AllPic[32], int& throw_y)
{
	int samePos = 100;								// Variable for storing number of one of 32 pieces,
													// 100 for default because it looks nice and piece with number 100 doesn't exist
	if (checkColor() == "White")
	{
		// Check if any black piece have the same position
		for (int i = 16; i < 32; i++)
		{
			if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
			{
				samePos = i;
			}
		}
	}
	else if (checkColor() == "Black")
	{
		// Check if any black piece have the same position
		for (int i = 0; i < 16; i++)
		{
			if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
			{
				samePos = i;
			}
		}
	}


	// 1. If two up one right or one left				2. If two down one right or one left
	// 3. If two to the right and one down or up		4. If two to the left and one down or up
	if (grab_destR_y() == positionBeforeMove.y + moveSize * 2 && (grab_destR_x() == positionBeforeMove.x + moveSize || grab_destR_x() == positionBeforeMove.x - moveSize) ||
		grab_destR_y() == positionBeforeMove.y - moveSize * 2 && (grab_destR_x() == positionBeforeMove.x + moveSize || grab_destR_x() == positionBeforeMove.x - moveSize) ||
		grab_destR_x() == positionBeforeMove.x + moveSize * 2 && (grab_destR_y() == positionBeforeMove.y + moveSize || grab_destR_y() == positionBeforeMove.y - moveSize) ||
		grab_destR_x() == positionBeforeMove.x - moveSize * 2 && (grab_destR_y() == positionBeforeMove.y + moveSize || grab_destR_y() == positionBeforeMove.y - moveSize))
	{
		// If the piece hasn't made a wrong move and piece is detected -> Knock down a piece, Pass token to black pieces
		// Else If the piece hasn't made a wrong move -> Pass token to black pieces
		// If the pawn has not moved correctly -> Restore old position
		if (samePos != 100)
		{
			AllPic[samePos].set_destR_w_h((int)(((windowHeight / 8) * 0.61) / 2), (int)((windowHeight / 8) / 2));
			if (checkColor() == "White")
			{
				AllPic[samePos].set_destR_x_y(grab_throw_x_White(), throw_y);
			}
			else if(checkColor() == "Black")
			{
				AllPic[samePos].set_destR_x_y(grab_throw_x_Black(), throw_y);
			}
			throw_y += (int)((windowHeight / 8) * 0.48);
			return true;
		}
		else if (samePos == 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Pieces::movement_Bishop(Pieces AllPic[32], int& throw_y)
{
	int samePos = 100;
	int biasMove = 0;

	// Check if piece move diagonally and set one of possible movements from 1 to 4		(If movement is not diagonally then set biasMove to 0)
	// 1. Right down			2. Left up
	// 3. Right up				4. Left down
	for (int bias = moveSize; bias <= moveSize * 7; bias += moveSize)
	{
		if (grab_destR_x() == positionBeforeMove.x + bias && grab_destR_y() == positionBeforeMove.y + bias)
		{
			biasMove = 1;
		}
		else if (grab_destR_x() == positionBeforeMove.x - bias && grab_destR_y() == positionBeforeMove.y - bias)
		{
			biasMove = 2;
		}
		else if (grab_destR_x() == positionBeforeMove.x + bias && grab_destR_y() == positionBeforeMove.y - bias)
		{
			biasMove = 3;
		}
		else if (grab_destR_x() == positionBeforeMove.x - bias && grab_destR_y() == positionBeforeMove.y + bias)
		{
			biasMove = 4;
		}
	}

	// If from pos.x to dest.x and from pos.y to dest.y there was a Piece (but excluding this piece) -> set biasMove to 0
	if (biasMove == 1)
	{
		for (int srcX = positionBeforeMove.x, srcY = positionBeforeMove.y, destX = grab_destR_x(), destY = grab_destR_y(); srcX + moveSize <= destX && srcY + moveSize <= destY; srcX += moveSize, srcY += moveSize)
		{
			for (int i = 0; i < 32; i++)
			{
				//std::cout << "\nPionek[" << i << "]: " << std::endl;
				//std::cout << "AllPic[" << i << "].pos.x: " << AllPic[i].grab_destR_x() << "\nAllPic[" << i << "].pos.y: " << AllPic[i].grab_destR_y();
				//std::cout << "\nsrcX: " << srcX + moveSize << "\nsrcY: " << srcY + moveSize << std::endl;
				if (AllPic[i].grab_destR_x() == srcX && AllPic[i].grab_destR_y() == srcY)
				{
					biasMove = 0;
				}
			}
		}
	}
	else if (biasMove == 2)
	{
		for (int srcX = positionBeforeMove.x, srcY = positionBeforeMove.y, destX = grab_destR_x(), destY = grab_destR_y(); srcX - moveSize >= destX && srcY - moveSize >= destY; srcX -= moveSize, srcY -= moveSize)
		{
			for (int i = 0; i < 32; i++)
			{
				if (AllPic[i].grab_destR_x() == srcX && AllPic[i].grab_destR_y() == srcY)
				{
					biasMove = 0;
				}
			}
		}
	}
	else if (biasMove == 3)
	{
		for (int srcX = positionBeforeMove.x, srcY = positionBeforeMove.y, destX = grab_destR_x(), destY = grab_destR_y(); srcX + moveSize <= destX && srcY - moveSize >= destY; srcX += moveSize, srcY -= moveSize)
		{
			for (int i = 0; i < 32; i++)
			{
				if (AllPic[i].grab_destR_x() == srcX && AllPic[i].grab_destR_y() == srcY)
				{
					biasMove = 0;
				}
			}
		}
	}
	else if (biasMove == 4)
	{
		for (int srcX = positionBeforeMove.x, srcY = positionBeforeMove.y, destX = grab_destR_x(), destY = grab_destR_y(); srcX - moveSize >= destX && srcY + moveSize <= destY; srcX -= moveSize, srcY += moveSize)
		{
			for (int i = 0; i < 32; i++)
			{
				if (AllPic[i].grab_destR_x() == srcX && AllPic[i].grab_destR_y() == srcY)
				{
					biasMove = 0;
				}
			}
		}
	}
	
	if (checkColor() == "White")
	{
		// Check if any black piece have the same position
		for (int i = 16; i < 32; i++)
		{
			if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
			{
				samePos = i;
			}
		}
	}
	else if (checkColor() == "Black")
	{
		// Check if any white piece have the same position
		for (int i = 0; i < 16; i++)
		{
			if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
			{
				samePos = i;
			}
		}
	}


	// If piece didn't make diagonnaly move -> Restore old position
	// If this piece did diagonally move and another piece is detected -> Knock down a piece, Pass token to black pieces
	// If this piece did diagonally move -> Pass token to black pieces
	if (biasMove == 0)
	{
		return false;
	}
	else if (biasMove != 0 && samePos != 100)
	{
		AllPic[samePos].set_destR_w_h((int)((windowHeight / 8) * 0.61) / 2, (int)((windowHeight / 8) / 2));
		if (checkColor() == "White")
		{
			AllPic[samePos].set_destR_x_y(grab_throw_x_White(), throw_y);
		}
		else if (checkColor() == "Black")
		{
			AllPic[samePos].set_destR_x_y(grab_throw_x_Black(), throw_y);
		}
		throw_y += (int)((windowHeight / 8) * 0.48);
		return true;
	}
	else if (biasMove != 0 && samePos == 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Pieces::movement_Queen(Pieces AllPic[32], int& throw_y)
{
	if (movement_Bishop(AllPic,throw_y) == true)
	{
		return true;
	}
	else if (movement_Rook(AllPic, throw_y) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Pieces::movement_King(Pieces AllPic[32], int& throw_y)
{
	// If player is dumb and move on the same place -> return false
	// Else if the piece moved one space in any direction
	// Else -> Restore old position
	if (grab_destR_x() == positionBeforeMove.x && grab_destR_y() == positionBeforeMove.y)
	{
		return false;
	}
	else if ((grab_destR_x() == positionBeforeMove.x + moveSize || grab_destR_x() == positionBeforeMove.x - moveSize || grab_destR_x() == positionBeforeMove.x) && (grab_destR_y() == positionBeforeMove.y + moveSize || grab_destR_y() == positionBeforeMove.y - moveSize || grab_destR_y() == positionBeforeMove.y))
	{
		int samePos = 100;

		if (checkColor() == "White")
		{
			// Check if any black piece have the same position
			for (int i = 16; i < 32; i++)
			{
				if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
				{
					samePos = i;
				}
			}
		}
		else if (checkColor() == "Black")
		{
			// Check if any white piece have the same position
			for (int i = 0; i < 16; i++)
			{
				if (grab_destR_x() == AllPic[i].grab_destR_x() && grab_destR_y() == AllPic[i].grab_destR_y())
				{
					samePos = i;
				}
			}
		}

		// If any piece have the same position -> Knock down a piece, Pass token to black pieces
		// Else if move is correct but no elements with the same position are detected
		if (samePos != 100)
		{
			AllPic[samePos].set_destR_w_h((int)(((windowHeight / 8) * 0.61) / 2), (int)((windowHeight / 8) / 2));
			if (checkColor() == "White")
			{
				AllPic[samePos].set_destR_x_y(grab_throw_x_White(), throw_y);
			}
			else if (checkColor() == "Black")
			{
				AllPic[samePos].set_destR_x_y(grab_throw_x_Black(), throw_y);
			}

			throw_y += (int)((windowHeight / 8) * 0.48);
			return true;
		}
		else if (samePos == 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void handlingPieceMovement(Pieces& Pic, Pieces AllPic[32])
{
	static int moveToken = 0;								// Turn-based figure movement 0/1
	bool wrongColorMove = false;							// If moving a figure to a figure with the same color
	static std::string tokenColor = "none";

	// Reset token after pawn promotion
	if (moveToken == 3 && tokenColor == "White")
	{
		moveToken = 1;
	}
	else if (moveToken == 3 && tokenColor == "Black")
	{
		moveToken = 0;
	}

	// Check the color of the figure and Token
	if (Pic.checkColor() == "White" && moveToken == 0)
	{
		// Set a place for white broken pieces									
		static int throw_y = 0;

		// Check if white piece has moved to another white piece
		for (int i = 0; i < 16; i++)							
		{
			if ((Pic.grab_destR_x() == AllPic[i].grab_destR_x() && Pic.grab_destR_y() == AllPic[i].grab_destR_y()) && Pic.grab_PieceNumber() != AllPic[i].grab_PieceNumber())
			{
				Pic.restoreOldPosition();
				wrongColorMove = true;
			}
		}

		// If don't moved a white figure on a white figure
		if (wrongColorMove == false)										
		{
			// Check the figure name
			if		(Pic.checkName() == "Pawn"	)		
			{
				if (Pic.movement_Pawn(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					if (Pic.grab_destR_y() == moveSize * 7)		// For Pawn promotion
					{
						moveToken = 3;
						tokenColor = "White";
					}
					else
					{
						moveToken = 1;
					}
				}
			}
			else if (Pic.checkName() == "Rook"	)
			{
				if (Pic.movement_Rook(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 1;
				}
			}
			else if (Pic.checkName() == "Knight")
			{
				if (Pic.movement_Knight(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 1;
				}
			}
			else if (Pic.checkName() == "Bishop")
			{
				if (Pic.movement_Bishop(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 1;
				}
			}
			else if (Pic.checkName() == "Queen")
			{
				if (Pic.movement_Queen(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 1;
				}
			}
			else if (Pic.checkName() == "King"	)	
			{
				if (Pic.movement_King(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 1;
				}
			}

			// If moving a figure off the board then restore old position
			if (Pic.grab_destR_x() > ((moveSize*7) + ((windowHeight/8)*0,22)+7))
			{
				Pic.restoreOldPosition();
				moveToken = 0;
			}
		}

	}
	else if (Pic.checkColor() == "Black" && moveToken == 1)
	{
		// Set a place for black broken pieces
		static int throw_y = 0;

		// Check if black piece has moved to another black piece
		for (int i = 16; i < 32; i++)
		{
			if ((Pic.grab_destR_x() == AllPic[i].grab_destR_x() && Pic.grab_destR_y() == AllPic[i].grab_destR_y()) && Pic.grab_PieceNumber() != AllPic[i].grab_PieceNumber())
			{
				Pic.restoreOldPosition();
				wrongColorMove = true;
			}
		}

		// If don't moved a black figure on a black figure
		if (wrongColorMove == false)										
		{
			// Check the figure name
			if		(Pic.checkName() == "Pawn"	)
			{
				if (Pic.movement_Pawn(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					if (Pic.grab_destR_y() == moveSize * 7)		// For Pawn promotion
					{
						moveToken = 3;
						tokenColor = "White";
					}
					else
					{
						moveToken = 0;
					}
				}
			}
			else if (Pic.checkName() == "Rook"	)					// Wieza
			{
				if (Pic.movement_Rook(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 0;
				}
			}
			else if (Pic.checkName() == "Knight")
			{
				if (Pic.movement_Knight(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 0;
				}
			}
			else if (Pic.checkName() == "Bishop")
			{
				if (Pic.movement_Bishop(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 0;
				}
			}
			else if (Pic.checkName() == "Queen"	)				// Krolowa
			{
				if (Pic.movement_Queen(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 0;
				}
			}
			else if (Pic.checkName() == "King"	)	
			{
				if (Pic.movement_King(AllPic, throw_y) == false)
				{
					Pic.restoreOldPosition();
				}
				else
				{
					moveToken = 0;
				}
			}

			// If moving a figure off the board then restore old position
			if (Pic.grab_destR_x() > ((moveSize * 7) + ((windowHeight / 8) * 0, 22) + 7))
			{
				std::cout << "co";
				Pic.restoreOldPosition();
				moveToken = 1;
			}
		}
	}
	else
	{
		// If player want to make 2 moves, restore old piece position
		if (moveToken == 1)
		{
			std::cout << "\nRuch Czarnego\n";
		}
		else
		{
			std::cout << "\nRuch Bialego\n";
		}
		
		Pic.restoreOldPosition();
	}
}