#pragma once

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif


class IV_App : public wxApp{
public:
      virtual bool OnInit() wxOVERRIDE;
};