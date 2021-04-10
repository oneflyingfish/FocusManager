#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#include<QtWidgets/QWidget>
#include<QBoxlayout>
#include<QLineEdit>
#include<QLabel>
#include<QRadioButton>
#include<QButtonGroup>
#include<QComboBox>
#include<QGroupBox>
#include<QShortCut>
#include<QMessageBox>
#include<QFile>
#include<QJsonValue>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QByteArray>
#include<QDir>
#include<QSystemTrayIcon>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QDir>
#include<QApplication>
#include<QStandardPaths> 
#include"HandleInfo.h"
#include"WindowsHandle.h"
// 导入全局热键库，仅引用了windows平台的相关文件，实际上此库全平台支持：https://github.com/ddqd/qxtglobalshortcut5
#include"QxtGlobalShortcut/QxtGlobalShortcut.h"  
#include"WindowsHandle.h"

class FocusManager : public QWidget
{
    Q_OBJECT

public:
    FocusManager(QWidget *parent = Q_NULLPTR);
    ~FocusManager();

private slots:
    void lockFocusComboBoxActionChanged(QString text);
    void switchFocusComboBoxActionChanged(QString text);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void setAppStatus();
    void flushSwitchAction(bool status);

private:
    void setTrayIcon();
    void initGUI();                     // 初始化界面布局
    void initConfiguration();
    void recordConfiguration();
    void connectSignalAndSlot();
    void switchFocus();
    void lockFocus();
    bool eventFilter(QObject* o, QEvent* e);

private:
    QxtGlobalShortcut* switchFocusShortcut = new QxtGlobalShortcut(this);
    QxtGlobalShortcut* lockFocusShortcut = new QxtGlobalShortcut(this);
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
    QAction* switchAction;
    QAction* minimizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QMenu* trayIconMenu;

    // 焦点信息对象
    HandleInfo currentHandle;
    HandleInfo lockHandle;

    QDir configFilePath;

private:
    // 定义主体布局
    QVBoxLayout* mainBox = new QVBoxLayout();

    // 定义绑定焦点快捷键
    QHBoxLayout* lockFocusHBoxLayout = new QHBoxLayout();
    QLabel* lockFocusLabel = new QLabel(tr("绑定焦点快捷键: "));
    QComboBox* lockFocusComboBox = new QComboBox();


    // 定义焦点切换快捷键
    QHBoxLayout* switchFocusHBoxLayout = new QHBoxLayout();
    QLabel* switchFocusLabel = new QLabel(tr("切换焦点快捷键: "));
    QComboBox* switchFocusComboBox = new QComboBox();


    // 显示绑定焦点信息
    QVBoxLayout* lockFocusOnVBoxLayout = new QVBoxLayout();
    QGroupBox* lockFocusOnProgramNameGroupBox = new QGroupBox(tr("绑定焦点信息"));
    // 句柄号与进程名水平布局
    QHBoxLayout* lockFocusOnInfoHBboxLayout = new QHBoxLayout();
    //显示进程号
    QHBoxLayout* lockFocusOnProcessIdHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnProcessIdTipLabel = new QLabel(tr("进程号: "));
    QLabel* lockFocusOnProcessIdInfoLabel = new QLabel();
    // 显示句柄号
    QHBoxLayout* lockFocusOnHandleHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnHandleTipLabel = new QLabel(tr("句柄号: "));
    QLabel* lockFocusOnHandleInfoLabel = new QLabel();
    // 显示进程名
    QHBoxLayout* lockFocusOnProgramNameHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnProgramNameTipLabel = new QLabel(tr("应用标题: "));
    QLabel* lockFocusOnProgramNameInfoLabel = new QLabel();
    // 显示进程进程
    QHBoxLayout* lockFocusOnProgramPathHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnProgramPathTipLabel = new QLabel(tr("程序路径: "));
    QLineEdit* lockFocusOnProgramPathInfoLineEdit = new QLineEdit();


    // 显示当前焦点信息
    QVBoxLayout* currentFocusOnVBoxLayout = new QVBoxLayout();
    QGroupBox* currentFocusOnProgramNameGroupBox = new QGroupBox(tr("当前焦点信息"));
    // 句柄号与进程名水平布局
    QHBoxLayout* currentFocusOnInfoHBboxLayout = new QHBoxLayout();
    //显示进程号
    QHBoxLayout* currentFocusOnProcessIdHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnProcessIdTipLabel = new QLabel(tr("进程号: "));
    QLabel* currentFocusOnProcessIdInfoLabel = new QLabel();
    // 显示句柄号
    QHBoxLayout* currentFocusOnHandleHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnHandleTipLabel = new QLabel(tr("句柄号: "));
    QLabel* currentFocusOnHandleInfoLabel = new QLabel();
    // 显示进程名
    QHBoxLayout* currentFocusOnProgramNameHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnProgramNameTipLabel = new QLabel(tr("应用标题: "));
    QLabel* currentFocusOnProgramNameInfoLabel = new QLabel();
    // 显示进程进程
    QHBoxLayout* currentFocusOnProgramPathHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnProgramPathTipLabel = new QLabel(tr("程序路径: "));
    QLineEdit* currentFocusOnProgramPathInfoLineEdit = new QLineEdit();

    // 程序开关
    QButtonGroup* appSwitchButtonGroup = new QButtonGroup();
    QHBoxLayout* appSwitchHBoxLayout = new QHBoxLayout();
    QRadioButton* appOnRadioButton = new QRadioButton(tr("启用"));
    QRadioButton* appOffRadioButton = new QRadioButton(tr("关闭"));
};

#endif