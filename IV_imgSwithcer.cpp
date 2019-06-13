#include "IV_imgSwithcer.h"

IV_imgSwithcer::IV_imgSwithcer(wxFrame *parent){
	this->parent=parent;
	this->isHovered=false;
	this->hoveredButton=IV_imgSwithcer::BUTTON::NONE;
}
void IV_imgSwithcer::OnClick(wxMouseEvent &event){
	//TO DO
}
void IV_imgSwithcer::OnMove(wxMouseEvent &event){
	//TO DO
}
void IV_imgSwithcer::OnPaint(wxMemoryDC &memDC){
	//TO DO
}