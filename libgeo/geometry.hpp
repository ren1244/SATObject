#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <vector>
class point
{
public:
	//屬性
	double x;
	double y;
	//建構
	point(double ix=0.0,double iy=0.0);
	//操作
	void rotate(double degree); //旋轉:會直接改變點的內容！
	double project(const point &axis)const; //投影
};
enum geometryType{
	GEO_NONE,
	GEO_POLYGEN,
	GEO_RECT,
	GEO_CIRCLE
};
//基本
class geometry_base
{
public:
	//[共用函式]
	//建構
	geometry_base(/*const point& Position=point(0,0),double Rotation=0.0*/);
	//重疊判斷
	bool isOverlap(double min1,double max1,double min2,double max2)const;
	
	//[虛擬函式]
	//自己在axisVec軸上投影出來的位置
	virtual void projection(const point& axisVec,double& min,double& max,const point& pos,double rot)const=0;
	//以自己的軸來看，自己與obj是否分離
	virtual bool isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const=0;
	//回傳自己的類型ID
	virtual int type()const=0;
};
//圓形
class circle:public geometry_base
{
public:
	//屬性
	point center;
	double radius;
	//建構
	circle(const point& Position=point(0,0),double Radius=0.0);

	//[虛擬函式]
	//自己在axisVec軸上投影出來的位置
	virtual void projection(const point& axisVec,double& min,double& max,const point& pos,double rot)const;
	//以自己的軸來看，自己與obj是否分離
	virtual bool isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const;
	//回傳自己的類型ID
	virtual int type()const;
};

//多邊形
class polygen:public geometry_base
{
public:
	//屬性
	std::vector<point> points;
	
	//建構
	polygen();
	
	//找最近點：將距離src_p最近的點設定給dest_p
	void closePoint(const point& src_p,point& dest_p,const point& pos,double rot)const;

	//自己在axisVec軸上投影出來的位置
	virtual void projection(const point& axisVec,double& min,double& max,const point& pos,double rot)const;
	//以自己的軸來看，自己與obj是否分離
	virtual bool isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const;
	//回傳自己的類型ID
	virtual int type()const;
};
class rect:public polygen
{
private:
	double width;
	double height;
public:
	//建構:P1為左上座標，P2為右下座標，預設Origin為(0,0)
	rect(const point& P1=point(0,0),const point& P2=point(0,0));
	//重設尺寸:這邊的設定是相對於origin的值
	void setRect(double start_x,double start_y,double Width,double Height);
	//以自己的軸來看，自己與obj是否分離
	virtual bool isSeperate(const geometry_base& obj,const point& pos1,double rot1,const point& pos2,double rot2)const;
	//回傳自己的類型ID
	virtual int type()const;
};
#endif
