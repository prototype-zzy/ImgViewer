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
//����˵����Ҫ��zoom��rotate��mirror�Ĺ��ܵġ������⼸�����ܽ�����һ��,Ŀǰ��ֻʵ��zoom�����ˣ������ӿ����ţ�֮���ٻ�����
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
//������Щ���������ǿյ�
void IV_Image::zoomBy(double delta_zoom,wxPoint zoomed_dcenter){}	//���zoomed_dcenter����ûȡ�ã�������˼��������canvas����������(һ�������ָ��ĵ�)��ʵ�����ģ�Ҳ����center��Ⱦ�����Ǹ���ľ��룩
void IV_Image::zoomTo(double zoom_new,wxPoint zoom_center){}
void IV_Image::zoom100(wxSize canvasSize){}
void IV_Image::rotate(bool CLOCKWISEorAnti){}	//true����˳ʱ����ת90�ȣ�false������ʱ����ת90��
void IV_Image::mirror(bool HORIZONTALorVertical){}
void IV_Image::switchImage(bool NEXTorLast){}	//true�����е���һ�ţ�false�����е���һ��
double IV_Image::getZoom(){
	return zoom;
}