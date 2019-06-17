#include "IV_imgSwitcher.h"

IV_imgSwitcher::IV_imgSwitcher(wxFrame *parent){
	this->parent=parent;
	this->isHovered=false;
	this->hoveredButton=IV_imgSwitcher::BUTTON::NONE;
}
void IV_imgSwitcher::OnClick(wxMouseEvent &event, IV_ImgManager &imgManager){
	if (!isHovered)
		return;
	//wxLogMessage("click:%d", (int)hoveredButton);
	switch ((int)hoveredButton) {
		case 1: {
			imgManager.switch2Last();
			parent->Refresh();
			break;
		}
		case 2: {
			imgManager.switch2Next();
			parent->Refresh();
			break;
		}
	}
	parent->SetTitle("ImageViewer   " + imgManager.getFileName());

}
void IV_imgSwitcher::OnMove(wxMouseEvent &event){
	rightButtonPoint = wxPoint(parent->GetClientSize().x - buttonSize.x, (parent->GetClientSize().y - buttonSize.y) / 2);
	leftButtonPoint = wxPoint(0, (parent->GetClientSize().y - buttonSize.y) / 2);
	if (judgeHoveredButton(event.GetPosition(), rightButtonPoint, leftButtonPoint)) {
		if (isHovered == false) {
			isHovered = true;
			parent->Refresh();
		}
	}
	else {
		if (isHovered == true) {
			isHovered = false;
			parent->Refresh();
		}
	}
}
void IV_imgSwitcher::paint(wxPaintDC &paintDC){
	if (isHovered) {
		wxInitAllImageHandlers();
		wxBitmap rightButtonBitmap = imageAdapter::imageAdapter("button\\right.png").getBitmap();
		wxBitmap leftButtonBitmap = imageAdapter::imageAdapter("button\\left.png").getBitmap();
		rightButtonPoint = wxPoint(paintDC.GetSize().x - buttonSize.x, (paintDC.GetSize().y - buttonSize.y) / 2);
		leftButtonPoint = wxPoint(0, (paintDC.GetSize().y - buttonSize.y) / 2);

		paintDC.DrawBitmap(rightButtonBitmap, rightButtonPoint);
		paintDC.DrawBitmap(leftButtonBitmap, leftButtonPoint);
		//wxLogMessage("%d", (int)hoveredButton);
	}
}
bool IV_imgSwitcher::judgeHoveredButton(wxPoint current, wxPoint rightPoint, wxPoint leftPoint) {//trueÎªÐü¸¡£¬falseÎªÎ´Ðü¸¡£»Ðü¸¡Ê±»áÉèÖÃhoveredButton
	if (current.x > leftPoint.x && (current.x - leftPoint.x) < buttonSize.x && current.y > leftPoint.y && (current.y - leftPoint.y) < buttonSize.y) {
		hoveredButton = LAST_IMG;
		return true;
	}
	else if (current.x > rightPoint.x && (current.x - rightPoint.x) < buttonSize.x && current.y > rightPoint.y && (current.y - rightPoint.y) < buttonSize.y) {
		hoveredButton = NEXT_IMG;
		return true;
	}
	hoveredButton = NONE;
	return false;
}