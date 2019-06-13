#include "IV_Frame.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

#include "IV_ImgManager.h"
#include "IV_toolbar.h"
#include "IV_imgSwitcher.h"

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
	EVT_CLOSE(IV_Frame::OnClose)
	EVT_SIZE(IV_Frame::OnResize)
    EVT_PAINT(IV_Frame::OnPaint)
//
//    EVT_MENU(Minimal_About, IV_Frame::OnAbout)
wxEND_EVENT_TABLE()


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
IV_Frame::IV_Frame()
        : wxFrame(NULL, wxID_ANY,"ImageViewer"),
		  toolbar(this),
		  imgSwitcher(this)
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
        : wxFrame(NULL, wxID_ANY,path),
		  toolbar(this),
		  imgSwitcher(this)
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
void IV_Frame::OnClose(wxCloseEvent &event){
	if(imgManager!= nullptr){
		delete imgManager;
	}
	if(screenCache!= nullptr){
		delete screenCache;
	}
	Destroy();
}
void IV_Frame::OnResize(wxSizeEvent &event){
	delete screenCache;
	screenCache=new wxBitmap(GetClientSize(),32);
	refresh();
}
void IV_Frame::OnPaint(wxPaintEvent &event) {
//	wxPaintDC dc(this);
//	dc.SetPen(*wxYELLOW_PEN);
//	dc.Clear();
//	dc.DrawLine(0,0,GetClientSize().x,GetClientSize().y);
	wxClientDC dc(this);
	dc.SetPen(*wxYELLOW_PEN);
	dc.Clear();
	dc.DrawLine(0,0,GetClientSize().x,GetClientSize().y);


//    wxPaintDC paintDC(this);
//    paintDC.Clear();
//    paintDC.DrawBitmap(*screenCache,0,0,false);
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
		IV_Image &image=imgManager->getCurrentImage();
		if(image.m_imageAdapter.getImgType()!=imageAdapter::IMG_TYPE::FAILED){
			wxSize clientSize=GetClientSize();
			wxPoint mousePos=event.GetPosition();
			wxPoint dcenter(mousePos.x-clientSize.x/2.0,mousePos.y-clientSize.y/2.0);
			image.zoomBy(1.0*event.m_wheelRotation/100,dcenter);
		}
	}
}
void IV_Frame::OnMouseClick(wxMouseEvent& event){
	if(mode==MODE::GUIDE){

	}else if(mode==MODE::IMAGE){

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
                 "About  ImgViewer",
                 wxOK | wxICON_INFORMATION,
                 this);
}

//私有方法
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
	if(mode==MODE::GUIDE){

	}else {
		//wxLogMessage("123");
////		wxBitmap abc(300,300);
////		wxMemoryDC memDC(abc);
////		memDC.SetPen(*wxGREEN_PEN);
////		memDC.DrawLine(0,0,200,200);
////		memDC.Clear();
////		switch(imgManager->getStatus()){
////			case IV_ImgManager::STATUS::FINE:
////				if(imgManager->getCurrentImage().m_imageAdapter.getImgType()!=imageAdapter::IMG_TYPE::FAILED){
////					imgManager->getCurrentImage().paint2cache(memDC);
////				}else{
////
////				}
////				break;
////			case IV_ImgManager::STATUS::EMPTY_DIR:
////				break;
////			case IV_ImgManager::STATUS::ILLEGAL_PATH:
////				break;
////		}
	}
}