#include"Text.h"


void printText(RenderWindow * window,Text &text)
{
	Font font;
	font.loadFromFile("Fonts/MarkerFelt.ttf");
	
	text.setFont(font);
	text.setColor(Color::Red);
	text.setPosition(10, 10);
	text.setString("CLICK THE BUTTON");
	
}