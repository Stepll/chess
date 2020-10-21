#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
//#include "Connector.hpp"

using namespace sf;

int size = 56;

Sprite figure[32];
int figureindex[32];

int board[8][8] =
{-3,-4,-5,-2,-1,-5,-4,-3,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  3, 4, 5, 2, 1, 5, 4, 3};

int boardinfo[8][8];

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



void move(std::string str)
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	if (oldPos != newPos)
	{
		for (int i = 0; i < 32; i++)
			if (figure[i].getPosition() == newPos) figure[i].setPosition(-50, -50);

		for (int i = 0; i < 32; i++)
			if (figure[i].getPosition() == oldPos) figure[i].setPosition(newPos);
	}
}

std::string position = "";

void loadPosition()
{
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			figure[k].setTextureRect(IntRect(size * x, size * y, size, size));
			figure[k].setPosition(size * j, size * i);
			figureindex[k] = board[i][j];
			k++;
		}
	}

	for (int i = 0; i < position.length(); i += 5)
	{
		move(position.substr(i, 4));
	}
}

int current = 0;

void scan() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardinfo[i][j] = 0;
	for (int i = 0; i < 32; i++)
	{
		int xx = figure[i].getPosition().x / size;
		int yy = figure[i].getPosition().y / size;
		boardinfo[yy][xx] = figureindex[i];
	}
}

bool check(int index, Vector2f oldpos, Vector2f newpos)
{
	std::cout << oldpos.x/size << " " << oldpos.y/size << std::endl;
	std::cout << newpos.x/size << " " << newpos.y/size << std::endl;
	int oldx = oldpos.x / size;
	int oldy = oldpos.y / size;
	int newx = newpos.x / size;
	int newy = newpos.y / size;
	
	if (index == 6) // ����� �����
	{
		if ((oldy - newy == 1) && (oldx == newx) && (boardinfo[newy][newx] == 0)) { /*std::cout << boardinfo[newy][newx] << std::endl;*/ return true; } // ��� ������ � ����� ������ �� ����
		if ((oldy == 6) && (newy == 4) && (oldx == newx) && (boardinfo[newy][newx] == 0) && (boardinfo[newy + 1][newx] == 0)) { return true; } // ��������� ��� �� 2 � ����� �� ���� � �� �����������
		if ((oldy - newy == 1) && (abs(oldx - newx) == 1) && (boardinfo[newy][newx] < 0)) { return true; } // ������� �� ��������� ���� ��� ������ ������� �����
	}
	if (index == 3) // ����� �����
	{
		if (oldx == newx) // ��������� �� y
		{
			if (newy > oldy) // ����
			{
				for (int i = oldy + 1; i < newy; i++)
					if (boardinfo[i][oldx] != 0) return false;
				if (boardinfo[newy][oldx] <= 0) return true;
				return false;
			}
			if (newy < oldy) // �����
			{
				for (int i = oldy - 1; i > newy; i--)
					if (boardinfo[i][oldx] != 0) return false;
				if (boardinfo[newy][oldx] <= 0) return true;
				return false;
			}
		}
		if (oldy == newy) // ��������� �� x
		{
			if (newx > oldx) // ������
			{
				for (int i = oldx + 1; i < newx; i++)
					if (boardinfo[oldy][i] != 0) return false;
				if (boardinfo[newy][newx] <= 0) return true;
				return false;
			}
			if (newx < oldx) // �����
			{
				for (int i = oldx - 1; i > newx; i--)
					if (boardinfo[oldy][i] != 0) return false;
				if (boardinfo[newy][newx] <= 0) return true;
				return false;
			}
		}
	}
	if (index == 4 && boardinfo[newy][newx] <= 0) // ���� // 8 ���������
	{
		if ((newx - oldx == 1) && (abs(newy - oldy) == 2)) return true;
		if ((newx - oldx == -1) && (abs(newy - oldy) == 2)) return true;
		if ((newx - oldx == 2) && (abs(newy - oldy) == 1)) return true;
		if ((newx - oldx == -2) && (abs(newy - oldy) == 1)) return true;
		return false;
	}
	if (index == 5 && boardinfo[newy][newx] <= 0) { // ����
		if (oldx + oldy == newx + newy) // x+ y+ or x- y-
		{
			if (newx > oldx)
			{
				int j = oldy - 1;
				for (int i = oldx + 1; i < newx; i++, j--)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
			if (newx < oldx)
			{
				int j = oldy + 1;
				for (int i = oldx - 1; i > newx; i--, j++)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
		}
		if (abs(oldx - oldy) == abs(newx - newy)) // x- y+ or x+ y-
		{
			if (newx > oldx)
			{
				int j = oldy + 1;
				for (int i = oldx + 1; i < newx; i++, j++)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
			if (newx < oldx)
			{
				int j = oldy - 1;
				for (int i = oldx - 1; i > newx; i--, j--)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
		}
	}
	if (index == 2 && boardinfo[newy][newx] <= 0) // ��������
	{
		if (oldx == newx) // ��������� �� y
		{
			if (newy > oldy) // ����
			{
				for (int i = oldy + 1; i < newy; i++)
					if (boardinfo[i][oldx] != 0) return false;
				if (boardinfo[newy][oldx] <= 0) return true;
				return false;
			}
			if (newy < oldy) // �����
			{
				for (int i = oldy - 1; i > newy; i--)
					if (boardinfo[i][oldx] != 0) return false;
				if (boardinfo[newy][oldx] <= 0) return true;
				return false;
			}
		}
		if (oldy == newy) // ��������� �� x
		{
			if (newx > oldx) // ������
			{
				for (int i = oldx + 1; i < newx; i++)
					if (boardinfo[oldy][i] != 0) return false;
				if (boardinfo[newy][newx] <= 0) return true;
				return false;
			}
			if (newx < oldx) // �����
			{
				for (int i = oldx - 1; i > newx; i--)
					if (boardinfo[oldy][i] != 0) return false;
				if (boardinfo[newy][newx] <= 0) return true;
				return false;
			}
		}
		if (oldx + oldy == newx + newy) // x+ y+ or x- y-
		{
			if (newx > oldx)
			{
				int j = oldy - 1;
				for (int i = oldx + 1; i < newx; i++, j--)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
			if (newx < oldx)
			{
				int j = oldy + 1;
				for (int i = oldx - 1; i > newx; i--, j++)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
		}
		if (abs(oldx - oldy) == abs(newx - newy)) // x- y+ or x+ y-
		{
			if (newx > oldx)
			{
				int j = oldy + 1;
				for (int i = oldx + 1; i < newx; i++, j++)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
			if (newx < oldx)
			{
				int j = oldy - 1;
				for (int i = oldx - 1; i > newx; i--, j--)
					if (boardinfo[j][i] != 0) return false;
				return true;
			}
		} // �������� �� ��������
	}
	if (index == 1 && boardinfo[newy][newx] <= 0) // �����b
	{
		if ((abs(oldx - newx) <= 1) && ((abs(oldy - newy) <= 1))) return true;
	}
	
	return false;
}



int main()
{
	
	RenderWindow window(VideoMode(453, 453), "chess");

	Texture t1, t2;
	t1.loadFromFile("images/chess.png");
	t2.loadFromFile("images/bg.png");

	Sprite sBoard(t2);

	for (int i = 0; i < 32; i++) figure[i].setTexture(t1);

	loadPosition();

	int current = 0;
	Vector2f oldPos,newPos;
	std::string str;
	bool isMove = false;
	float dx = 0, dy = 0;
	int n;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if ((event.key.code == Keyboard::Z) && (position.length() > 5))
				{
					position.erase(position.length() - 6, 5);
					loadPosition();
				}
			}


			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					scan();
					for (int i = 0; i < 32; i++)
						if (figure[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true;
							n = i;
							dx = pos.x - figure[i].getPosition().x;
							dy = pos.y - figure[i].getPosition().y;
							oldPos = figure[i].getPosition();
							current = figureindex[i];
							//std::cout << figureindex[i] << std::endl;
						}
					
				}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = figure[n].getPosition() + Vector2f(size / 2, size / 2);
					Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
					
					//std::cout << newPos.x << " " << newPos.y << std::endl;
					if (check(current, oldPos, newPos)) { std::cout << "nice" << std::endl; }
					str = toChessNote(oldPos) + toChessNote(newPos);
					move(str);
					position += str + " ";
					std::cout << str << std::endl;
					figure[n].setPosition(newPos);
					//scan();
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							std::cout << boardinfo[i][j];
						}
						std::cout << std::endl;
					}
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			str = "e2e4";

			oldPos = toCoord(str[0], str[1]);
			newPos = toCoord(str[2], str[3]);

			for (int i = 0; i < 32; i++) if (figure[i].getPosition() == oldPos) n = i;
		
			for (int k = 0; k < 50; k++)
			{
				Vector2f p = newPos - oldPos;
				figure[n].move(p.x / 50, p.y / 50);
				window.draw(sBoard);
				for (int i = 0; i < 32; i++) window.draw(figure[i]); window.draw(figure[n]);
				window.display();
			}

			move(str);
			position += str + "";
			std::cout << str << std::endl;
			figure[n].setPosition(newPos);
		
		}


		if (isMove) figure[n].setPosition(pos.x - dx, pos.y - dy);

		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < 32; i++) window.draw(figure[i]);
		window.display();
	}
	return 0;
}