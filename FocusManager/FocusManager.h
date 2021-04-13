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
    void setTrayIcon();
    void initGUI();                     // 初始化界面布局
    void initConfiguration();
    void recordConfiguration();
    void connectSignalAndSlot();
    void switchFocus();
    void lockFocus();
    bool eventFilter(QObject* o, QEvent* e);
    void flushUI();
    void setAutomaticSoftwareStartup(bool autoRun);

private:
    QxtGlobalShortcut* switchFocusShortcut = new QxtGlobalShortcut(this);
    QxtGlobalShortcut* lockFocusShortcut = new QxtGlobalShortcut(this);
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
    QVBoxLayout* mainBox = new QVBoxLayout();
    QHBoxLayout* topHbox = new QHBoxLayout();

    // 快捷键设置
    QGroupBox* focusGroupBox = new QGroupBox();
    QVBoxLayout* focusVBox = new QVBoxLayout();
    // 定义绑定焦点快捷键
    QHBoxLayout* lockFocusHBoxLayout = new QHBoxLayout();
    QLabel* lockFocusLabel = new QLabel();
    QComboBox* lockFocusComboBox = new QComboBox();

    // 定义焦点切换快捷键
    QHBoxLayout* switchFocusHBoxLayout = new QHBoxLayout();
    QLabel* switchFocusLabel = new QLabel();
    QComboBox* switchFocusComboBox = new QComboBox();


    //定义设置功能按钮
    QGroupBox* appSetGroupBox = new QGroupBox();
    QVBoxLayout* appSetVBox = new QVBoxLayout();
    // 语言设置
    QHBoxLayout* languageHBoxLayout = new QHBoxLayout();
    QLabel* languageTipLabel = new QLabel();
    QButtonGroup* languageButtonGroup = new QButtonGroup();
    QRadioButton* languageChineseRadioButton = new QRadioButton("中文");
    QRadioButton* languageEnglishRadioButton = new QRadioButton("English");

    // 开机自启动
    QHBoxLayout* autoRunHBoxLayout = new QHBoxLayout();
    QLabel* autoRunTipLabel = new QLabel();
    QCheckBox* autoRunCheckBox = new QCheckBox();

    // 显示绑定焦点信息
    QVBoxLayout* lockFocusOnVBoxLayout = new QVBoxLayout();
    QGroupBox* lockFocusOnProgramNameGroupBox = new QGroupBox();
    // 句柄号与进程名水平布局
    QHBoxLayout* lockFocusOnInfoHBboxLayout = new QHBoxLayout();
    //显示进程号
    QHBoxLayout* lockFocusOnProcessIdHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnProcessIdTipLabel = new QLabel();
    QLabel* lockFocusOnProcessIdInfoLabel = new QLabel();
    // 显示句柄号
    QHBoxLayout* lockFocusOnHandleHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnHandleTipLabel = new QLabel();
    QLabel* lockFocusOnHandleInfoLabel = new QLabel();
    // 显示进程名
    QHBoxLayout* lockFocusOnProgramNameHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnProgramNameTipLabel = new QLabel();
    QLabel* lockFocusOnProgramNameInfoLabel = new QLabel();
    // 显示进程进程
    QHBoxLayout* lockFocusOnProgramPathHboxLayout = new QHBoxLayout();
    QLabel* lockFocusOnProgramPathTipLabel = new QLabel();
    QLineEdit* lockFocusOnProgramPathInfoLineEdit = new QLineEdit();


    // 显示当前焦点信息
    QVBoxLayout* currentFocusOnVBoxLayout = new QVBoxLayout();
    QGroupBox* currentFocusOnProgramNameGroupBox = new QGroupBox();
    // 句柄号与进程名水平布局
    QHBoxLayout* currentFocusOnInfoHBboxLayout = new QHBoxLayout();
    //显示进程号
    QHBoxLayout* currentFocusOnProcessIdHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnProcessIdTipLabel = new QLabel();
    QLabel* currentFocusOnProcessIdInfoLabel = new QLabel();
    // 显示句柄号
    QHBoxLayout* currentFocusOnHandleHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnHandleTipLabel = new QLabel();
    QLabel* currentFocusOnHandleInfoLabel = new QLabel();
    // 显示进程名
    QHBoxLayout* currentFocusOnProgramNameHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnProgramNameTipLabel = new QLabel();
    QLabel* currentFocusOnProgramNameInfoLabel = new QLabel();
    // 显示进程进程
    QHBoxLayout* currentFocusOnProgramPathHboxLayout = new QHBoxLayout();
    QLabel* currentFocusOnProgramPathTipLabel = new QLabel();
    QLineEdit* currentFocusOnProgramPathInfoLineEdit = new QLineEdit();

    // 程序开关
    QHBoxLayout* appSwitchHBoxLayout = new QHBoxLayout();
    QButtonGroup* appSwitchButtonGroup = new QButtonGroup();
    QRadioButton* appOnRadioButton = new QRadioButton();
    QRadioButton* appOffRadioButton = new QRadioButton();
};

#endif