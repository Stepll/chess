#ifndef OOP
#define OOP

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class Figure // x32
{
public:
	int x, y; // coordinates
	bool color; // true is white, false is black

	Figure() {}

	Figure(int x, int y, bool color)
	{
		this->x = x;
		this->y = y;
		this->color = color;
	}
};

class Pawn : public Figure // x16...
{
public:

};

class Field // x64(8x8) info attack
{
public:
	int x, y; // coordinates
	std::vector<Figure> listFigures; // all figures that attack this field

	Field() {}

	Field(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

class Player // x2
{
public:
	bool step; // true is current player step
	bool color;
	Figure Figures[16]; // all figures this player

	Player() {}

	Player(bool color, Figure Figures[16])
	{
		this->color = color;
		this->step = color; // white have first step
		for (int i = 0; i < 16; i++)
		{
			this->Figures[i] = Figures[i];
		}
	}
};
class Board // x1
{
public:
	Field map[8][8];
	//Figure Figures[32]; //mb
	Player white, black;

	Board(Player white, Player black, Field map[8][8])
	{
		this->white = white;
		this->black = black;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				this->map[i][j] = map[i][j];
			}
		}
	}
};


#endif OOP