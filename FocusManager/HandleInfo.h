#ifndef HANDLEINFO_H
#define HANDLEINFO_H

#include<QString>
#include<QTextCodec>
#include"windows.h"
#include"winuser.h"
#include"TChar.h"
#include"psapi.h"

class HandleInfo
{
public:
    HandleInfo(DWORD processId=0, HWND handleId =0, TCHAR* processTitle = NULL, TCHAR* processPath=NULL);

public:
    unsigned long long int processId=0;
    unsigned long long int handleId=0;
    QString processTitle="";
    QString processPath="";
    HWND handle_HWND=0;
    HWND activateHandle_HWND=0;

private:
    QString TCharArrayToQString(TCHAR* tcharArray=NULL);     // TChar数组转化为str::string，最终转化为QString ————Unicode
};

#endif

