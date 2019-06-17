#pragma once

#include "wx/wxprec.h"
#include "wx/dir.h"
#include "wx/filefn.h" 
#include "wx/filename.h"
#include "wx/vector.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "IV_Image.h"
/*
 * 要求这个类能够
 * 管理多个VI_Image并且能够进行切换和缓存
 * 在源文件发生变化的时候能够析构老的Image并加载新的Image
 * 在文件夹文件目录发生改变的时候也需要重新排一下
 */
/*
 * 之后成功了可以把这个累改成一个虚基类，分别实现积极预读和懒惰读取，看看哪种方案的效率更高，或者讲选择权交给用户
 */
class IV_ImgManager {
public:
	/*
	 * 一个理想化的IV_ImgManager，只有1个构造函数，这个构造函数参数为wxString，意义为path
	 * 这个path会被解析，
	 * 如果解析失败，那么IV_ImgManager的getStatus()返回ILLEGAL_PATH
	 * 如果解析成功且解析为文件夹，默认currentImage为该文件夹中根据自有匹配机制匹配到的第一个图片（注意文件夹里不存在匹配图片的情况）
	 * 如果解析成功且解析为文件，则检查从文件名来看是否符合匹配格式：那么IV_ImgManager的getStatus()返回ILLEGAL_PATH；若是，尝试加载
	 * 此时还不能使用switch2Next()和switch2Last()两个函数，hasLastImage()和hasNextImage()也都会返回false
	 * 要想使用以上函数，需要调用preload()函数（这个函数名没取好，不够形象）
	*/
	enum STATUS{
		ILLEGAL_PATH,
		EMPTY_DIR,
		FINE
	};

	IV_ImgManager(wxString path);
	~IV_ImgManager();
	bool hasLastImage();//弃用
	bool hasNextImage();//弃用
	const enum STATUS getStatus();
	const wxString getPath();	//返回初始化时的地址
	IV_Image& getCurrentImage();
	void switch2Next();
	void switch2Last();
	void preload();	
	wxString getFileName();
private:
	IV_Image *imgTMP;

	STATUS state;
	wxString fileName;//仅文件名(带后缀)
	wxString filePath;//仅路径
	wxString fullName;//全路径加文件名
	wxString nextFile;//全路径加文件名
	wxString lastFile;//同上
	wxString fileExt;//后缀（自动转换为小写）
	wxVector<wxString> fileList;

	bool setFileList(wxString path);     //创建目标目录下的文件名列表  
	bool setNextAndLast();    //创建当前图片的上一张、下一张              
	wxString judgeSuffix(wxString name);         //判断后缀是否为图片（参数为全路径+文件名）,不是则返回""                
};