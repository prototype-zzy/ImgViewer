#include "IV_ImgManager.h"

//接下来的是一些测试用的函数    

IV_ImgManager::IV_ImgManager(wxString path){
	if (wxFileExists(path) && judgeSuffix(path) != "") {      //判断文件是否存在,且为图片格式    
		fileName = wxFileNameFromPath(path);
		filePath = wxPathOnly(path);
		fullName = path;
		fileExt = judgeSuffix(path);
	}
	else {
		state = ILLEGAL_PATH;
		return;
	}
	setFileList(filePath);
	setNextAndLast();
	
	imgTMP=new IV_Image(path);
	state = FINE;
}

IV_ImgManager::~IV_ImgManager() {}

bool IV_ImgManager::hasLastImage(){return false;}//弃用    

bool IV_ImgManager::hasNextImage(){return false;}//弃用    

const enum IV_ImgManager::STATUS IV_ImgManager::getStatus() { return state;}

const wxString IV_ImgManager::getPath(){ return fullName;}	//返回初始化时的地址    

IV_Image& IV_ImgManager::getCurrentImage(){return *imgTMP;}

void IV_ImgManager::switch2Next() {
	if (!wxFileExists(nextFile)) {
		if (!setFileList(filePath))
			return;    //文件夹没了（被删了）     
		if (!setNextAndLast())
			return;       //当前文件没了（被删了）        

	}
	delete imgTMP;
	fileName = wxFileNameFromPath(nextFile);
	fullName = nextFile;
	imgTMP = new IV_Image(nextFile);
	setFileList(filePath);
	setNextAndLast();
}

void IV_ImgManager::switch2Last(){
	if (!wxFileExists(lastFile)) {
		if (!setFileList(filePath))
			return;//文件夹没了（被删了）    
		if (!setNextAndLast())
			return;//当前文件没了（被删了）   
	}
	delete imgTMP;
	fileName = wxFileNameFromPath(lastFile);
	fullName = lastFile;
	imgTMP = new IV_Image(lastFile);
	setFileList(filePath);
	setNextAndLast();
}

void IV_ImgManager::preload(){}	           //preload函数要尽量地小，避免一次占用过多时间造成卡顿    

wxString IV_ImgManager::judgeSuffix(wxString name) {        //判断后缀是否为图片（参数为全路径+文件名）,不是则返回""        
	wxFileName fullPathName(name);
	wxString Ext = fullPathName.GetExt();
	Ext.MakeLower();
	if (Ext == "jpg" || Ext == "jpeg" || Ext == "png" || Ext == "tif" || Ext == "gif" || Ext == "bmp" || Ext == "svg") {   ///////@hyb 你看看有哪些漏掉的格式          
		return Ext;
	}
	return "";
}

bool IV_ImgManager::setFileList(wxString path) {        //创建目标目录下的文件名列表              
	fileList.clear();
	if (!wxDirExists(path)) {
		state = EMPTY_DIR;
		return false;
	}
		
	wxString pathPattern = path + "/*.*";
	wxString f = wxFindFirstFile(pathPattern);
	while (!f.empty())
	{
		if (judgeSuffix(f) != "")
			fileList.push_back(f);
		f = wxFindNextFile();
	}
	return true;
}

bool IV_ImgManager::setNextAndLast() {                //创建当前图片件的上一张、下一张              
	for (int i = 0; i < fileList.size(); i++) {
		if (fullName == fileList.at(i)) {
			if (i != 0)
				lastFile = fileList.at(i - 1);
			else
				lastFile = fileList.at(fileList.size() - 1);
			if (i != (fileList.size() - 1))
				nextFile = fileList.at(i + 1);
			else
				nextFile = fileList.at(0);
			return true;
		}
	}
	state = ILLEGAL_PATH;
	return false;
}
wxString IV_ImgManager::getFileName() { return fileName; }