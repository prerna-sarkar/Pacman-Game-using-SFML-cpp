

#include"coinGrid.h"
using namespace sf;

int main()
{
	VideoMode vm(634, 722); // Create a video mode object

	RenderWindow window(vm, "PACMAN"); // Create and open a window for the game

	Texture textureBackground; // Create a texture to hold a graphic on the GPU

	textureBackground.loadFromFile("graphics/pac-man.bmp"); // Load a graphic into the texture

	Sprite spriteBackground; // Create a sprite

	spriteBackground.setTexture(textureBackground); // Attach the texture to the sprite

	spriteBackground.setPosition(0, 0); // Set the spriteBackground to cover the screen

	bool paused = true; // Track whether the game is running

	bool bIsPressed = false; // Track whether button is pressed

	// Display text/message ------------------------------------------------------------------------
	sf::Text messageText;
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	messageText.setString("PRESS ENTER TO START"); 	// Assign the actual message
	messageText.setCharacterSize(50);
	messageText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds(); 	// Position the text
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(324, 330);

	// Prepare Pacman ------------------------------------------------------------------------
	Texture texturePacman;
	texturePacman.loadFromFile("graphics/pacman.bmp");
	Sprite spritePacman;
	spritePacman.setTexture(texturePacman);
	spritePacman.setPosition(300, 490);

	Vector2f pacPosition;
	Vector2f pacOldPosition;

	pacPosition.x = 300;
	pacPosition.y = 490;
	float pacSpeed = 80.0f;
	int pacMoving = 0; // 1 =>left; 2=>right; 3=>up; 4=>down

	// Prepare Ghosts ------------------------------------------------------------------------

	// GhostPink
	Texture textureGhostPink;
	textureGhostPink.loadFromFile("graphics/pink_ghost.bmp");
	Sprite spriteGhostPink;
	spriteGhostPink.setTexture(textureGhostPink);

	// GhostOrange
	Texture textureGhostOrange;
	textureGhostOrange.loadFromFile("graphics/orange_ghost.bmp");
	Sprite spriteGhostOrange;
	spriteGhostOrange.setTexture(textureGhostOrange);

	// GhostBlue
	Texture textureGhostBlue;
	textureGhostBlue.loadFromFile("graphics/blue_ghost.bmp");
	Sprite spriteGhostBlue;
	spriteGhostBlue.setTexture(textureGhostBlue);

	// GhostRed
	Texture textureGhostRed;
	textureGhostRed.loadFromFile("graphics/red_ghosts.bmp");
	Sprite spriteGhostRed;
	spriteGhostRed.setTexture(textureGhostRed);

	// Vectors of Ghosts
	std::vector<sf::Sprite> vecGhosts;
	vecGhosts.push_back(spriteGhostPink);
	vecGhosts.push_back(spriteGhostOrange);
	vecGhosts.push_back(spriteGhostBlue);
	vecGhosts.push_back(spriteGhostRed); //red ghost at the last so it matches the startup screen

	std::vector<bool> vecGhostsAlive; //store status (Alive => Active Ghost)
	std::vector<float> vecGhostsSpeed; //store speed of the ghosts
	std::vector<int> vecGhostsDirection; //store direction of the ghosts (1-left; 2-right; 3-up; 4-down)

	std::vector<Vector2f> vecGhosts_Position; //store current position of the ghosts
	std::vector<Vector2f> vecGhosts_OldPosition; //store old position of the ghosts


	for (int i = 0; i < 4; i++) //initializing all vectors
	{
		vecGhosts[i].setPosition(303, 247);
		vecGhostsAlive.push_back(true); //no ghosts eaten up, all four alive
		vecGhostsSpeed.push_back(80.0f); // How fast can the ghost wander
		vecGhosts_Position.push_back(vecGhosts[i].getPosition());
		vecGhosts_OldPosition.push_back(vecGhosts[i].getPosition());
		vecGhostsDirection.push_back(1 + (std::rand() % 4)); //initial direction of ghosts is determined randomly (1/2/3/4)
	}

	bool collisionWithGhost = false;

	// PowerUps ------------------------------------------------------------------------
	sf::CircleShape PowerUp1(6.3f); //radius of circle
	PowerUp1.setPosition(55, 92);  //x,y position of circle
	sf::CircleShape PowerUp2(6.3f);
	PowerUp2.setPosition(55, 500);
	sf::CircleShape PowerUp3(6.3f);
	PowerUp3.setPosition(568, 92);
	sf::CircleShape PowerUp4(6.3f);
	PowerUp4.setPosition(568, 500);

	//vector storing all power-ups
	std::vector<sf::CircleShape> vecPowerUps;
	for (int i = 0; i < 4; i++)
	{
		vecPowerUps.push_back(PowerUp1);
		vecPowerUps.push_back(PowerUp2);
		vecPowerUps.push_back(PowerUp3);
		vecPowerUps.push_back(PowerUp4);
	}

	bool collisionWithPowerUp = false;
	float powerUpTimeRemaining = 0.0f;

	// Coins ----------------------------------------------------------------------------
	
	//(x,y) position of first coin (top left)
	int x0 = 60;
	int y0 = 55 - 20;

	std::vector<CircleShape> vecCoins; //holds one row at a time
	std::vector<std::vector<CircleShape>> vecCoins2d; //holds all the coins
	int numRows = 29;
	for (int i = 1; i < numRows + 1; i++)
	{
		switch (i)
		{
		case 1:
		case 20:
			createRow1(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 2:
		case 3:
		case 4:
		case 21:
		case 22:
			createRow2(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 5:
		case 29:
			createRow5(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 6:
		case 7:
			createRow6(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 8:
		case 26:
			createRow8(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			createRow9(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 23:
			createRow23(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 24:
		case 25:
			createRow24(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		case 27:
		case 28:
			createRow27(x0, y0 + (20.5 * i), vecCoins);
			vecCoins2d.push_back(vecCoins);
			break;
		default:
			break;
		}
	}

	// Middle tunnel at both ends ----------------------------------------------------------------
	sf::RectangleShape leftTunnelEnd(sf::Vector2f(10, 344-303));
	leftTunnelEnd.setPosition(0, 303);

	sf::RectangleShape rightTunnelEnd(sf::Vector2f(641-625, 344 - 303));
	rightTunnelEnd.setPosition(625, 303);

	// Walls -------------------------------------------------------------------------------------
	
	std::vector<RectangleShape> vecWalls; //holds wall rectangles

	//...four edges
	vecWalls.push_back(RectangleShape(sf::Vector2f(650, 40))); //top
	vecWalls.back().setPosition(0, 650);

	vecWalls.push_back(RectangleShape(sf::Vector2f(650, 40))); //bottom
	vecWalls.back().setPosition(0, 0);

	vecWalls.push_back(RectangleShape(sf::Vector2f(42, 303))); //left1
	vecWalls.back().setPosition(0, 0);

	vecWalls.push_back(RectangleShape(sf::Vector2f(42, 310))); //left2
	vecWalls.back().setPosition(0, 341);

	vecWalls.push_back(RectangleShape(sf::Vector2f(40, 303))); //right1
	vecWalls.back().setPosition(595, 0);

	vecWalls.push_back(RectangleShape(sf::Vector2f(40, 310))); //right2
	vecWalls.back().setPosition(595, 341);

	//...row 1
	vecWalls.push_back(RectangleShape(sf::Vector2f(145 - 82, 120 - 76)));
	vecWalls.back().setPosition(82, 76);

	vecWalls.push_back(RectangleShape(sf::Vector2f(268 - 184, 120 - 76)));
	vecWalls.back().setPosition(184, 76);

	vecWalls.push_back(RectangleShape(sf::Vector2f(330-307, 120 - 26)));
	vecWalls.back().setPosition(307, 26);

	vecWalls.push_back(RectangleShape(sf::Vector2f(453 - 368, 120 - 76)));
	vecWalls.back().setPosition(368, 76);

	vecWalls.push_back(RectangleShape(sf::Vector2f(555 - 491, 120 - 76)));
	vecWalls.back().setPosition(491, 76);

	//...row 2
	vecWalls.push_back(RectangleShape(sf::Vector2f(145 - 81, 182 - 158)));
	vecWalls.back().setPosition(82, 158);

	vecWalls.push_back(RectangleShape(sf::Vector2f(207 - 184, 304 - 158)));
	vecWalls.back().setPosition(184, 158);

	vecWalls.push_back(RectangleShape(sf::Vector2f(391 - 245, 182 - 158)));
	vecWalls.back().setPosition(245, 158);

	vecWalls.push_back(RectangleShape(sf::Vector2f(207 - 183, 304 - 158)));
	vecWalls.back().setPosition(429, 158);

	vecWalls.push_back(RectangleShape(sf::Vector2f(555 - 491, 182 - 158)));
	vecWalls.back().setPosition(491, 158);

	vecWalls.push_back(RectangleShape(sf::Vector2f(328 - 307, 245 - 181)));
	vecWalls.back().setPosition(306, 181);

	//...row 3
	vecWalls.push_back(RectangleShape(sf::Vector2f(146 - 30, 304 - 219)));
	vecWalls.back().setPosition(30, 219);

	vecWalls.push_back(RectangleShape(sf::Vector2f(268 - 204, 243 - 219)));
	vecWalls.back().setPosition(204, 219);

	vecWalls.push_back(RectangleShape(sf::Vector2f(268 - 204, 243 - 219)));
	vecWalls.back().setPosition(368, 219);

	vecWalls.push_back(RectangleShape(sf::Vector2f(146 - 30, 304 - 219)));
	vecWalls.back().setPosition(491, 219);

	//...row 4
	vecWalls.push_back(RectangleShape(sf::Vector2f(292 - 245, 366 - 284)));
	vecWalls.back().setPosition(245, 284);

	vecWalls.push_back(RectangleShape(sf::Vector2f(346 - 292, 366 - 284)));
	vecWalls.back().setPosition(291, 284);

	vecWalls.push_back(RectangleShape(sf::Vector2f(292 - 245, 366 - 284)));
	vecWalls.back().setPosition(344, 284);

	//...row 5
	vecWalls.push_back(RectangleShape(sf::Vector2f(146 - 30, 304 - 218)));
	vecWalls.back().setPosition(30, 341);

	vecWalls.push_back(RectangleShape(sf::Vector2f(453 - 429, 428 - 344)));
	vecWalls.back().setPosition(184, 344);

	vecWalls.push_back(RectangleShape(sf::Vector2f(453-429, 428 - 344)));
	vecWalls.back().setPosition(429, 344);

	vecWalls.push_back(RectangleShape(sf::Vector2f(146 - 30, 304 - 218)));
	vecWalls.back().setPosition(491, 341);

	//...row 6
	vecWalls.push_back(RectangleShape(sf::Vector2f(391 - 245, 182 - 158)));
	vecWalls.back().setPosition(245, 405);

	vecWalls.push_back(RectangleShape(sf::Vector2f(329 - 308, 245 - 181)));
	vecWalls.back().setPosition(308, 424);

	//...row 7
	vecWalls.push_back(RectangleShape(sf::Vector2f(145 - 81, 182 - 158)));
	vecWalls.back().setPosition(82, 466);

	vecWalls.push_back(RectangleShape(sf::Vector2f(268 - 183, 182 - 158)));
	vecWalls.back().setPosition(184, 466);

	vecWalls.push_back(RectangleShape(sf::Vector2f(268 - 183, 182 - 158)));
	vecWalls.back().setPosition(368, 466);

	vecWalls.push_back(RectangleShape(sf::Vector2f(145 - 81, 182 - 158)));
	vecWalls.back().setPosition(491, 466);

	vecWalls.push_back(RectangleShape(sf::Vector2f(453 - 429, 428 - 344)));
	vecWalls.back().setPosition(122,466);

	vecWalls.push_back(RectangleShape(sf::Vector2f(453 - 429, 428 - 344)));
	vecWalls.back().setPosition(491,466);

	//...row 8
	vecWalls.push_back(RectangleShape(sf::Vector2f(145 - 81, 182 - 158)));
	vecWalls.back().setPosition(20,527 );

	vecWalls.push_back(RectangleShape(sf::Vector2f(207 - 184, 428 - 344)));
	vecWalls.back().setPosition(184, 527);

	vecWalls.push_back(RectangleShape(sf::Vector2f(391 - 245, 182 - 158)));
	vecWalls.back().setPosition(245, 527);

	vecWalls.push_back(RectangleShape(sf::Vector2f(207 - 183, 428 - 344)));
	vecWalls.back().setPosition(429, 527);

	vecWalls.push_back(RectangleShape(sf::Vector2f(145 - 81, 182 - 158)));
	vecWalls.back().setPosition(555, 527);

	vecWalls.push_back(RectangleShape(sf::Vector2f(328 - 307, 245 - 181)));
	vecWalls.back().setPosition(308, 551);

	//..row 9
	vecWalls.push_back(RectangleShape(sf::Vector2f(266-82, 182 - 158)));
	vecWalls.back().setPosition(82, 590);

	vecWalls.push_back(RectangleShape(sf::Vector2f(266 - 82, 182 - 158)));
	vecWalls.back().setPosition(368, 590);

	bool wallReached = false;
	
	//------------------------------------------------------------------------------
	
	//Time in game
	Clock clock; 
	Time dt;

	bool acceptInput = false; //control the player inputs
	std::string current_direction; //up down left right
	std::string desired_direction; //up down left right

	int numCoinsEaten = 0; //to keep track of number of coins eaten


	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				acceptInput = true;// Listen for key presses
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
			{
				paused = false;
				textureBackground.loadFromFile("graphics/maze.bmp");
				if (!bIsPressed)
				{
					bIsPressed = true;
				}
			}
		}

		// PACMAN MOVEMENTS

		Time dt = clock.restart(); // Update the delta time

		pacOldPosition = pacPosition;

		if (pacMoving == 1)
		{
			pacPosition.x -= pacSpeed * dt.asSeconds();
			current_direction = "left";
		}
		else if (pacMoving == 2)
		{
			pacPosition.x += pacSpeed * dt.asSeconds();
			current_direction = "right";
		}
		else if (pacMoving == 3)
		{
			pacPosition.y -= pacSpeed * dt.asSeconds();
			current_direction = "up";
		}
		else if (pacMoving == 4)
		{
			pacPosition.y += pacSpeed * dt.asSeconds();
			current_direction = "down";
		}

		spritePacman.setPosition(pacPosition);

		// GHOST MOVEMENTS

		for (int i = 0; i < 4; i++)
		{
			vecGhosts_OldPosition[i] = vecGhosts_Position[i];

			if (vecGhostsDirection[i] == 1)
			{
				vecGhosts_Position[i].x -= vecGhostsSpeed[i] * dt.asSeconds();
			}
			else if (vecGhostsDirection[i] == 2)
			{
				vecGhosts_Position[i].x += vecGhostsSpeed[i] * dt.asSeconds();
			}
			else if (vecGhostsDirection[i] == 3)
			{
				vecGhosts_Position[i].y -= vecGhostsSpeed[i] * dt.asSeconds();
			}
			else if (vecGhostsDirection[i] == 4)
			{
				vecGhosts_Position[i].y += vecGhostsSpeed[i] * dt.asSeconds();
			}

			vecGhosts[i].setPosition(vecGhosts_Position[i]);
		}

		// Ghost - Wall Collision
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < vecWalls.size(); j++)
			{
				if ((vecGhostsAlive[i] == true) && (vecGhosts[i].getGlobalBounds().intersects(vecWalls[j].getGlobalBounds())))
				{
					vecGhosts_Position[i] = vecGhosts_OldPosition[i]; //on collision with wall, move one step back and change direction!
					vecGhostsDirection[i] = 1 + (std::rand() % 4); //determine direction randomly (number between 1 to 4)
				}
			}
		}

		// Pacman - Coin Collision
		for (int i = 0; i < vecCoins2d.size(); i++)
		{
			for (int j = 0; j < vecCoins2d[i].size(); j++)
			{
				if (spritePacman.getGlobalBounds().intersects(vecCoins2d[i][j].getGlobalBounds()))
				{
					vecCoins2d[i][j].setPosition(2000, 2000); //hide the Coin
					numCoinsEaten++;
				}
			}
		}
		
		if (numCoinsEaten == 246)
		{
			window.close(); //if pacman eats all coins game ends
		}

		// Pacman - PowerUp Collision
		for (int i = 0; i < 4; i++)
		{
			if (spritePacman.getGlobalBounds().intersects(vecPowerUps[i].getGlobalBounds()))
			{
				collisionWithPowerUp = true;
				powerUpTimeRemaining = 5.0f;
				vecPowerUps[i].setPosition(4000, 4000); //hide the PowerUp
				break;
			}
		}

		if (collisionWithPowerUp) //for 5 seconds - can eat ghost
		{
			powerUpTimeRemaining -= dt.asSeconds(); //Subtract from the amount of power up time remaining
		}
		if (collisionWithPowerUp && (powerUpTimeRemaining <= 0.0f))
		{
			printf("powerup time up");
			collisionWithPowerUp = false;
		}

		// Pacman - Ghost Collision
		for (int i = 0; i < 4; i++)
		{
			if (vecGhostsAlive[i] == true) //collision with eaten up ghosts do not matter
			{
				if (spritePacman.getGlobalBounds().intersects(vecGhosts[i].getGlobalBounds()))
				{
					if (collisionWithPowerUp) //if ghost collides with powered up pacman
					{
						collisionWithGhost = true;
						vecGhostsAlive[i] = false; //Pacman eats the ghost!
					}
					else
					{
						window.close();  //if ghost collides with non-powered up pacman, game ends
					}
				}
			}
		}

		// Pacman - Wall Collision
		for (int i = 0; i < vecWalls.size(); i++)
		{
			if (spritePacman.getGlobalBounds().intersects(vecWalls[i].getGlobalBounds()))
			{
				wallReached = true;
			}
		}

		if (wallReached)
		{
			spritePacman.setPosition(pacOldPosition); //when Pacman intersects with wall, it takes a step back (to its previous position)
		}

		pacPosition = spritePacman.getPosition();

		if (acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right)) // Handle the right cursor key
			{
				desired_direction = "right";
				pacMoving = 2;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) // Handle the up cursor key
			{
				desired_direction = "up";
				pacMoving = 3;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) // Handle the left cursor key
			{
				desired_direction = "left";
				pacMoving = 1;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) // Handle the down cursor key
			{
				desired_direction = "down";
				pacMoving = 4;
			}
		}

		if (current_direction != desired_direction)
		{
			if (wallReached) //collision with current direction
			{
				current_direction = desired_direction; //as wallReached while going in a given direction, we set current direction to desired direction and reset flag wallReached
				wallReached = false;
			}
		}

		// Pacman can go through the middle tunnels on each side
		if (spritePacman.getGlobalBounds().intersects(leftTunnelEnd.getGlobalBounds()))
		{
			pacPosition.x = 562;
			spritePacman.setPosition(pacPosition);
		}
		else if (spritePacman.getGlobalBounds().intersects(rightTunnelEnd.getGlobalBounds()))
		{
			pacPosition.x = 40;
			spritePacman.setPosition(pacPosition);
		}

		// Ghosts can go through the middle tunnels on each side
		for (int i = 0; i < 4; i++)
		{
			if (vecGhosts[i].getGlobalBounds().intersects(leftTunnelEnd.getGlobalBounds()))
			{
				vecGhosts_Position[i].x = 562;
			}
			else if (vecGhosts[i].getGlobalBounds().intersects(rightTunnelEnd.getGlobalBounds()))
			{
				vecGhosts_Position[i].x = 40;
			}
			vecGhosts[i].setPosition(vecGhosts_Position[i]);
		}

		// Clear everything from the last frame -----------------------------------------------------------------
		window.clear();

		// Draw our game scene here -----------------------------------------------------------------------------
		
		window.draw(spriteBackground);
		if (!paused)
		{
			for (int i = 0; i < vecCoins2d.size(); i++)
			{
				for (int j = 0; j < vecCoins2d[i].size(); j++)
				{
					window.draw(vecCoins2d[i][j]);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				if (vecGhostsAlive[i] == true)
				{
					window.draw(vecGhosts[i]); //display only alive ghosts
				}
				window.draw(vecPowerUps[i]);
			}
			window.draw(spritePacman);
		}
		if (paused)
		{
			window.draw(messageText); // Draw our message
		}

		window.display(); // Show everything we just drew
	}
	return 0;
}
