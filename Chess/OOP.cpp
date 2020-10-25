#ifndef OOP
#define OOP

#include <SFML/Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;

class Coordinates 
{
public:
	int x, y;

	Coordinates() {}

	Coordinates(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

class Figure // x32
{
public:
	Coordinates pos;
	Sprite texture;
	std::vector<Coordinates> figureReadyMove;
	bool color = true; // true is white, false is black
	int index = 0;


	Figure() {}

	Figure(int index, int x, int y, bool color)
	{
		this->index = index;
		this->pos.x = x;
		this->pos.y = y;
		this->color = color;
	}

	int getindex()
	{
		return index;
	}
};


class Field // x64(8x8) info attack
{
public:
	Figure figure;
	// int x, y; // coordinates
	Coordinates pos;
	std::vector<Figure> listFigures; // all figures that attack this field

	Field() {}

	Field(int x, int y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}

	Field(int x, int y, Figure figure) : Field(x, y)
	{
		this->figure = figure;
	}
};

class Map
{
public:
	Field field[8][8];

	Map()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				field[i][j] = *new Field();
			}
		}
	}

	void check() 
	{

	}

	void updateone(Figure figure) // Field.listFigures and  Figure.figureReadyMove
	{
		if (figure.index == 6)
		{
			if ((figure.color) && (figure.pos.y == 6))
			{
				
				if (((&field[figure.pos.x][figure.pos.y - 2].figure) &&
					(field[figure.pos.x][figure.pos.y - 2].figure.color != figure.color) &&
					(!&field[figure.pos.x][figure.pos.y - 1].figure)) ||
					((!&field[figure.pos.x][figure.pos.y - 2].figure) &&
						(!&field[figure.pos.x][figure.pos.y - 1].figure)))
				{
					Coordinates tmp = *new Coordinates(figure.pos.x, figure.pos.y - 1);
					figure.figureReadyMove.push_back(tmp);
				}
				
			}
			if (figure.color)
			{
				if (((&field[figure.pos.x][figure.pos.y - 1].figure) &&
					(field[figure.pos.x][figure.pos.y - 1].figure.color != figure.color)) ||
					(!&field[figure.pos.x][figure.pos.y - 1].figure))
				{
					Coordinates tmp = *new Coordinates(figure.pos.x, figure.pos.y - 1);
					figure.figureReadyMove.push_back(tmp);
				}
				if (((&field[figure.pos.x][figure.pos.y - 1].figure) &&
					(field[figure.pos.x][figure.pos.y - 1].figure.color != figure.color)) ||
					(!&field[figure.pos.x][figure.pos.y - 1].figure))
				{
					Coordinates tmp = *new Coordinates(figure.pos.x, figure.pos.y - 1);
					figure.figureReadyMove.push_back(tmp);
				}
			}
		}
	}

	void update()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (&field[i][j].figure) updateone(field[i][j].figure);
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
	Map map;
	//Figure Figures[32]; //mb
	Player white, black;
	std::string position;
	int size;

	Board(Player white, Player black, Field field[8][8], int size)
	{
		position = "e2e2 ";
		Map map = *new Map();
		this->white = white;
		this->black = black;
		this->size = size;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				this->map.field[i][j] = field[i][j];
			}
		}
	}

	void swichStep()
	{
		black.step = !black.step;
		white.step = !white.step;
	}

	std::string toChessNote(Vector2f p)
	{
		std::string s = "";
		s += char(p.x / size + 97);
		s += char(7 - p.y / size + 49);
		return s;
	}

	Vector2f toCoord(char a, char b)
	{
		int x = int(a) - 97;
		int y = 7 - int(b) + 49;
		return Vector2f(x * size, y * size);
	}

	void move(std::string str) // oop ready
	{
		Vector2f oldPos = toCoord(str[0], str[1]);
		Vector2f newPos = toCoord(str[2], str[3]);

		if (oldPos != newPos)
		{
			for (int i = 0; i < 16; i++)
			{
				if (white.Figures[i].texture.getPosition() == newPos) white.Figures[i].texture.setPosition(-50, -50);
				if (black.Figures[i].texture.getPosition() == newPos) black.Figures[i].texture.setPosition(-50, -50);
			}


			for (int i = 0; i < 16; i++)
			{
				if (white.Figures[i].texture.getPosition() == oldPos) white.Figures[i].texture.setPosition(newPos);
				if (black.Figures[i].texture.getPosition() == oldPos) black.Figures[i].texture.setPosition(newPos);
			}
		}
	}


	void loadPosition() // opp ready
	{
		int k = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				std::cout << i << " " << j << std::endl;
				int n = map.field[i][j].figure.getindex();
				if (!n) continue;
				int x = n - 1;
				int y = map.field[i][j].figure.color ? 1 : 0;
				map.field[i][j].figure.texture.setTextureRect(IntRect(size * x, size * y, size, size));
				map.field[i][j].figure.texture.setPosition(size * j, size * i);
				k++;
			}
		}

		for (int i = 0; i < position.length(); i += 5)
		{
			move(position.substr(i, 4));
		}
	}
};


#endif OOP