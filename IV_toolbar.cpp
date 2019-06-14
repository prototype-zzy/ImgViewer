#include "IV_toolbar.h"
IV_toolbar::IV_toolbar(wxFrame *parent){
	this->parent=parent;
	this->isHovered= false;
	this->hoveredButton=IV_toolbar::BUTTON::NONE;
}
void IV_toolbar::OnClick(wxMouseEvent &event){
	//如果在左右边界，调用前切/后切
	//如果在工具栏，视具体情况调用具体函数
}
void IV_toolbar::OnMove(wxMouseEvent &event){
	/*如果在控件范围内，检查isActive是否为真。
	 * 	若为真，则检查鼠标是不是在对应按钮上，按钮和之前的按钮是不是同一个，不是的话更新buttonHovered的值并调用refresh()
	 * 	若为假，则调用refresh()
	 *如果在控件范围外，检查isActive是否为真。
	 * 	若为真，则调用refresh()
	 * 	若为假，则将buttonHovered置NONE
	*/
}
void IV_toolbar::paint(wxPaintDC &paintDC){
	//isHovered和buttonHovered进行绘图
	//颜色别太有特色，50%灰度的#000不错
}