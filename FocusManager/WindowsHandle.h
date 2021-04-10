#ifndef WINDOWSHANDLE_H
#define WINDOWSHANDLE_H

// 以下为win32 API库，不支持跨平台，"User32.dll"
#include"windows.h"
#include"winuser.h"
#include"TChar.h"
#include"psapi.h"
#include"HandleInfo.h"
#include"errhandlingapi.h"

class WindowsHandle
{
public:
    static HandleInfo getCurrentSystemFocus();              // 获取当前焦点信息
    static HandleInfo getHandleInfoFromHWND(HWND handle);
    static void setHandleFocus(HandleInfo handle);          // 使某个handle获取焦点
};

#endif
