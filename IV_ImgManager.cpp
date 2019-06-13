#include "IV_ImgManager.h"

//接下来的是一些测试用的函数
IV_ImgManager::IV_ImgManager(wxString path){
	imgTMP=new IV_Image(path);
}
bool IV_ImgManager::hasLastImage(){return false;}
bool IV_ImgManager::hasNextImage(){return false;}
const enum IV_ImgManager::STATUS IV_ImgManager::getStatus(){ return STATUS ::FINE;}
const wxString IV_ImgManager::getPath(){ return wxString("_M_E_M_O_R_Y_");}	//返回初始化时的地址
IV_Image& IV_ImgManager::getCurrentImage(){return *imgTMP;}
void IV_ImgManager::switch2Next(){}
void IV_ImgManager::switch2Last(){}
void IV_ImgManager::preload(){}	//preload函数要尽量地小，避免一次占用过多时间造成卡顿

