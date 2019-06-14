#include "IV_App.h"
#include "IV_Frame.h"

wxIMPLEMENT_APP(IV_App);

/*
 * onInit()需要做到这几件事：
 * 为整个程序初始化各种支持库
 * 检查命令行参数：
 * 如果有，将命令行的每一个参数当成path传给IVFrame的构造函数，不需要验证path的合法性，IVFrame的构造函数知道怎么处理不合法的path
 * 如果没有命令行参数，直接调用无参IVFrame()，IVFrame会自己生成引导界面
 *
 */
/* 测试期间，为了求方便，OnInit()函数的作用暂时是初始化wxImageHandler并生成一个对话框来选定一个图片 */
bool IV_App::OnInit() {
    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();


    wxString path;
    path = wxLoadFileSelector("image", wxEmptyString);
    if (path != wxEmptyString) {
        IV_Frame *frame = new IV_Frame(path);
        frame->Show(true);
    }

    return true;
}