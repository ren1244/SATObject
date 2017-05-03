#include "objects.hpp"
#include <cmath>
#define PI 3.1415926535

object_base::object_base(SDL_Texture* imgTexture,
                         SDL_Rect*    pClip,
                         SDL_Point*   pCenter)
:img(imgTexture)
{
	if(pClip!=NULL)
		clip=*pClip;
	if(pCenter!=NULL)
		center=*pCenter;
}
bool object_base::isCollise(const object_base& other,
                            const point&       pos1,
                            double             rot1,
                            const point&       pos2,
                            double             rot2)
{
	int M=shape.size();
	int N=other.shape.size();
	int i,j;
	for(i=0;i<M;++i)
	{
		for(j=0;j<N;++j)
		{
			if(    !shape[i]->isSeperate(*(other.shape[j]),pos1,rot1,pos2,rot2)
			    && !other.shape[j]->isSeperate(*(shape[i]),pos2,rot2,pos1,rot1)
			  )
				return true;
		}
	}
	return false;
}
void object_base::draw(SDL_Renderer *gRenderer,
                       const point&  pos,
                       double        rot)
{
	SDL_Rect destRect(clip);
	destRect.x=pos.x-center.x;
	destRect.y=pos.y-center.y;
	if(img!=NULL)
		SDL_RenderCopyEx(gRenderer,img,&clip,&destRect,rot,&center,SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	for(int i=shape.size()-1;i>=0;--i)
	{
		if(shape[i]->type()==GEO_CIRCLE)
		{
			int k;
			double r=dynamic_cast<circle*>(shape[i])->radius;
			point c(dynamic_cast<circle*>(shape[i])->center);
			c.rotate(rot);
			c.x+=pos.x;
			c.y+=pos.y;
			for(int j=0;j<40;++j)
			{
				k=(j+1)%40;
				SDL_RenderDrawLine(gRenderer,c.x+r*cos(j/20.0*PI),c.y+r*sin(j/20.0*PI)
					,c.x+r*cos(k/20.0*PI),c.y+r*sin(k/20.0*PI));
			}
		}
		else
		{
			int N=dynamic_cast<polygen*>(shape[i])->points.size(),k;
			point p,q;
			for(int j=0;j<N;++j)
			{
				k=(j+1)%N;
				p=dynamic_cast<polygen*>(shape[i])->points[j];
				q=dynamic_cast<polygen*>(shape[i])->points[k];
				p.rotate(rot);
				q.rotate(rot);
				
				SDL_RenderDrawLine(gRenderer,p.x+pos.x,p.y+pos.y,q.x+pos.x,q.y+pos.y);
			}
		}
	}
}
