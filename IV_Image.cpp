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
void IV_Image::paint(wxMemoryDC &memDC){
	memDC.SetUserScale(zoom,zoom);
	memDC.DrawBitmap
		(
			m_imageAdapter.getBitmap(),
			memDC.DeviceToLogicalX(memDC.GetSize().x/2-zoom*center.x),
			memDC.DeviceToLogicalY(memDC.GetSize().y/2-zoom*center.y),
			true
		);
}