#include "HandleInfo.h"


HandleInfo::HandleInfo(DWORD processId, HWND handleId, TCHAR* processTitle, TCHAR* processPath)
{
    this->processId = (unsigned long long int)processId;
    this->handle_HWND = handleId;
    this->handleId = (unsigned long long int)handleId;
    this->processTitle = TCharArrayToQString(processTitle);
    this->processPath = TCharArrayToQString(processPath);
}

QString HandleInfo::TCharArrayToQString(TCHAR* tcharArray)
{
    if (tcharArray)
    {
        int length = WideCharToMultiByte(CP_ACP, 0, tcharArray, -1, NULL, 0, NULL, NULL);
        char* charArray = new char[length * sizeof(char)];
        WideCharToMultiByte(CP_ACP, 0, tcharArray, -1, charArray, length, NULL, NULL);
        std::string str(charArray);
        delete[] charArray;
        return QTextCodec::codecForLocale()->toUnicode((str).c_str());
    }
    else
    {
        return QString("");;
    }
}
