#pragma once


#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class IV_Toolbar {
public:
	IV_Toolbar(wxFrame *parent);
	void OnClick(wxMouseEvent &event);
	void OnMove(wxMouseEvent &event);
	void OnPaint(wxMemoryDC &memDC);
private:
	wxFrame *parent;
	bool isHovered;
	enum BUTTON{
		NONE,
		ZOOM_IN,
		ZOOM_OUT,
		ZOOM_100,
		ROTATE,
		HORIZONTAL_MIRROR,
		VERTICAL_MIRROR,
		NEXT_IMG,
		LAST_IMG,
	};
};