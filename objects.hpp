#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "geometry.hpp"
#include <SDL.h>

class object_base
{
	//【屬性】
public:	
	//(1)圖檔相關
	SDL_Texture *img; //圖檔
	SDL_Rect clip;   //圖檔的部分
	SDL_Point center; //圖檔對照position位置
	

	//(2)碰撞模型的形狀
	std::vector<geometry_base*> shape; //形狀列表(這個物件是由多個基本形狀組成)
	
	//【方法】
	//建構
	object_base(SDL_Texture* imgTexture=NULL,//圖檔 Texture
	            SDL_Rect*    pClip=NULL,     //裁切 
	            SDL_Point*   pCenter=NULL);  //設定中心點
	//碰撞
	bool isCollise(const object_base& other,const point& pos1,double rot1,const point& pos2,double rot2);
	//描繪
	void draw(SDL_Renderer *gRenderer,
              const point&  pos,
              double        rot);
};

#endif
