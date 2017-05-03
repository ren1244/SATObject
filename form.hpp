#ifndef FORM_HPP
#define FORM_HPP
#include <SDL.h>
#include "objects.hpp"

enum
{
	FORM_IMG=1
};


class form
{
public:
	//media to load
	SDL_Texture *img;
	
	//status
	SDL_Renderer *gRenderer;
	int Rot;
	point Pos;
	int resourceST;
	
	//
	object_base obj;
	object_base obj2;
	
	
	
	/*polygen poly;
	rect    rec;
	circle  cir;
	polygen  ppp;*/
	//
	form(SDL_Renderer *pRenderer);
	~form();
	int eventHandle();//事件處理
	
	int Load();     //載入媒體
	void Close();   //卸載媒體
	bool hasDraw;
	void showStatus(int mx,int my);
	void draw();
	bool isReady();
};

#endif


