#pragma once
#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;
class SpinGems
{
public:
	RenderWindow * window;
	Sprite sprite;
	float speed;
	float Frame;
	vector <IntRect> Frames;
public:
	SpinGems();
	~SpinGems();

	SpinGems(RenderWindow * window, Texture &t, int column, int line, int width, int height, float speed, int count);
	void update();
	void draw();
};

