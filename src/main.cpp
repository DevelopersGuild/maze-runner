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

void handleWallCollision(sf::Sprite *tileArr, sf::Sprite& PacmanSprite)
{
if (overlap(tileArr, PacmanSprite))
{
	

//eaten++;
//reset(cookieSprite);
//charizardSprite.scale(1.1, 1.1);
}
}
*/
void handleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}
/* //Pacman
void update(sf::Sprite& PacmanSprite, bool arr[][COL])
{
if (event.key.code == sf::Keyboard::Left) //keeps it moving even though key is not pressed
{
	PacmanSprite.move(0.05, 0);
}
else if ((event.key.code == sf::Keyboard::Right))
{
	PacmanSprite.move(0.05, 0);
}
else if ((event.key.code == sf::Keyboard::Up)
{
	PacmanSprite.move(0, -0.05);
}
else if ((event.key.code == sf::Keyboard::Down)
{
	PacmanSprite.move(0, 0.05);
}

}
*/
void draw(sf::RenderWindow& window)
{
	window.clear();
	
	window.display();
}


void drawWall(sf::RenderWindow& window, bool arr[][COL], sf::Sprite *tileArr, sf::Texture wallTexture)
{
	int i = 0;
	//insert wall sprite
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (arr[r][c] == true)
			{
				tileArr[i] = sf::Sprite(wallTexture);
				tileArr[i].setPosition(r * 64, c * 64); 
				window.draw(tileArr[i]);
				// place the sprite
				// this need to be the new sprite every time.
				// use vector
				i++;
			}
		}
	}
	window.display();

}

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Works!");
	window.setVerticalSyncEnabled(true);

	sf::Texture wallTexture;
	wallTexture.loadFromFile(resourcePath() + "assets/wall.png");

	sf::Sprite *tileArray = NULL;

	//this would be better if we can call the inputfile.
	// map array beta
	// please finish design the map so I can finish this!
	int map[9][11] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
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

	tileArray = new sf::Sprite[counter];

	drawWall(window, wall, tileArray, wallTexture);

	while (window.isOpen())
	{
		handleEvent(window);

		window.clear();
		
	}
	
	//delete tileArray;
	return 0;
}