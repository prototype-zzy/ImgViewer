#include "IV_toolbar.h"

IV_toolbar::IV_toolbar(wxFrame *parent){
	this->parent=parent;
	this->isHovered= false;
	this->hoveredButton=IV_toolbar::BUTTON::NONE;
}
void IV_toolbar::OnClick(wxMouseEvent &event, IV_ImgManager &imgManager){
	//如果在左右边界，调用前切/后切
	//如果在工具栏，视具体情况调用具体函数
	if (!isHovered)
		return;
	wxLogMessage("click:%d", (int)hoveredButton);
	switch ((int)hoveredButton) {
		case 1: {
			//imgManager.getCurrentImage().zoomTo();
			break;
		}
		case 2: {
			//imgManager.getCurrentImage().zoomTo();
			break;
		}
		case 3: {
			imgManager.getCurrentImage().zoom100(parent->GetSize());
			break;
		}
		case 4: {
			imgManager.getCurrentImage().rotate(true);
			break;
		}
		case 5: {
			imgManager.getCurrentImage().rotate(false);
			break;
		}
		case 6: {
			//imgManager.getCurrentImage().mirror();
			break;
		}
		case 7: {
			//imgManager.getCurrentImage().mirror();
			break;
		}
	}

}
void IV_toolbar::OnMove(wxMouseEvent &event){
	/*如果在控件范围内，检查isActive是否为真。
	 * 	若为真，则检查鼠标是不是在对应按钮上，按钮和之前的按钮是不是同一个，不是的话更新buttonHovered的值并调用refresh()
	 * 	若为假，则调用refresh()
	 *如果在控件范围外，检查isActive是否为真。
	 * 	若为真，则调用refresh()
	 * 	若为假，则将buttonHovered置NONE
	*/
	//wxLogMessage("%d %d", event.GetPosition().x, event.GetPosition().y);
	;
	toolbarPoint = wxPoint((parent->GetClientSize().x - toolbarSize.x) / 2, parent->GetClientSize().y - toolbarSize.y);
	wxPoint current = event.GetPosition();
	if (current.x >= toolbarPoint.x && current.y >= toolbarPoint.y && current.x <= toolbarPoint.x + toolbarSize.x && current.y <= toolbarPoint.y + toolbarSize.y) {
		if (isHovered == false || judgeHoveredButton(current ,toolbarPoint)) {//需要把toolbar刷出来
			isHovered = true;
			parent->Refresh();
		}
	}
	else {
		hoveredButton = NONE;
		if (isHovered == true) {//需要把toolbar刷没得
			isHovered = false;
			parent->Refresh();
		}
		
	}
	
	
	
}
void IV_toolbar::paint(wxPaintDC &paintDC) {
	//isHovered和buttonHovered进行绘图
	//颜色别太有特色，50%灰度的#000不错
	if (isHovered) {
		wxInitAllImageHandlers();
		wxBitmap toolbarBitmap = imageAdapter::imageAdapter("button\\toolbar.png").getBitmap();
		toolbarPoint = wxPoint((paintDC.GetSize().x - toolbarSize.x) / 2, paintDC.GetSize().y - toolbarSize.y);
		paintDC.DrawBitmap(toolbarBitmap, toolbarPoint);

		wxPoint highlightPiont;

		//以下是假高亮
		highlightPiont = wxPoint(toolbarPoint.x + (int)(hoveredButton - 1) * toolbarSize.y, toolbarPoint.y);
		if (hoveredButton != 0) {
			paintDC.SetPen(wxPen(wxColor(255, 255, 255, 20)));
			paintDC.SetBrush(wxBrush(wxColor(0, 0, 0, 20)));
			wxPoint p1 = highlightPiont;//左上
			wxPoint p2 = wxPoint(highlightPiont.x + toolbarSize.y, highlightPiont.y);//右上
			wxPoint p3 = wxPoint(highlightPiont.x, highlightPiont.y + toolbarSize.y);//左下
			wxPoint p4 = wxPoint(highlightPiont.x + toolbarSize.y, highlightPiont.y + toolbarSize.y);//右下
			paintDC.DrawLine(p1, p2);
			paintDC.DrawLine(p1, p3);
			paintDC.DrawLine(p2, p4);
			paintDC.DrawLine(p3, p4);
		}
		//wxLogMessage("%d", (int)hoveredButton);
	}
}
bool IV_toolbar::judgeHoveredButton(wxPoint current, wxPoint toolbarPoint) {//ture表示鼠标指向的按钮发生了变换，false表示没变,同时改变hoveredButton
	
	int a = (int)(current.x - toolbarPoint.x) / toolbarSize.y + 1;
	switch (a){
		case 1:{
			if (hoveredButton == ZOOM_OUT)
				return false;
			hoveredButton = ZOOM_OUT;
			break;
		}
		case 2:{
			if (hoveredButton == ZOOM_IN)
				return false;
			hoveredButton = ZOOM_IN;
			break;
		}case 3:{
			if (hoveredButton == ZOOM_100)
				return false;
			hoveredButton = ZOOM_100;
			break;
		}case 4:{
			if (hoveredButton == ROTATE_RIGHT)
				return false;
			hoveredButton = ROTATE_RIGHT;
			break;
		}case 5:{
			if (hoveredButton == ROTATE_LEFT)
				return false;
			hoveredButton = ROTATE_LEFT;
			break;
		}case 6:{
			if (hoveredButton == HORIZONTAL_MIRROR)
				return false;
			hoveredButton = HORIZONTAL_MIRROR;
			break;
		}case 7:{
			if (hoveredButton == VERTICAL_MIRROR)
				return false;
			hoveredButton = VERTICAL_MIRROR;
			break;
		}
		default:
			return false;
	}
	return true;
}

