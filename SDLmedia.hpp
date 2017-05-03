#ifndef SDL_MEDIA_HPP
#define SDL_MEDIA_HPP
#include <SDL.h>
#include <SDL_mixer.h>
enum
{
	MEDIA_SDL_INIT=1,
	MEDIA_WINDOW,
	MEDIA_RENDERER,
	MEDIA_MIX_OGG,
	MEDIA_MIX_OPENAUDIO
};

class SDLmedia
{
protected:
public:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	int ResourceST;

	SDLmedia();
	~SDLmedia();
	int Load();     //載入媒體
	void Close();   //卸載媒體
	bool Ready();   //確認是否可運作
	int eventHandle();//事件處理
};

#endif


