#include "SpinGems.h"



SpinGems::SpinGems(RenderWindow * window, Texture &t, int column, int line, int width, int height, float speed, int count)
{
	this->window = window;
	this->speed = speed;
	this->Frame = 0;

	for (int i = 0; i < count; i++)
		this->Frames.push_back(IntRect(column + width*i, line, width, height));

	this->sprite.setTexture(t);
	this->sprite.setScale(1, 1);
	this->sprite.setTextureRect(this->Frames[0]);
}


SpinGems::~SpinGems()
{
}

void SpinGems::update()
{
	this->Frame += this->speed;
	int n = this->Frames.size();
	if (this->Frame > n)
		this->Frame -= n;
	this->sprite.setTextureRect(this->Frames[int(this->Frame)]);
}

void SpinGems::draw()
{
	this->window->draw(this->sprite);
}