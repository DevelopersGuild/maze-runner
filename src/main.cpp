
#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
const int ROW = 9;
const int COL = 11;

void handleEvent(sf::RenderWindow& window, sf::Event &event)
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
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
void drawCandy(sf::RenderWindow& window, bool arr[][COL], sf::Sprite *candyArr, sf::Texture candyTexture)
{
	int i = 0;

	for (int r = 0; r < ROW; r++)
	{
		for (int c = 1; c < COL; c++)
		{
			if (arr[r][c] == true)
			{
				candyArr[i] = sf::Sprite(candyTexture);
				candyArr[i].setPosition((c * 64) + 32, (r * 64) + 32); // c = x && r = y
				candyArr[i].setOrigin(10, 10);
				window.draw(candyArr[i]);
				i++;
			}
		}
	}
}
//this function should find the row and col for the overlapped candy sprite.
void findCandy(sf::Vector2f candyPosition, sf::Sprite *candyArr, bool arr[][COL], int &numcandy)
{
	int col = candyPosition.x;
	int row = candyPosition.y;

	col = (col - 32) / 64;
	row = (row - 32) / 64;

	if (row != 0 && col != 0)
	{
		arr[row][col] = false;
		numcandy--;
	}


}

bool handleWallCollision(sf::Sprite *tileArr, sf::Sprite pacmanSprite, int counter)
{
	for (int i = 0; i < counter; i++)
	{
		if (overlap(tileArr[i], pacmanSprite))
			return true; // there is collision
	}
	return false;
}

sf::Vector2f update(sf::Sprite* candyArr, sf::Sprite *tileArr, sf::Sprite& PacmanSprite, sf::Event event, int numtile, int numCandy, 
	bool *boolCandy)
{
	sf::Vector2f currPos = PacmanSprite.getPosition();
	if (event.key.code == sf::Keyboard::Left) //keeps it moving even though key is not pressed
	{
		PacmanSprite.setRotation(180);
		PacmanSprite.move(-2, 0);
	}
	else if ((event.key.code == sf::Keyboard::Right))
	{
		PacmanSprite.setRotation(0);
		PacmanSprite.move(2, 0);
	}
	else if ((event.key.code == sf::Keyboard::Up))
	{
		PacmanSprite.setRotation(270);
		PacmanSprite.move(0, -2);
	}
	else if ((event.key.code == sf::Keyboard::Down))
	{
		PacmanSprite.setRotation(90);
		PacmanSprite.move(0, 2);
	}

	// if pacman hits a wall, set position back to currPos
	bool wallCollision = false;
	wallCollision = handleWallCollision(tileArr, PacmanSprite, numtile);
	if (wallCollision)
	{
		PacmanSprite.setPosition(currPos);
	}

	//if pacman and candy overlaps that candy disappears
	for (int x = 0; x < numCandy; x++)
	{
		if (overlap(PacmanSprite, candyArr[x]))
		{
			sf::Vector2f candyposition = candyArr[x].getPosition();

			return candyposition;
		}
	}
	sf::Vector2f noOverlap;
	noOverlap.x = 0;
	noOverlap.y = 0;
	return noOverlap; // candy is there
}

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(704, 576), "SFML Works!");
	window.setVerticalSyncEnabled(true);

	sf::Texture wallTexture;
	wallTexture.loadFromFile(resourcePath() + "assets/wall.png");

	sf::Texture pacmanTexture;
	pacmanTexture.loadFromFile(resourcePath() + "assets/pacman.png");
	sf::Sprite pacmanSprite(pacmanTexture);
	pacmanSprite.setPosition(36, 250+36);
	pacmanSprite.setScale(1.5f, 1.5f);
	pacmanSprite.setOrigin(18, 18);
	sf::Texture candyTexture;
	candyTexture.loadFromFile(resourcePath() + "assets/candy.png");


	// map array beta
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

	//bool array for the map
	int numtile = 0;
	bool wall[ROW][COL];
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map[r][c] == 1)
			{
				wall[r][c] = true; // there is a wall
				numtile++;
			}
			if (map[r][c] == 0)
				wall[r][c] = false; // blank
		}
	}

	int numcandy = 0;
	bool candy[ROW][COL];
	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			if (map[r][c] == 0)
			{
				candy[r][c] = true; // there is a candy	
				numcandy++;
			}
			if (map[r][c] == 1)
				candy[r][c] = false; // blank
		}
	}

	sf::Sprite *tileArray = new sf::Sprite[numtile];
	sf::Sprite*candyArray = new sf::Sprite[numcandy];
	sf::Vector2f overlapCandy;


	sf::Font font;
	if (!font.loadFromFile(resourcePath() + "assets/snap.ttf"))
	{
		cout << "CANNOT OPEN THE FILE." << endl;
	}
	sf::String sentence;
	sf::Text text(sentence, font, 60);
	text.setString("VICTORY");
	text.setColor(sf::Color::White);
	text.setOrigin(160, 32);
	text.setPosition(350, 300);

	while (window.isOpen())// && numcandy != 0)
	{
		window.clear();

		sf::Event event;
		handleEvent(window, event);
		overlapCandy = update(candyArray, tileArray, pacmanSprite, event, numtile, numcandy, *candy);
	
		findCandy(overlapCandy, candyArray, candy, numcandy);
		cout << numcandy << endl;

		drawWall(window, wall, tileArray, wallTexture);
		drawCandy(window, candy, candyArray, candyTexture);
		
		if (numcandy == 0)
		{
			window.draw(text);
		}
		draw(window, pacmanSprite, numtile);
	}

	
	return 0;
}
