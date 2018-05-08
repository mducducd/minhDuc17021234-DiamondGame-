#include "StartSound.h"



StartSound::StartSound(Music music)
{
	if (!music.openFromFile("sounds/spell3.wav.ogg"))
	{
		std::cout << "ERROR" << std::endl;
	}
	else music.play();
}


StartSound::~StartSound()
{
}
