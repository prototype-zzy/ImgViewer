#include "imageAdapter.h"

imageAdapter::imageAdapter(wxString path){
	//对所有指针类型的变量进行初始化，损失一点点性能方便通过检查是否为nullptr，方便资源回收
	bitmapCache= nullptr;
	m_wxImage= nullptr;
	//目前只考虑通过wxImage导入第一张图片
	m_wxImage=new wxImage();
	if(m_wxImage->LoadFile(path)){
		m_imgType=IMG_TYPE::PLAIN;
		bitmapCache=new wxBitmap(*m_wxImage);
	}else{
		m_imgType=IMG_TYPE::FAILED;
		delete m_wxImage;
	}
}

imageAdapter::~imageAdapter(){
	if(m_wxImage!= nullptr){
		delete m_wxImage;
	}
	//在FAIL情况下，能够保证bitmapCache=nullptr，所以剩下的情况九只有单图片|多图片格式了
	if(bitmapCache!= nullptr){
		if(m_imgType==PLAIN){
			delete bitmapCache;
		}else{
			delete[] bitmapCache;
		}
	}
}

enum imageAdapter::IMG_TYPE imageAdapter::getImgType(){
	return m_imgType;
}
const wxBitmap& imageAdapter::getBitmap(){
	return *bitmapCache;
}
//展示就这样吧这样吧
const wxBitmap& imageAdapter::getBitmap(int num){
	return *bitmapCache;
}
