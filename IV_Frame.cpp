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
}
IV_Frame::IV_Frame(const wxString path)
		: IV_Frame()
{
	OpenFile(path);
}

// event handlers
void IV_Frame::OnClose(wxCloseEvent &event){
	if(imgManager!= nullptr){
		delete imgManager;
	}
	Destroy();
}
void IV_Frame::OnPaint(wxPaintEvent &event) {
	wxPaintDC paintDC(this);
	if(imgManager->getStatus()==IV_ImgManager::STATUS::FINE){
		if(imgManager->getCurrentImage().m_imageAdapter.getImgType()!=imageAdapter::IMG_TYPE::FAILED){
			imgManager->getCurrentImage().paint(paintDC);
			toolbar.paint(paintDC);
			imgSwitcher.paint(paintDC);
		}else{
			paintDC.DrawText(wxString("略略略"),wxPoint(0,0));
		}
	}else{
		paintDC.DrawText(wxString("略略略"),wxPoint(0,0));
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