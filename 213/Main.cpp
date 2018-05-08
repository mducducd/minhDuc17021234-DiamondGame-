#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "SpinGems.h"
#include "Sound.h"
#include"makeText.h"
#include "Animation.h"
#include "timeElapsed.h"


using namespace sf;

int ts = 82; //gems gap
Vector2i offset(93, 51);// table's pos

struct piece
{	
	int x, y, col, row, kind, match, alpha;
	piece() { match = 0; alpha = 255; }
} grid[10][10];

void swap(piece p1, piece p2)
{
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	grid[p1.row][p1.col] = p1;
	grid[p2.row][p2.col] = p2;
}

void PlayGame(RenderWindow &window)  
{
	//srand((unsigned)time(NULL));
	Texture t1, t2;
	t1.loadFromFile("images/background.png");
	t2.loadFromFile("images/gems.png");
	

	Music music;
	
	Sprite background(t1), gems(t2);

	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			grid[i][j].kind = rand() % 7;
			grid[i][j].col = j;
			grid[i][j].row = i;
			grid[i][j].x = j*ts;
			grid[i][j].y = i*ts;
		}

	int x0, y0, x, y; int click = 0; Vector2i pos;
	bool isSwap = false, isMoving = false;
	unsigned long long score = 0;
	Font font;
	font.loadFromFile("Fonts/MarkerFelt.ttf");
	Text Diem,over;
	Diem.setFont(font);
	Diem.setColor(Color::Red);
	Diem.setCharacterSize(43);
	Diem.setPosition(900, 88);
	Diem.setString("Score: " + to_string(score));

	
	sf::Time second = sf::seconds(0.01f);



	sf::Clock clock; // starts the clock
	Text timeElapsed;
	timeElapsed.setFont(font);
	timeElapsed.setColor(Color::Red);
	timeElapsed.setPosition(1010, 490);
	timeElapsed.setCharacterSize(40);
	timeElapsed.setString("Time: " + to_string(clock.getElapsedTime().asSeconds()));
	
	Texture t;
	t.loadFromFile("images/a.png");
	Animation hourGlass(&window, t, 0, 0, 85,132 , 0.1, 4);

	Texture _blue;
	_blue.loadFromFile("images/blue.png");
	Animation blue(&window, _blue, 0, 0, 64, 896, 0.1, 29);
	
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::MouseButtonPressed)
			{	
				if (e.key.code == Mouse::Left)
				{
					PlayTargetSound(music);
					if (!isSwap && !isMoving) click++;
					pos = Mouse::getPosition(window) - offset;
					
					
				}
			}
		}

		// mouse click
		if (click == 1)
		{	
			x0 = pos.x / ts + 1;
			y0 = pos.y / ts + 1;
			
			
		}
		if (click == 2)
		{	
			x = pos.x / ts + 1;
			y = pos.y / ts + 1;
			if (abs(x - x0) + abs(y - y0) == 1)
			{
				swap(grid[y0][x0], grid[y][x]); isSwap = 1; click = 0;
			}
			else click = 1;
		}

		//Match finding
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				if (grid[i][j].kind == grid[i + 1][j].kind)
					if (grid[i][j].kind == grid[i - 1][j].kind)
						for (int n = -1; n <= 1; n++) grid[i + n][j].match++;

				if (grid[i][j].kind == grid[i][j + 1].kind)
					if (grid[i][j].kind == grid[i][j - 1].kind)
						for (int n = -1; n <= 1; n++) grid[i][j + n].match++;
			}

		//Moving animation
		isMoving = false;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				piece &p = grid[i][j];
				int dx, dy;
				for (int n = 0; n<4; n++)   // speed
				{
					dx = p.x - p.col*ts;
					dy = p.y - p.row*ts;
					if (dx) p.x -= dx / abs(dx);
					if (dy) p.y -= dy / abs(dy);
				}
				if (dx || dy) isMoving = 1;
			}

		//Deleting amimation
		if (!isMoving)
			for (int i = 1; i <= 8; i++)
				for (int j = 1; j <= 8; j++)
					if (grid[i][j].match) if (grid[i][j].alpha>10) { grid[i][j].alpha -= 10; isMoving = true; }

		//Get score
		int  ifscore = 0;
		//bool key = true;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				score += grid[i][j].match; 
				//key = false;
				ifscore += grid[i][j].match;
				//score += score_;
			}
		


		//Second swap if no match
		if (isSwap && !isMoving)
		{
			if (!ifscore) swap(grid[y0][x0], grid[y][x]); isSwap = 0;
		}

		//Update grid
		if (!isMoving)
		{
			for (int i = 8; i>0; i--)
				for (int j = 1; j <= 8; j++)
					if (grid[i][j].match)
						for (int n = i; n>0; n--)
							if (!grid[n][j].match) { swap(grid[n][j], grid[i][j]); break; };

			for (int j = 1; j <= 8; j++)
				for (int i = 8, n = 0; i>0; i--)
					if (grid[i][j].match)
					{
						grid[i][j].kind = rand() % 7;
						grid[i][j].y = -ts*n++;
						grid[i][j].match = 0;
						grid[i][j].alpha = 255;
					}
		}


		//////draw///////
		window.draw(background);

		blue.update(790, 5);
		blue.draw();
		blue.update(0, 5);
		blue.draw();
		hourGlass.update(900, 455);
		hourGlass.draw();
		Diem.setString("Score:   " + to_string(score / 1000 ));
		window.draw(Diem);
		int time = clock.getElapsedTime().asSeconds();
		timeElapsed.setString("00:" + to_string(59 - time) + "s");
		
		if (time > 59)
		{
			
			window.draw(Diem);
			
			sf::sleep(seconds(3));
			window.close();
		}
		window.draw(timeElapsed);
		
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
			{
				piece p = grid[i][j];
				gems.setTextureRect(IntRect(p.kind * 64, 0, 64, 64));
				gems.setColor(Color(255, 255, 255, p.alpha));
				gems.setPosition(p.x, p.y);
				gems.move(offset.x - ts, offset.y - ts);
				window.draw(gems);
			}
		
		window.display();
	}
}

int main()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RenderWindow window(VideoMode(1280, 720), "Diamond Game!", Style::Default);
	window.setFramerateLimit(60);
	srand(time(NULL));
	Texture button;
	button.loadFromFile("PlayButton.png");
	Sprite Button(button);
	Button.setOrigin(52, 24);
	Button.setPosition(600, 320);
	Texture back;
	back.loadFromFile("GameMenu.png");
	Sprite Back(back);
	Music music;
	Text text;
	Font font;
	font.loadFromFile("Fonts/MarkerFelt.ttf");
	text.setFont(font);
	text.setColor(Color::Red);
	text.setPosition(10, 10);
	text.setString("CLICK THE BUTTON");
	
	
	
	if (!music.openFromFile("sounds/spell3.wav.ogg"))
	{
		std::cout << "ERROR" << std::endl;
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		window.clear();
		window.draw(Back);
		window.draw(Button); 
		window.draw(text);
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Mouse::getPosition(window).x >= 548 && Mouse::getPosition(window).x <= 652 && Mouse::getPosition(window).y >= 266 && Mouse::getPosition(window).y <= 324)
			{
				PlayStartingSound( music);
				PlayGame(window);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return 0;
		window.display();
	}

	return 0;
}



