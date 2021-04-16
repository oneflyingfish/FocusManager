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
#include<QTranslator>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QSettings>
#include<QDir>
#include<QApplication>
#include<QStandardPaths> 
#include<QCheckBox.h>
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

public:
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon();

private slots:
    void setLanguageChinese(bool);
    void setLanguageEnglish(bool);
    void lockFocusComboBoxActionChanged(QString text);
    void switchFocusComboBoxActionChanged(QString text);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void setAppStatus();
    void flushSwitchAction(bool status);
    void autoRunConfig(int state);


private:
    void setDefaultValue();
    void setTrayIcon();
    void initGUI();                     // 初始化界面布局
    void initConfiguration();
    void recordConfiguration();
    void connectSignalAndSlot();
    void switchFocus();
    void lockFocus();
    bool eventFilter(QObject* o, QEvent* e);
    void flushUI();
    void initObjects();
    void setAutomaticSoftwareStartup(bool autoRun);

private:
    QxtGlobalShortcut* switchFocusShortcut = NULL;
    QxtGlobalShortcut* lockFocusShortcut = NULL;
    QAction* switchAction;
    QAction* minimizeAction;
    QAction* restoreAction;
    QAction* quitAction;
    QMenu* trayIconMenu;

    // 焦点信息对象
    HandleInfo currentHandle;
    HandleInfo lockHandle;

    QDir configFilePath;
    QTranslator translator;

private:
    // 定义主体布局
    QVBoxLayout* mainBox = NULL;
    QHBoxLayout* topHbox = NULL;

    // 快捷键设置
    QGroupBox* focusGroupBox = NULL;
    QVBoxLayout* focusVBox = NULL;
    // 定义绑定焦点快捷键
    QHBoxLayout* lockFocusHBoxLayout = NULL;
    QLabel* lockFocusLabel = NULL;
    QComboBox* lockFocusComboBox = NULL;

    // 定义焦点切换快捷键
    QHBoxLayout* switchFocusHBoxLayout = NULL;
    QLabel* switchFocusLabel = NULL;
    QComboBox* switchFocusComboBox = NULL;


    //定义设置功能按钮
    QGroupBox* appSetGroupBox = NULL;
    QVBoxLayout* appSetVBox = NULL;
    // 语言设置
    QHBoxLayout* languageHBoxLayout = NULL;
    QLabel* languageTipLabel = NULL;
    QButtonGroup* languageButtonGroup = NULL;
    QRadioButton* languageChineseRadioButton = NULL;
    QRadioButton* languageEnglishRadioButton = NULL;

    // 开机自启动
    QHBoxLayout* autoRunHBoxLayout = NULL;
    QLabel* autoRunTipLabel = NULL;
    QCheckBox* autoRunCheckBox = NULL;

    // 显示绑定焦点信息
    QVBoxLayout* lockFocusOnVBoxLayout = NULL;
    QGroupBox* lockFocusOnProgramNameGroupBox = NULL;
    // 句柄号与进程名水平布局
    QHBoxLayout* lockFocusOnInfoHBboxLayout = NULL;
    //显示进程号
    QHBoxLayout* lockFocusOnProcessIdHboxLayout = NULL;
    QLabel* lockFocusOnProcessIdTipLabel = NULL;
    QLabel* lockFocusOnProcessIdInfoLabel = NULL;
    // 显示句柄号
    QHBoxLayout* lockFocusOnHandleHboxLayout = NULL;
    QLabel* lockFocusOnHandleTipLabel = NULL;
    QLabel* lockFocusOnHandleInfoLabel = NULL;
    // 显示进程名
    QHBoxLayout* lockFocusOnProgramNameHboxLayout = NULL;
    QLabel* lockFocusOnProgramNameTipLabel = NULL;
    QLabel* lockFocusOnProgramNameInfoLabel = NULL;
    // 显示进程进程
    QHBoxLayout* lockFocusOnProgramPathHboxLayout = NULL;
    QLabel* lockFocusOnProgramPathTipLabel = NULL;
    QLineEdit* lockFocusOnProgramPathInfoLineEdit = NULL;


    // 显示当前焦点信息
    QVBoxLayout* currentFocusOnVBoxLayout = NULL;
    QGroupBox* currentFocusOnProgramNameGroupBox = NULL;
    // 句柄号与进程名水平布局
    QHBoxLayout* currentFocusOnInfoHBboxLayout = NULL;
    //显示进程号
    QHBoxLayout* currentFocusOnProcessIdHboxLayout = NULL;
    QLabel* currentFocusOnProcessIdTipLabel = NULL;
    QLabel* currentFocusOnProcessIdInfoLabel = NULL;
    // 显示句柄号
    QHBoxLayout* currentFocusOnHandleHboxLayout = NULL;
    QLabel* currentFocusOnHandleTipLabel = NULL;
    QLabel* currentFocusOnHandleInfoLabel = NULL;
    // 显示进程名
    QHBoxLayout* currentFocusOnProgramNameHboxLayout = NULL;
    QLabel* currentFocusOnProgramNameTipLabel = NULL;
    QLabel* currentFocusOnProgramNameInfoLabel = NULL;
    // 显示进程进程
    QHBoxLayout* currentFocusOnProgramPathHboxLayout = NULL;
    QLabel* currentFocusOnProgramPathTipLabel = NULL;
    QLineEdit* currentFocusOnProgramPathInfoLineEdit = NULL;

    // 程序开关
    QHBoxLayout* appSwitchHBoxLayout = NULL;
    QButtonGroup* appSwitchButtonGroup = NULL;
    QRadioButton* appOnRadioButton = NULL;
    QRadioButton* appOffRadioButton = NULL;
};

#endif