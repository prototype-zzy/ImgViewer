#pragma once



#include "wx/wxprec.h"
#include "imageAdapter.h"
#include "IV_ImgManager.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

const wxSize buttonSize(64,64);
class IV_imgSwitcher {
public:
	IV_imgSwitcher(wxFrame *parent);
	void OnClick(wxMouseEvent &event,IV_ImgManager &imgManager);
	void OnMove(wxMouseEvent &event);
	void paint(wxPaintDC &paintDC);
private:
	wxPoint rightButtonPoint;
	wxPoint leftButtonPoint;
	wxFrame *parent;
	bool isHovered;
	enum BUTTON{
		NONE,
		LAST_IMG,
		NEXT_IMG
	};
	enum BUTTON hoveredButton;
	bool judgeHoveredButton(wxPoint current, wxPoint rightPoint, wxPoint leftPoint);//true为悬浮，false为未悬浮；悬浮时会设置hoveredButton
};