# 焦点快速切换（焦点管理工具）
基于`QT C++`和`Win32 API`编写的焦点快速切换工具，旨在将某个快捷键与特定的应用窗口绑定，使得可以通过快捷键在此应用和当前正在使用的应用之间快速来回切换。

## 开发环境
开发语言：`C++`  
开发环境：`QT 5.14.2 、 Windows 10 64位 + Visual Stdio 2019 Community`   
第三方库：`QxtGlobalShortcut`（支持全平台），代码已附含，暂仅在项目中引用windows相关 

## 运行环境
操作系统：`Windows Vista及以上`  
注：通过替换`HandleInfo`和`WindowsHandle`中相关`Win 32 API`的调用，并修改对`QxtGlobalShortcut`库文件的引用，可以将应用适配为跨平台应用。若要适配开机自启动，应考虑修改`FocusManager.cpp`中的注册表内容

## 支持语言

* 中文
* English

## 应用举例
* 对于两块屏幕的用户（屏幕上分别有应用A，B），可通过快捷键在A，B之间快速切换，而不用鼠标指定。 
* 您可以在使用某个程序A时，快速从后台调出某程序B（例如即时通讯软件）并进入可编辑状态，随后快速切换回A，而免去鼠标操作 
* 其它

## 二进制下载：
* [windows安装包](https://github.com/oneflyingfish/FocusManager/releases/tag/V1.0.0)
