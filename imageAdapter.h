#pragma once

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


//imgAdaptor重构啦
//新版的imgAdaptor把原有的Display功能去掉，只保留提供当前需要渲染的bitmap的引用的能力，从而做到全心全意地实现图片支持的功能

class imageAdapter {
public:
	//图像的处理器可能是原生wx，cairo2或者是freeImage等等等等，目前只实现原生wx支持
	//虽然需要支持例如GIF，TIFF，ICO这样的多文件格式，不过现在还不准备支持，目前这些当成plain处理，只能得到第1张图
	enum IMG_TYPE{
		FAILED,
		PLAIN,
		GIF,
		TIFF,
		ICO
	};
	imageAdapter(wxString path);
    virtual ~imageAdapter();
    enum IMG_TYPE getImgType();
    int getImgNum();
    //getBitmap之前一定要观察image有没有就绪（是不是fail状态），否则后果自负
    const wxBitmap& getBitmap();
	//虽然需要支持例如GIF，TIFF，ICO这样的多文件格式，不过现在还不准备支持，目前这些当成plain处理，只能得到第1张图
	const wxBitmap& getBitmap(int num);
private:
    wxBitmap *bitmapCache;
    enum IMG_TYPE m_imgType;
    wxImage *m_wxImage;
};