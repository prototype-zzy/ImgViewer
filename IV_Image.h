#pragma once


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "imageAdapter.h"

/*
 * IV_Image只是一个用来封装显示素材的类，显示的操作应当由显示相关类（预计也可以做成虚基类/子类实现来实现多功能）来做
 */
class IV_Image {
public:
	IV_Image(wxString path);
	virtual  ~IV_Image();
	imageAdapter m_imageAdapter;
	void paint(wxMemoryDC &memDC);
	//注意方所函数需要考虑镜像、旋转、放缩、中心的问题，所以不要直接控制image内部的属性来调用
	void zoomBy(double delta_zoom,wxPoint zoomed_dcenter);	//这个zoomed_dcenter名字没取好，它的意思本来是在canvas上缩放中心和实际中心（也就是center渲染到的那个点的距离）
	void zoomTo(double zoom_new,wxPoint zoom_center);
	void zoom100(wxSize canvasSize);
	void rotate(bool CLOCKWISEorAnti);	//true代表顺时针旋转90度，false代表逆时针旋转90度
	void mirror(bool HORIZONTALorVertical);
	void switchImage(bool NEXTorLast);	//true代表切到下一张，false代表切到上一张
	double getZoom();
private:
	enum ROTATION{
		R0=0,
		R90=1,
		R180=2,
		R270=3
	};
	wxPoint center;
	double zoom;
	enum ROTATION rotation;
	bool horizontal_mirror;
	bool vertical_mirror;
};
