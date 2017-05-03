#include "form.hpp"
#include "geometry.hpp"
#define PI 3.1415926535
#include <cmath>
#include <cstdio>



form::form(SDL_Renderer* pRenderer)
	:gRenderer(pRenderer)
{
	resourceST=0;
	hasDraw=false;
	Rot=0;
	Pos=point(320,240);
	if(Load()!=0)
		return ;
	
	obj2.img=obj.img=img;
	obj2.clip=obj.clip={0,0,214,189};
	obj2.center=obj.center={104,80};
	
	//設定矩形
	geometry_base *pGeo;
	pGeo=new rect;
	dynamic_cast<rect*>(pGeo)->setRect(-104,-75,70,70);
	obj.shape.push_back(pGeo);
	pGeo=new rect;
	dynamic_cast<rect*>(pGeo)->setRect(-104,-75,70,70);
	obj2.shape.push_back(pGeo);
	
	//設定圓形
	pGeo=new circle;
	dynamic_cast<circle*>(pGeo)->center=point(69.282,-40);
	dynamic_cast<circle*>(pGeo)->radius=40;
	obj.shape.push_back(pGeo);
	pGeo=new circle;
	dynamic_cast<circle*>(pGeo)->center=point(69.282,-40);
	dynamic_cast<circle*>(pGeo)->radius=40;
	obj2.shape.push_back(pGeo);
	
	//設定三角形
	pGeo=new polygen;
	dynamic_cast<polygen*>(pGeo)->points.push_back(point(0,22.265));
	dynamic_cast<polygen*>(pGeo)->points.push_back(point(-50,108.866));
	dynamic_cast<polygen*>(pGeo)->points.push_back(point(50,108.866));
	obj.shape.push_back(pGeo);
	pGeo=new polygen;
	dynamic_cast<polygen*>(pGeo)->points.push_back(point(0,22.265));
	dynamic_cast<polygen*>(pGeo)->points.push_back(point(-50,108.866));
	dynamic_cast<polygen*>(pGeo)->points.push_back(point(50,108.866));
	obj2.shape.push_back(pGeo);
}
form::~form()
{
	for(int i=obj.shape.size()-1;i>=0;--i)
		delete obj.shape[i];
	for(int i=obj2.shape.size()-1;i>=0;--i)
		delete obj2.shape[i];
	Close();
}
int form::eventHandle()
{
	int ret=1;
	SDL_Event evt;
	while(SDL_PollEvent(&evt)!= 0)
	{
		switch(evt.type)
		{
		case SDL_QUIT:
			ret=0;
			break;
		case SDL_MOUSEMOTION:
			//showStatus(evt.button.x,evt.button.y);
			Pos=point(evt.motion.x,evt.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			Rot+=evt.wheel.y*5;
			break;
		}
	}
	draw();
	return ret;
}
void form::draw()
{
	/*if(hasDraw)
		return;
	hasDraw=true;*/
	
	int i,j,N,cx,cy,rot;
	SDL_GetRendererOutputSize(gRenderer,&cx,&cy);
	
	if(isReady())
	{
		//SDL_RenderCopy(gRenderer,img,NULL,NULL);
		if(obj.isCollise(obj2,Pos,Rot,point(320,240),30))
			SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);
		else
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        obj2.draw(gRenderer,point(320,240),30);
		obj.draw(gRenderer,Pos,Rot);
		
	}
	else
		printf("not ready");
		
	
	
	SDL_RenderPresent(gRenderer);
}
void form::showStatus(int mx,int my)
{
	/*point src(mx,my),dest;
	poly.closePoint(src,dest,point(320,240),Rot);
	printf("(%d,%d)-(%.1lf,%.1lf)\n",mx,my,dest.x,dest.y);*/
}

int form::Load()
{
	SDL_Surface *suf=SDL_LoadBMP("img2.bmp");
	if(suf==NULL)
	{
		printf("\nERR:%s\n",SDL_GetError());
		Close();
		return FORM_IMG;
	}
	SDL_SetColorKey(suf,SDL_TRUE,SDL_MapRGB(suf->format,0xFF,0x00,0xFF));
	img=SDL_CreateTextureFromSurface(gRenderer,suf);
	resourceST=FORM_IMG;
	SDL_FreeSurface(suf);
	return 0;
}
void form::Close()
{
	switch(resourceST)
	{
	case FORM_IMG:
		SDL_DestroyTexture(img);
	default:
		resourceST=0;
	}
}
bool form::isReady()
{
	return resourceST==FORM_IMG;
}
