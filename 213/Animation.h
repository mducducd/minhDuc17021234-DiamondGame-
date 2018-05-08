#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Animation

{
public:
	RenderWindow * window;
	Sprite sprite;
	float speed;
	float Frame;
	vector <IntRect> Frames;
public:
	Animation();
	~Animation();

	Animation(RenderWindow * window, Texture &t, int column, int line, int width, int height, float speed, int count);
	void update(int x,int y);// x,y are animation's postion 
	void draw();



};
