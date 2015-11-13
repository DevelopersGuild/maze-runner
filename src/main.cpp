#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
const int ROW = 9;
const int COL = 11;
/*
void reset(sf::Sprite& cookieSprite)
{
cookieSprite.setPosition(rand() % 750, rand() % 550);
}
*/


bool handleWallCollision(sf::Sprite *tileArr, sf::Sprite pacmanSprite, int counter)
{
	for (int i = 0; i < counter; i++)
	{
		if (overlap(tileArr[i], pacmanSprite))
			return true; // there is collision
	}
		return false;
}

void handleEvent(sf::RenderWindow& window, sf::Event &event)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}


//Pacman
void update(sf::Sprite* tileArr, sf::Sprite& PacmanSprite, sf::Event event, int counter)
{

	if (event.key.code == sf::Keyboard::Left) //keeps it moving even though key is not pressed
	{
		if (handleWallCollision(tileArr, PacmanSprite, counter))
		{
			PacmanSprite.move(0, 0);
		}
		else
			PacmanSprite.move(-1, 0);
	}
	else if ((event.key.code == sf::Keyboard::Right))
	{
		if (handleWallCollision(tileArr, PacmanSprite, counter))
		{
			PacmanSprite.move(0, 0);

		}
		else
			PacmanSprite.move(1, 0);
	}
	else if ((event.key.code == sf::Keyboard::Up))
	{
		if (handleWallCollision(tileArr, PacmanSprite, counter))
		{
			PacmanSprite.move(0, 0);
		}
		else
			PacmanSprite.move(0, -1);
	}
	else if ((event.key.code == sf::Keyboard::Down))
	{
		if (handleWallCollision(tileArr, PacmanSprite, counter))
		{
			PacmanSprite.move(0, 0);

		}
		else
			PacmanSprite.move(0, 1);
	}
}

void draw(sf::RenderWindow& window, sf::Sprite pacmanSprite, int counter)
{
	window.draw(pacmanSprite);
	window.display();
}


void drawWall(sf::RenderWindow& window, bool arr[][COL], sf::Sprite *tileArr, sf::Texture wallTexture)
{
	int i = 0;

	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (arr[r][c] == true)
			{
				tileArr[i] = sf::Sprite(wallTexture);
				tileArr[i].setPosition(c * 64, r * 64);
				window.draw(tileArr[i]);
				i++;
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Works!");
	window.setVerticalSyncEnabled(true);

	sf::Texture wallTexture;
	wallTexture.loadFromFile(resourcePath() + "assets/wall.png");

	sf::Texture pacmanTexture;
	pacmanTexture.loadFromFile(resourcePath() + "assets/pacman.png");
	sf::Sprite pacmanSprite(pacmanTexture);
	pacmanSprite.setOrigin(32, 32);
	pacmanSprite.setPosition(0 + 32+ 16, 4 * 64 + 32+16);


	//this would be better if we can call the inputfile.
	// map array beta
	// please finish design the map so I can finish this!
	int map[9][11] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	//bool array
	int counter = 0;
	bool wall[9][11];
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map[r][c] == 1)
			{
				wall[r][c] = true; // there is a wall
				counter++;
			}
			if (map[r][c] == 0)
				wall[r][c] = false; // blank
		}
	}

	sf::Sprite *tileArray = new sf::Sprite[counter];

	while (window.isOpen())
	{
		window.clear();

		sf::Event event;
		handleEvent(window, event);

		update(tileArray, pacmanSprite, event, counter);
		
		drawWall(window, wall, tileArray, wallTexture);
		draw(window, pacmanSprite, counter);

	}
	return 0;
}