#include "targetSound.h"

void PlayTargetgSound(Music &music)
{
	if (!music.openFromFile("sounds/target.ogg"))
	{
		std::cout << "ERROR" << std::endl;
	}
	else music.play();
}