#include "geometry.hpp"
#include <cmath>
#define PI 3.1415926535
//=============point=============
point::point(double ix,double iy)
	:x(ix),y(iy)
{
}
void point::rotate(double degree)
{
	double c=cos(degree/180.0*PI);
	double s=sin(degree/180.0*PI);
	double tx=x;
	x=x*c-y*s;
	y=tx*s+y*c;
}
double point::project(const point &axis)const
{
	double l=sqrt(axis.x*axis.x+axis.y*axis.y);
	return (x*axis.x+y*axis.y)/l;
}
//=============geometry_base=============
geometry_base::geometry_base(/*const point& Position,double Rotation)
	:position(Position),rotation(Rotation*/)
{
}
bool geometry_base::isOverlap(double min1,double max1,double min2,double max2)const
{
	return !(min2>max1 || min1>max2);
}

//=============circle=============
circle::circle(const point& Position,double Radius)
	:center(Position),radius(Radius)
{
}
void circle::projection(const point& axisVec,double& min,double& max,const point& pos,double rot)const
{
	point p(center);
	p.rotate(rot);
	p.x+=pos.x;
	p.y+=pos.y;
	double x=p.project(axisVec);
	min=x-radius;
	max=x+radius;
}
bool circle::isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const
{
	int objType=obj.type();
	if(objType==GEO_CIRCLE)
	{
		point c1(center),c2(dynamic_cast<const circle&>(obj).center);
		c1.rotate(rot1);
		c2.rotate(rot2);
		double dx=(pos1.x+c1.x)-(pos2.x+c2.x);
		double dy=(pos1.y+c1.y)-(pos2.y+c2.y);
		double R=radius+dynamic_cast<const circle&>(obj).radius;
		return dx*dx+dy*dy>R*R;
	}
	else if(objType==GEO_POLYGEN || objType==GEO_RECT)
	{
		point p,q,c(center);
		double min,max,Max,Min;
		c.rotate(rot1);
		c.x+=pos1.x;
		c.y+=pos1.y;
		dynamic_cast<const polygen&>(obj).closePoint(c,p,pos2,rot2);
		q.x=p.x-c.x;
		q.y=p.y-c.y;
		obj.projection(q,min,max,pos2,rot2);
		projection(q,Min,Max,pos1,rot1);
		if(!isOverlap(min,max,Min,Max))
			return true;
		return false;
	}
	return false;
}
int circle::type()const
{
	return GEO_CIRCLE;
}




polygen::polygen()
{
	
}
void polygen::closePoint(const point& src_p,point& dest_p,const point& pos,double rot)const
{
	if(points.size()==0)
		return;
	point p,dp;
	double min,r;
	int t=0;
	
	p.x=src_p.x-pos.x;
	p.y=src_p.y-pos.y;
	p.rotate(-rot);
	
	dp.x=p.x-points[0].x;
	dp.y=p.y-points[0].y;
	min=sqrt(dp.x*dp.x+dp.y*dp.y);
	
	for(int i=points.size()-1;i>0;--i)
	{
		dp.x=p.x-points[i].x;
		dp.y=p.y-points[i].y;
		r=sqrt(dp.x*dp.x+dp.y*dp.y);
		if(r<min)
		{
			t=i;
			min=r;
		}
	}
	dest_p=points[t];
	dest_p.rotate(rot);
	dest_p.x+=pos.x;
	dest_p.y+=pos.y;
}
void polygen::projection(const point& axisVec,double& min,double& max,const point& pos,double rot)const
{
	if(points.size()==0)
		return;
	double x;
	point p;
	
	p=points[0];
	p.rotate(rot);
	p.x+=pos.x;
	p.y+=pos.y;
	x=p.project(axisVec);
	
	max=min=x;
	for(int i=points.size()-1;i>0;--i)
	{
		p=points[i];
		p.rotate(rot);
		p.x+=pos.x;
		p.y+=pos.y;
		x=p.project(axisVec);
		if(x>max)
			max=x;
		if(x<min)
			min=x;
	}
}
bool polygen::isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const
{
	int N=points.size(),j;
	point axis,d;
	double max,min,Max,Min;
	if(N<3)
		return false;
	for(int i=0;i<N;++i)
	{
		j=(i+1)%N;
		axis.y=points[j].x-points[i].x;
		axis.x=-(points[j].y-points[i].y);
		axis.rotate(rot1);
		obj.projection(axis,min,max,pos2,rot2);
		projection(axis,Min,Max,pos1,rot1);
		if(!isOverlap(min,max,Min,Max))
			return true;
	}
	return false;
}
int polygen::type()const
{
	return GEO_POLYGEN;
}
//舉行

rect::rect(const point& P1,const point& P2)
	:width(fabs(P1.x-P2.x)),height(fabs(P1.y-P2.y))
{
	points.push_back(P1);
	points.push_back(point(P2.x,P1.y));
	points.push_back(P2);
	points.push_back(point(P1.x,P2.y));
}
void rect::setRect(double start_x,double start_y,double Width,double Height)
{
	width=Width;
	height=Height;
	points[3].x=points[0].x=start_x;
	points[2].x=points[1].x=start_x+width;
	points[1].y=points[0].y=start_y;
	points[2].y=points[3].y=start_y+height;
}
bool rect::isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const
{
	point axis(1,0);
	double min,max,Min,Max;
	
	axis.rotate(rot1);
	obj.projection(axis,min,max,pos2,rot2);
	projection(axis,Min,Max,pos1,rot1);
	if(!isOverlap(min,max,Min,Max))
		return true;
	
	axis.rotate(90);
	obj.projection(axis,min,max,pos2,rot2);
	projection(axis,Min,Max,pos1,rot1);
	if(!isOverlap(min,max,Min,Max))
		return true;
}
int rect::type()const
{
	return GEO_RECT;
}

