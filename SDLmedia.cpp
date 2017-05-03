#include "SDLmedia.hpp"

#include <cstdio>

#define mediaErrorProc(errcode) \
{Close();return errcode;}\
	else\
		ResourceST=errcode;

SDLmedia::SDLmedia()
{
	ResourceST=0;
	Load();
}
SDLmedia::~SDLmedia()
{
	Close();
}
int SDLmedia::Load()
{
	//MEDIA_SDL_INIT
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0)
		mediaErrorProc(MEDIA_SDL_INIT)
	//MEDIA_WINDOW
	gWindow=SDL_CreateWindow("Demo",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
			640,480,SDL_WINDOW_SHOWN);
	if(gWindow==NULL)
		mediaErrorProc(MEDIA_WINDOW)
	//MEDIA_RENDERER
	gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
	if(gRenderer==NULL)
		mediaErrorProc(MEDIA_RENDERER)
	//MEDIA_MIX_OGG
	if(Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
		mediaErrorProc(MEDIA_MIX_OGG)
	//MEDIA_MIX_OPENAUDIO
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)!=0)
		mediaErrorProc(MEDIA_MIX_OPENAUDIO)
}
void SDLmedia::Close()
{
	switch(ResourceST)
	{
	case MEDIA_MIX_OPENAUDIO:
		Mix_CloseAudio();
		printf("Close Audio\n");
	case MEDIA_MIX_OGG:
		Mix_Quit();
		printf("Mix Quit\n");
	case MEDIA_RENDERER:
		SDL_DestroyRenderer(gRenderer);
		printf("Destroy renderer\n");
	case MEDIA_WINDOW:
		SDL_DestroyWindow(gWindow);
		printf("Destroy window\n");
	case MEDIA_SDL_INIT:
		SDL_Quit();
		printf("free sdl\n");
	default:
		ResourceST=0;
	}
}
bool SDLmedia::Ready()
{
	return ResourceST==MEDIA_MIX_OPENAUDIO;
}
int SDLmedia::eventHandle()
{
	int ret=1;
	SDL_Event evt;
	while(SDL_PollEvent(&evt)!= 0)
	{
		switch(evt.type)
		{
		case SDL_QUIT:
			ret=0;
		}
	}
	return ret;
}
