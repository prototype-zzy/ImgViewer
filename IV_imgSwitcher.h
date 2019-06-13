#pragma once



#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


class IV_imgSwitcher {
public:
	IV_imgSwitcher(wxFrame *parent);
	void OnClick(wxMouseEvent &event);
	void OnMove(wxMouseEvent &event);
	void OnPaint(wxMemoryDC &memDC);
private:
	wxFrame *parent;
	bool isHovered;
	enum BUTTON{
		NONE,
		LAST_IMG,
		NEXT_IMG
	};
	enum BUTTON hoveredButton;
};