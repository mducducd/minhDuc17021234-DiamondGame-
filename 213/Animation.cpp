#include "Animation.h"


Animation::

Animation::Animation(RenderWindow * window, Texture &t, int column, int line, int width, int height, float speed, int count)
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


Animation::~Animation()
{
}

void Animation::update(int x,int y)
{
	this->sprite.setPosition(Vector2f(x, y));
	this->Frame += this->speed;
	int n = this->Frames.size();
	if (this->Frame > n)
		this->Frame -= n;
	this->sprite.setTextureRect(this->Frames[int(this->Frame)]);
}

void Animation::draw()
{
	this->window->draw(this->sprite);
}