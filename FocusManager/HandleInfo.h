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
    unsigned long long int processId;
    unsigned long long int handleId;
    QString processTitle;
    QString processPath;
    HWND handle_HWND;

private:
    QString TCharArrayToQString(TCHAR* tcharArray=NULL);     // TChar数组转化为str::string，最终转化为QString ————Unicode
};

#endif

