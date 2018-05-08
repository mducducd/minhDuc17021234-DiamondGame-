#include "Sound.h"

void PlayStartingSound(Music &music)
{
	if (!music.openFromFile("sounds/spell3.wav.ogg"))
	{
		std::cout << "ERROR" << std::endl;
	}
	else music.play();
}
void PlayTargetSound(Music &music)
{
	if (!music.openFromFile("sounds/target.ogg"))
	{
		std::cout << "ERROR" << std::endl;
	}
	else music.play();
}