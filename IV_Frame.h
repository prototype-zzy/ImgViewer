#pragma once

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "IV_ImgManager.h"

/*
 * 对于这个类来说，正常的行为应当是：
 * 在GUIDE模式下，screenBuffer已经被初始化，但imgManager值为nullPtr
 * 在Image模式下，若imgManager正常，则
 * 打开失败的时候，自动切换到GUIDE模式下
 * 打开成功，但imgManager状态异常的时候，根据具体状态做具体操作
 */
class IV_Frame : public wxFrame{

public:
    // constructor(s)
    IV_Frame();
    IV_Frame(const wxString path);
	//不能直接写析构函数，这会覆盖掉父类的析构函数，而应该通过onClose()来解决(网上这么说，但是为什么呢)
    // event handlers (these functions should _not_ be virtual)
	void OnResize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnClose(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
	void OnCloseFile(wxCommandEvent& event);
	void OnMouseScroll(wxMouseEvent& event);
	void OnMouseClick(wxMouseEvent& event);
	void OnKeyboard(wxKeyEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    enum MODE{
        GUIDE,
        IMAGE
    };
    enum MODE mode;
    wxBitmap *screenCache;
    IV_ImgManager *imgManager;
    void OpenFile(wxString path);
    void CloseFile();
    void zoomBy(double delta_zoom);
    void zoomTo(double zoom_new);
    void lastImage();
    void nextImage();

    void refresh(); //该方法更新cache，并更新一次屏幕
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};