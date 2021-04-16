﻿#include "WindowsHandle.h"
#include<QDebug>



HandleInfo WindowsHandle::getHandleInfoFromHWND(HWND handle)
{
	if (!handle)
	{
		return HandleInfo();
	}

	// 获取标题
	TCHAR focusAppTitle[200] = { 0 };
	::GetWindowText(handle, focusAppTitle, 20);

	// 获取路径
	TCHAR focusAppPath[MAX_PATH + 1] = { 0 };
	TCHAR buffer[MAX_PATH + 1] = { 0 };
	DWORD idProcess;
	::GetWindowThreadProcessId(handle, &idProcess);	// 通过进程句柄获取进程id

	// 获取进程路径 参数1：进程ID 参数2：缓冲区指针，接收路径
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, idProcess);
	if (hProcess == NULL)
	{
		return NULL;
	}
	HMODULE hModule;
	DWORD cbNeeded;
	if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cbNeeded))
	{
		if (GetModuleFileNameEx(hProcess, hModule, buffer, MAX_PATH))
		{
			RtlMoveMemory((void*)focusAppPath, buffer, sizeof(TCHAR) * MAX_PATH);
		}
	}
	else {
		DWORD size = MAX_PATH;
		if (QueryFullProcessImageName(hProcess, 0, buffer, &size))
		{
			RtlMoveMemory((void*)focusAppPath, buffer, sizeof(TCHAR) * MAX_PATH);
		}
	}
	CloseHandle(hProcess);


	return HandleInfo(idProcess, handle, focusAppTitle, focusAppPath);
}

HandleInfo WindowsHandle::getCurrentSystemFocus()
{
    HWND handle = ::GetForegroundWindow();  // 获取当前焦点应用的句柄

	return getHandleInfoFromHWND(handle);
}

void WindowsHandle::setHandleFocus(HandleInfo handle)
{
	if (IsIconic(handle.handle_HWND)) 
	{
		ShowWindow(handle.handle_HWND, SW_SHOWNORMAL);	// 让窗口正常显示
	}
	::SetForegroundWindow(handle.handle_HWND);
	::SetActiveWindow(handle.handle_HWND);
}