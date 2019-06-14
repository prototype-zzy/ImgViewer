#include "IV_imgSwitcher.h"

IV_imgSwitcher::IV_imgSwitcher(wxFrame *parent){
	this->parent=parent;
	this->isHovered=false;
	this->hoveredButton=IV_imgSwitcher::BUTTON::NONE;
}
void IV_imgSwitcher::OnClick(wxMouseEvent &event){
	//TO DO
}
void IV_imgSwitcher::OnMove(wxMouseEvent &event){
	//TO DO
}
void IV_imgSwitcher::paint(wxPaintDC &paintDC){
	//TO DO
}