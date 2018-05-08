#include "timeElapsed.h"



timeElapsed::timeElapsed()
{

}

timeElapsed::~timeElapsed()
{
}


void drawTime(sf::RenderWindow& _window)
{
	Font font;
	font.loadFromFile("Fonts/MarkerFelt.ttf");
	sf::Time second = sf::seconds(0.01f);
	sf::Clock clock; // starts the clock
	Text timeElapse;
	timeElapse.setFont(font);
	timeElapse.setColor(Color::Red);
	timeElapse.setPosition(1010, 490);
	timeElapse.setCharacterSize(40);
	timeElapse.setString("Time: " + to_string(clock.getElapsedTime().asSeconds()));
	_window.draw(timeElapse);
}


