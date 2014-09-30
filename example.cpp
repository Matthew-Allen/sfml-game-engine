#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	window.setFramerateLimit(60);

	sf::Texture squareTexture, backgroundTexture;
	sf::Sprite squareSprite, backgroundSprite, square2;
	sf::Clock inputClock;
	sf::Time timeSinceInputCheck;

	if((!squareTexture.loadFromFile("images/square.png")) || (!backgroundTexture.loadFromFile("images/background.png")))
	{
		std::cout << "Problem loading texture." << std::endl;
		return 1;
	}

	squareSprite.setTexture(squareTexture);
	square2.setTexture(squareTexture);
	square2.setColor(sf::Color(0,255,0));
	backgroundSprite.setTexture(backgroundTexture);

	square2.setPosition(50,50);
	squareSprite.setPosition(10,50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        timeSinceInputCheck += inputClock.getElapsedTime();
        inputClock.restart();

        if(timeSinceInputCheck.asMilliseconds() >= 10)
        {
        	timeSinceInputCheck = sf::milliseconds(0);
	        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	        {
	        	squareSprite.move(-2,0);
	        }
	        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	        {
	        	squareSprite.move(2,0);
	        }
	        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	        {
	        	squareSprite.move(0,-2);
	        }
	        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	        {
	        	squareSprite.move(0,2);
	        }
	    }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(squareSprite);
        window.draw(square2);
        window.display();
    }

    return 0;
}