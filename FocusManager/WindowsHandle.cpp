#include "WindowsHandle.h"
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
    HWND handle = ::GetForegroundWindow();				// 获取当前顶层应用的句柄
	HandleInfo info= getHandleInfoFromHWND(handle);
	info.activateHandle_HWND = ::GetActiveWindow();

	return info;
}

void WindowsHandle::setHandleFocus(HandleInfo handle)
{
	if (IsIconic(handle.handle_HWND)) 
	{
		ShowWindow(handle.handle_HWND, SW_SHOWNORMAL);	// 让窗口正常显示
	}
	::SetForegroundWindow(handle.handle_HWND);
	//::SetActiveWindow(handle.activateHandle_HWND);
}

bool WindowsHandle::setHandleMouseLocation(HandleInfo handleInfo)
{
	// 以下方法效果不稳定，暂时弃用
	//POINT point;
	//HWND handle = ::GetForegroundWindow();
	//DWORD currentID = ::GetCurrentThreadId();
	//DWORD processID = ::GetWindowThreadProcessId(handle, NULL);
	//if (AttachThreadInput(processID, currentID, TRUE))
	//{
	//	if (::GetCaretPos(&point)) 
	//	{
	//		if (point.x != 0 || point.y != 0)
	//		{
	//			// 坐标有意义
	//			ClientToScreen(::GetFocus(), &point);
	//			qDebug() << point.x << point.y << endl;
	//			::SetCursorPos(point.x + 5, point.y + 5);
	//		}
	//		else
	//		{
	//			qDebug() << GetLastError();
	//			// 切换到中间
	//			RECT widgetRect;
	//			::GetWindowRect(handle, &widgetRect);//通过窗口句柄获得窗口的大小存储在rctA结构中
	//			::SetCursorPos((widgetRect.right + widgetRect.left) / 2, (widgetRect.bottom + widgetRect.top) / 2);
	//		}

	//		AttachThreadInput(currentID, processID, FALSE);		// 解除线程贴附
	//		return true;
	//	}
	//	AttachThreadInput(currentID, processID, FALSE);
	//}

	RECT widgetRect;
	::GetWindowRect(handleInfo.handle_HWND, &widgetRect);		//通过窗口句柄获得窗口的大小存储在rctA结构中
	::SetCursorPos((widgetRect.right + widgetRect.left) / 2, (widgetRect.bottom + widgetRect.top) / 2);


	return true;
}