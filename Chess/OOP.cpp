#ifndef OOP
#define OOP

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class Coordinates 
{
public:
	int x, y;
};

class Figure // x32
{
public:
	//int x, y; // coordinates
	Coordinates pos;
	std::vector<Coordinates> figureReadyMove;
	bool color; // true is white, false is black
	int index;


	Figure() {}

	Figure(int index, int x, int y, bool color)
	{
		this->index = index;
		this->pos.x = x;
		this->pos.y = y;
		this->color = color;
	}

	//virtual void update() {}
};

//class Pawn : public Figure // x16...
//{
//public:
//	/*void update()
//	{
//		figureReadyMove.clear();
//		if (color)
//		{
//			if (pos.y == 4) 
//		}
//		else
//		{
//		
//		}
//	}*/
//};
//
//class Knight : public Figure
//{
//public:
//
//};
//
//class Bishop : public Figure
//{
//public:
//
//};
//
//class Rook : public Figure
//{
//public:
//
//};
//
//class Queen : public Figure
//{
//public:
//
//};
//
//class King : public Figure
//{
//public:
//
//};

class Field // x64(8x8) info attack
{
public:
	Figure* figure;
	// int x, y; // coordinates
	Coordinates pos;
	std::vector<Figure> listFigures; // all figures that attack this field

	Field() {}

	Field(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}
};

class Map
{
public:
	Field field[8][8];

	void check() 
	{

	}

	void updateone(Figure* figure)
	{
	
	}

	void update()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (field[i][j].figure) updateone(field[i][j].figure);
			}
		}
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
	//Field map[8][8];
	Map map;
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
				this->map.field[i][j] = map[i][j];
			}
		}
	}
};


#endif OOP