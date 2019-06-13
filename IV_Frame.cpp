#include "IV_Frame.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#include "IV_ImgManager.h"

#endif

enum
{
    // menu items
            Minimal_Quit = wxID_EXIT,
            Minimal_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(IV_Frame, wxFrame)
	EVT_SIZE(IV_Frame::OnResize)
    EVT_PAINT(IV_Frame::OnPaint)
    EVT_MENU(Minimal_About, IV_Frame::OnAbout)
wxEND_EVENT_TABLE()


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
IV_Frame::IV_Frame()
        : wxFrame(NULL, wxID_ANY,"ImageViewer")
{
    // set the frame icon
    SetIcon(wxICON(sample));
    //set to guide mode
    mode=GUIDE;
    imgManager= nullptr;
    screenCache=new wxBitmap(GetClientSize(),32);
	refresh();
}
IV_Frame::IV_Frame(const wxString path)
        : wxFrame(NULL, wxID_ANY,path)
{
    // set the frame icon
    SetIcon(wxICON(sample));
    //set to image mode  and initialize
    mode=IMAGE;
    imgManager=new IV_ImgManager(path);
    OpenFile(path);
	screenCache=new wxBitmap(GetClientSize(),32);
	refresh();
}

// event handlers
void IV_Frame::OnResize(wxSizeEvent& event){
	delete screenCache;
	screenCache=new wxBitmap(GetClientSize(),32);
	refresh();
}
void IV_Frame::OnPaint(wxPaintEvent &event) {
    wxPaintDC paintDC(this);
    paintDC.Clear();
    paintDC.DrawBitmap(*screenCache,0,0,false);
}
void IV_Frame::OnClose(wxCommandEvent &event) {
	if(imgManager!= nullptr){
		delete imgManager;
	}
	if(screenCache!= nullptr){
		delete screenCache;
	}
}
void IV_Frame::OnOpenFile(wxCommandEvent &event) {
	wxString path;
	path = wxLoadFileSelector("image", wxEmptyString);
	if(path==wxEmptyString){
		//do nothing
	}else{

	}
}
void IV_Frame::OnCloseFile(wxCommandEvent &event) {
	mode = MODE::IMAGE;
	if (imgManager != nullptr) {
		delete imgManager;
	}
	mode=GUIDE;
	refresh();
}
void IV_Frame::OnMouseScroll(wxMouseEvent& event){
	if(mode==GUIDE){
		//do nothing
	}else if(mode==IMAGE && imgManager->getStatus()==IV_ImgManager::STATUS::FINE){
		//这个算法远远不够，应该做到的效果是以鼠标当前位置为中心进行放缩
		double &zoom=imgManager->getCurrentImage().m_displayConf.zoom;
		zoom+=event.m_wheelRotation/100.0;
		if(zoom>10){
			zoom=10;
		}else if(zoom <0.1){
			zoom=0.1;
		}
		refresh();
	}
}
void IV_Frame::OnMouseClick(wxMouseEvent& event){
	if(mode==MODE::GUIDE){

	}else if(mode==MODE::IMAGE){
		if(正常){
			bar.onMove(event)
		}
	}
}
void IV_Frame::OnKeyboard(wxKeyEvent& event){
	if(mode==MODE::GUIDE){

	}else if(mode==MODE::IMAGE){

	}
}
void IV_Frame::OnAbout(wxCommandEvent& WXUNUSED(event))
{

    wxMessageBox(wxString::Format
                         (
                                 "Image Viewer\n"
                                 "Powered by %s!,\n"
                                 "Under %s.\n",
                                 wxVERSION_STRING,
                                 wxGetOsDescription()
                         ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}
void IV_Frame::OpenFile(wxString path){
	IV_ImgManager *imgManagerTMP=new IV_ImgManager(path);
	if(imgManagerTMP->getStatus()==IV_ImgManager::STATUS::FINE){
		if(imgManager!= nullptr){
			delete imgManager;
			imgManager= nullptr;

		}
		imgManager=imgManagerTMP;
		mode=MODE::IMAGE;
		refresh();
	}else{
		wxLogError("Fail to open directory %s",path);
		delete imgManagerTMP;
	}
}
void IV_Frame::CloseFile(){
	if(imgManager!= nullptr){
		delete imgManager;
		imgManager= nullptr;
	}
}
void IV_Frame::refresh() {
	if(mode=MODE::GUIDE){

	}else(mode=MODE::IMAGE){

	}
}
