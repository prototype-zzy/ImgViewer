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
