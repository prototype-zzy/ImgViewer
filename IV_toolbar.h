#pragma once


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "imageAdapter.h"
#include "IV_ImgManager.h"
const wxSize toolbarSize(448,64);
class IV_toolbar {
public:
	IV_toolbar(wxFrame *parent);
	void OnClick(wxMouseEvent &event, IV_ImgManager &imgManager);
	void OnMove(wxMouseEvent &event);
	void paint(wxPaintDC &paintDC);
private:
	wxPoint toolbarPoint;
	wxFrame *parent;
	bool isHovered;
	enum BUTTON{
		NONE,
		ZOOM_OUT,
		ZOOM_IN,
		ZOOM_100,
		ROTATE_RIGHT,
		ROTATE_LEFT,
		HORIZONTAL_MIRROR,
		VERTICAL_MIRROR,
	};
	enum BUTTON hoveredButton;
	bool judgeHoveredButton(wxPoint current, wxPoint toolbarPoint); //ture表示鼠标指向的按钮发生了变换，false表示没变
};