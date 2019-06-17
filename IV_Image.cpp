#include "IV_Image.h"

IV_Image::IV_Image(wxString path):m_imageAdapter(path){
	zoom=1;
	rotation=ROTATION ::R0;
	horizontal_mirror=0;
	vertical_mirror=0;
	if(m_imageAdapter.getImgType()!=imageAdapter::IMG_TYPE::FAILED){
		center.x=m_imageAdapter.getBitmap().GetSize().x/2;
		center.y=m_imageAdapter.getBitmap().GetSize().y/2;
	}
}
//按理说是需要有zoom，rotate，mirror的功能的。但是这几个功能交杂在一起,目前就只实现zoom功能了，反正接口留着，之后再回来补
void IV_Image::paint(wxPaintDC &paintDC){
	paintDC.SetUserScale(zoom,zoom);
	paintDC.DrawBitmap
		(
			m_imageAdapter.getBitmap(),
			paintDC.DeviceToLogicalX(paintDC.GetSize().x/2-zoom*center.x),
			paintDC.DeviceToLogicalY(paintDC.GetSize().y/2-zoom*center.y),
			true
		);
	paintDC.SetUserScale(1, 1);

}
//现在这些方法都还是空的
void IV_Image::zoomBy(double delta_zoom,wxPoint zoomed_dcenter){}	//这个zoomed_dcenter名字没取好，它的意思本来是在canvas上缩放中心(一般是鼠标指向的点)和实际中心（也就是center渲染到的那个点的距离）
void IV_Image::zoomTo(double zoom_new,wxPoint zoom_center){}
void IV_Image::zoom100(wxSize canvasSize){}
void IV_Image::rotate(bool CLOCKWISEorAnti){}	//true代表顺时针旋转90度，false代表逆时针旋转90度
void IV_Image::mirror(bool HORIZONTALorVertical){}
void IV_Image::switchImage(bool NEXTorLast){}	//true代表切到下一张，false代表切到上一张
double IV_Image::getZoom(){
	return zoom;
}