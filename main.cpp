#include <SDL.h>
#include "SDLmedia.hpp"
#include "form.hpp"
int main(int argc,char *argv[])
{
	SDLmedia mysdl;
	form fm(mysdl.gRenderer);
	if(!mysdl.Ready())
		return 0;
	int GameState=1;
	while(GameState)
	{
		GameState=fm.eventHandle();
		SDL_Delay(20);
	}
	return 0;
}
