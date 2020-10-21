#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace sf;

int size = 56;

Sprite figure[32];

int board[8][8] =
{-3,-4,-5,-2,-1,-5,-4,-3,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  3, 4, 5, 2, 1, 5, 4, 3};

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

int yDeath = 0;
int xDeath = 450;

void move(std::string str)
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	if (oldPos != newPos)
	{
		for (int i = 0; i < 32; i++)
			if (figure[i].getPosition() == newPos)
			{
				figure[i].setPosition(xDeath, yDeath);
				yDeath += 48;
				if (yDeath >= 400)
				{
					xDeath += 48;
					yDeath = 0;
				}
			}

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
			k++;
		}
	}

	for (int i = 0; i < position.length(); i += 5)
	{
		move(position.substr(i, 4));
	}
}

int main()
{
	
	RenderWindow window(VideoMode(650, 453), "chess");

	Texture t1, t2;
	t1.loadFromFile("images/chess.png");
	t2.loadFromFile("images/bg.png");

	Sprite sBoard(t2);

	for (int i = 0; i < 32; i++) figure[i].setTexture(t1);

	loadPosition();
	
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
					for (int i = 0; i < 32; i++)
					if (figure[i].getGlobalBounds().contains(pos.x, pos.y))
					{
						isMove = true;
						n = i;
						dx = pos.x - figure[i].getPosition().x;
						dy = pos.y - figure[i].getPosition().y;
						oldPos = figure[i].getPosition();
					}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
					Vector2f p = figure[n].getPosition() + Vector2f(size / 2, size / 2);
					Vector2f newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
					str = toChessNote(oldPos) + toChessNote(newPos);
					move(str);
					position += str + " ";
					std::cout << str << std::endl;
					figure[n].setPosition(newPos);
				}
		}

		if (isMove) figure[n].setPosition(pos.x - dx, pos.y - dy);

		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < 32; i++) window.draw(figure[i]);
		window.display();
	}
	return 0;
}