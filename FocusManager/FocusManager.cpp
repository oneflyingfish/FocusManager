#include "FocusManager.h"

FocusManager::FocusManager(QWidget *parent): QWidget(parent)
{
    this->initObjects();
    this->setDefaultValue();
    // 安装事件管理器
    this->installEventFilter(this);             
    this->configFilePath = QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));

    // 初始化界面布局
    this->initGUI();
    this->connectSignalAndSlot();
    
    // 恢复配置文件
    this->initConfiguration();
    this->flushUI();
}

void FocusManager::initObjects()
{
    this->switchFocusShortcut = new QxtGlobalShortcut(this);
    this->lockFocusShortcut = new QxtGlobalShortcut(this);

    // 定义主体布局
    this->mainBox = new QVBoxLayout();
    this->topHbox = new QHBoxLayout();

    // 快捷键设置
    this->focusGroupBox = new QGroupBox();
    this->focusVBox = new QVBoxLayout();
    // 定义绑定焦点快捷键
    this->lockFocusHBoxLayout = new QHBoxLayout();
    this->lockFocusLabel = new QLabel();
    this->lockFocusComboBox = new QComboBox();

    // 定义焦点切换快捷键
    this->switchFocusHBoxLayout = new QHBoxLayout();
    this->switchFocusLabel = new QLabel();
    this->switchFocusComboBox = new QComboBox();


    //定义设置功能按钮
    this->appSetGroupBox = new QGroupBox();
    this->appSetVBox = new QVBoxLayout();
    // 语言设置
    this->languageHBoxLayout = new QHBoxLayout();
    this->languageTipLabel = new QLabel();
    this->languageButtonGroup = new QButtonGroup();
    this->languageChineseRadioButton = new QRadioButton("中文");
    this->languageEnglishRadioButton = new QRadioButton("English");

    // 开机自启动
    this->autoRunHBoxLayout = new QHBoxLayout();
    this->autoRunTipLabel = new QLabel();
    this->autoRunCheckBox = new QCheckBox();

    // 显示绑定焦点信息
    this->lockFocusOnVBoxLayout = new QVBoxLayout();
    this->lockFocusOnProgramNameGroupBox = new QGroupBox();
    // 句柄号与进程名水平布局
    this->lockFocusOnInfoHBboxLayout = new QHBoxLayout();
    //显示进程号
    this->lockFocusOnProcessIdHboxLayout = new QHBoxLayout();
    this->lockFocusOnProcessIdTipLabel = new QLabel();
    this->lockFocusOnProcessIdInfoLabel = new QLabel();
    // 显示句柄号
    this->lockFocusOnHandleHboxLayout = new QHBoxLayout();
    this->lockFocusOnHandleTipLabel = new QLabel();
    this->lockFocusOnHandleInfoLabel = new QLabel();
    // 显示进程名
    this->lockFocusOnProgramNameHboxLayout = new QHBoxLayout();
    this->lockFocusOnProgramNameTipLabel = new QLabel();
    this->lockFocusOnProgramNameInfoLabel = new QLabel();
    // 显示进程进程
    this->lockFocusOnProgramPathHboxLayout = new QHBoxLayout();
    this->lockFocusOnProgramPathTipLabel = new QLabel();
    this->lockFocusOnProgramPathInfoLineEdit = new QLineEdit();


    // 显示当前焦点信息
    this->currentFocusOnVBoxLayout = new QVBoxLayout();
    this->currentFocusOnProgramNameGroupBox = new QGroupBox();
    // 句柄号与进程名水平布局
    this->currentFocusOnInfoHBboxLayout = new QHBoxLayout();
    //显示进程号
    this->currentFocusOnProcessIdHboxLayout = new QHBoxLayout();
    this->currentFocusOnProcessIdTipLabel = new QLabel();
    this->currentFocusOnProcessIdInfoLabel = new QLabel();
    // 显示句柄号
    this->currentFocusOnHandleHboxLayout = new QHBoxLayout();
    this->currentFocusOnHandleTipLabel = new QLabel();
    this->currentFocusOnHandleInfoLabel = new QLabel();
    // 显示进程名
    this->currentFocusOnProgramNameHboxLayout = new QHBoxLayout();
    this->currentFocusOnProgramNameTipLabel = new QLabel();
    this->currentFocusOnProgramNameInfoLabel = new QLabel();
    // 显示进程进程
    this->currentFocusOnProgramPathHboxLayout = new QHBoxLayout();
    this->currentFocusOnProgramPathTipLabel = new QLabel();
    this->currentFocusOnProgramPathInfoLineEdit = new QLineEdit();

    // 程序开关
    this->appSwitchHBoxLayout = new QHBoxLayout();
    this->appSwitchButtonGroup = new QButtonGroup();
    this->appOnRadioButton = new QRadioButton();
    this->appOffRadioButton = new QRadioButton();
}

void FocusManager::setDefaultValue()
{
    this->resize(420, 320);
    this->languageChineseRadioButton->setChecked(true);
    this->autoRunCheckBox->setChecked(false);
}

void FocusManager::flushUI()
{
    this->setWindowTitle(tr("焦点管理工具"));
    focusGroupBox->setTitle(tr("快捷键设置"));
    lockFocusLabel->setText(tr("绑定焦点: "));
    switchFocusLabel->setText(tr("切换焦点: "));
    appSetGroupBox->setTitle(tr("软件设置"));
    languageTipLabel->setText(tr("语言: "));
    autoRunTipLabel->setText(tr("开机自启动: "));
    lockFocusOnProgramNameGroupBox->setTitle(tr("绑定焦点信息"));
    lockFocusOnProcessIdTipLabel->setText(tr("进程号: "));
    lockFocusOnHandleTipLabel->setText(tr("句柄号: "));
    lockFocusOnProgramNameTipLabel->setText(tr("应用标题: "));
    lockFocusOnProgramPathTipLabel->setText(tr("程序路径: "));
    currentFocusOnProgramNameGroupBox->setTitle(tr("当前焦点信息"));
    currentFocusOnProcessIdTipLabel->setText(tr("进程号: "));
    currentFocusOnHandleTipLabel->setText(tr("句柄号: "));
    currentFocusOnProgramNameTipLabel->setText(tr("应用标题: "));
    currentFocusOnProgramPathTipLabel->setText(tr("程序路径: "));
    appOnRadioButton->setText(tr("启用"));
    appOffRadioButton->setText(tr("禁用"));

    switchAction->setText(this->appOnRadioButton->isChecked()?tr("禁用"):tr("启用"));
    minimizeAction->setText(tr("最小化"));
    restoreAction->setText(tr("还原"));
    quitAction->setText(tr("退出"));
    this->trayIcon->setToolTip(tr("焦点管理工具"));
    this->resize(535, 355);
}

bool FocusManager::eventFilter(QObject* o, QEvent* e)
{
    if (o == this && e->type() == QEvent::WindowStateChange)
    {
        //窗口状态被改变的事件.
        if (this->windowState() == Qt::WindowMinimized)
        {
            this->hide();
            this->trayIcon->show();
            e->ignore();
            return true;
        }
    }
    else if (o == this && e->type() == QEvent::Close)
    {
        if (QMessageBox::question(this, tr("退出程序"), QString(tr("确认关闭程序，而非最小化到托盘？")), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            e->accept();  //介绍//程序退出
        }
        else
        {
            this->hide();
            this->trayIcon->show();
            e->ignore();
        }
        return true;
    }
    return QObject::eventFilter(o, e);
}

void FocusManager::setTrayIcon()
{
    //创建托盘图标
    this->trayIcon->setIcon(QIcon(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("icon/program.ico")));
    this->trayIcon->setToolTip(tr("焦点管理工具"));
    this->trayIcon->show();

    //创建监听行为
    this->switchAction = new QAction(tr("启用"), this);
    this->minimizeAction = new QAction(tr("最小化"), this);
    this->restoreAction = new QAction(tr("还原"), this); 
    this->quitAction = new QAction(tr("退出"), this); 

    //创建右键弹出菜单
    this->trayIconMenu = new QMenu(this);
    this->trayIconMenu->addAction(switchAction);
    this->trayIconMenu->addAction(minimizeAction);
    this->trayIconMenu->addAction(restoreAction);
    this->trayIconMenu->addSeparator();
    this->trayIconMenu->addAction(quitAction);
    this->trayIcon->setContextMenu(trayIconMenu);
}

void FocusManager::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        this->showNormal();
        this->activateWindow();
        break;
    default:
        break;
    }
}

void FocusManager::connectSignalAndSlot()
{
    connect(this->lockFocusComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(lockFocusComboBoxActionChanged(QString)));
    connect(this->switchFocusComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(switchFocusComboBoxActionChanged(QString)));
    connect(this->switchFocusShortcut, &QxtGlobalShortcut::activated, [=]() {this->switchFocus(); });
    connect(this->lockFocusShortcut, &QxtGlobalShortcut::activated, [=]() {this->lockFocus(); });
    connect(this->appOnRadioButton, SIGNAL(toggled(bool)), this, SLOT(flushSwitchAction(bool)));
    connect(this->languageChineseRadioButton, SIGNAL(toggled(bool)), this, SLOT(setLanguageChinese(bool)));
    connect(this->languageEnglishRadioButton, SIGNAL(toggled(bool)), this, SLOT(setLanguageEnglish(bool)));
    // 添加托盘单/双击鼠标相应
    connect(this->trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    connect(this->switchAction, SIGNAL(triggered()), this, SLOT(setAppStatus()));
    connect(this->minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect(this->restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(this->quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // 开机自启动
    connect(this->autoRunCheckBox, SIGNAL(stateChanged(int)), this, SLOT(autoRunConfig(int)));
}

void FocusManager::autoRunConfig(int state)
{
    if (state == Qt::CheckState::Unchecked)
    {
        this->setAutomaticSoftwareStartup(false);
    }
    else
    {
        this->setAutomaticSoftwareStartup(true);
    }
}

// 设置自启动
void FocusManager::setAutomaticSoftwareStartup(bool autoRun)
{
    //QSettings提供与操作系统无关的应用程序设置，windos下通常存储在注册表中
    //QSettings::NativeFormat:使用最适合平台的存储格式存储设置。
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString strAppPath = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    QString strAppName = QFileInfo(strAppPath).baseName();


    if (autoRun)
    {
        reg.setValue(strAppName, strAppPath);//写入注册表，开机自启动
    }
    else
    {
        reg.remove(strAppName);//从注册表移除，关闭开机自启
    }
}

void FocusManager::setLanguageEnglish(bool b)
{
    if (b)
    {
        translator.load(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("Translation_Files/focusmanager_en.qm"));
        qApp->installTranslator(&translator);
        this->flushUI();
    }
}

void FocusManager::setLanguageChinese(bool b)
{
    if (b)
    {
        qApp->removeTranslator(&translator);
        this->flushUI();
    }
}

void FocusManager::setAppStatus()
{
    qDebug() << this->switchAction->text() << endl;
    if (this->switchAction->text() == tr("启用") || this->switchAction->text() == tr("Enable"))
    {
        this->appOnRadioButton->setChecked(true);
    }
    else
    {
        this->appOffRadioButton->setChecked(true);
    }
}

void FocusManager::flushSwitchAction(bool status)
{
    this->switchAction->setText(status ? tr("禁用") : tr("启用"));
    if (status)
    {
        this->trayIcon->setIcon(QIcon(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("icon/program.ico")));
    }
    else
    {
        this->trayIcon->setIcon(QIcon(QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("icon/program_down.ico")));
    }
}

void FocusManager::switchFocus()
{
    // 确保关闭时无效
    if (this->appOffRadioButton->isChecked())
    {
        return;
    }

    qDebug() << "--switch Focus--";
    HandleInfo handle= WindowsHandle::getCurrentSystemFocus();
    if (handle.handleId == lockHandle.handleId)
    {
        if (currentHandle.handleId != 0)
        {
            // 切换回原来的句柄
            WindowsHandle::setHandleFocus(currentHandle);
            WindowsHandle::setHandleMouseLocation(currentHandle);
        }
    }
    else
    {
        // 切换到锁定应用
        if (lockHandle.handleId!=0)
        {
            this->currentHandle = handle;
            WindowsHandle::setHandleFocus(lockHandle);
            WindowsHandle::setHandleMouseLocation(lockHandle);
            this->currentFocusOnProcessIdInfoLabel->setText(QString::number(currentHandle.processId));
            this->currentFocusOnHandleInfoLabel->setText(QString::number(currentHandle.handleId));
            this->currentFocusOnProgramNameInfoLabel->setText(currentHandle.processTitle);
            this->currentFocusOnProgramPathInfoLineEdit->setText(currentHandle.processPath);
        }
        else
        {
            QMessageBox::information(this, tr("提示"), tr("请先绑定要切换的焦点应用"));
        }
    }

}

void FocusManager::lockFocus()
{
    // 确保关闭时无效
    if (this->appOffRadioButton->isChecked())
    {
        return;
    }

    qDebug() << "--lock Focus--";
    lockHandle = WindowsHandle::getCurrentSystemFocus();
    this->lockFocusOnProcessIdInfoLabel->setText(QString::number(lockHandle.processId));
    this->lockFocusOnHandleInfoLabel->setText(QString::number(lockHandle.handleId));
    this->lockFocusOnProgramNameInfoLabel->setText(lockHandle.processTitle);
    this->lockFocusOnProgramPathInfoLineEdit->setText(lockHandle.processPath);
}

void FocusManager::switchFocusComboBoxActionChanged(QString text)
{
    if (text.isEmpty() || text == "")
    {
        this->switchFocusShortcut->setShortcut(NULL);
        return;
    }

    if (!this->switchFocusShortcut->setShortcut(QKeySequence(text)))
    {
        this->switchFocusComboBox->setCurrentIndex(0);
        QMessageBox::information(this, "错误", QString("\"") + text + "\"被占用，请选择其它快捷键");
        this->switchFocusShortcut->setDisabled();
    }
    this->switchFocusShortcut->setEnabled();
}

void FocusManager::lockFocusComboBoxActionChanged(QString text)
{
    if (text.isEmpty() || text == "")
    {
        this->lockFocusShortcut->setShortcut(NULL);
        return;
    }

    if (!this->lockFocusShortcut->setShortcut(QKeySequence(text)))
    {
        this->lockFocusComboBox->setCurrentIndex(0);
        QMessageBox::information(this, "错误", QString("\"") + text + "\"被其他程序占用，请选择其他快捷键");
        this->lockFocusShortcut->setDisabled();
    }
    this->lockFocusShortcut->setEnabled();
}

void FocusManager::initGUI()
{
    this->activateWindow();     // 置顶显示
    this->hide();               // 默认隐藏窗口

    this->currentFocusOnProgramPathInfoLineEdit->setReadOnly(true);
    this->lockFocusOnProgramPathInfoLineEdit->setReadOnly(true);

    // 向快捷键组合框添加选项 数字
    for (int i = 0; i < 10; i++)
    {
        this->lockFocusComboBox->addItem(QString(""));
        this->lockFocusComboBox->addItem(QString("Alt+") + QString::number(i));
        this->lockFocusComboBox->addItem(QString("Ctrl+") + QString::number(i));
        this->lockFocusComboBox->addItem(QString("Ctrl+Shift+") + QString::number(i));
        this->lockFocusComboBox->addItem(QString("Ctrl+Alt+") + QString::number(i));

        this->switchFocusComboBox->addItem(QString(""));
        this->switchFocusComboBox->addItem(QString("Alt+") + QString::number(i));
        this->switchFocusComboBox->addItem(QString("Ctrl+") + QString::number(i));
        this->switchFocusComboBox->addItem(QString("Ctrl+Shift+") + QString::number(i));
        this->switchFocusComboBox->addItem(QString("Ctrl+Alt+") + QString::number(i));
    }

    // 向快捷键组合框添加选项 字母
    for (int i = 'A'; i <= 'Z'; i++)
    {
        this->lockFocusComboBox->addItem(QString(""));
        this->lockFocusComboBox->addItem(QString("Alt+") + QChar(i));
        this->lockFocusComboBox->addItem(QString("Ctrl+") + QChar(i));
        this->lockFocusComboBox->addItem(QString("Ctrl+Shift+") + QChar(i));
        this->lockFocusComboBox->addItem(QString("Ctrl+Alt+") + QChar(i));

        this->switchFocusComboBox->addItem(QString(""));
        this->switchFocusComboBox->addItem(QString("Alt+") + QChar(i));
        this->switchFocusComboBox->addItem(QString("Ctrl+") + QChar(i));
        this->switchFocusComboBox->addItem(QString("Ctrl+Shift+") + QChar(i));
        this->switchFocusComboBox->addItem(QString("Ctrl+Alt+") + QChar(i));
    }

    // 焦点绑定快捷键模块
    this->lockFocusHBoxLayout->setSpacing(5);
    this->lockFocusHBoxLayout->addWidget(this->lockFocusLabel,0);
    this->lockFocusHBoxLayout->addWidget(this->lockFocusComboBox,1);

    // 焦点切换快捷键模块
    this->switchFocusHBoxLayout->setSpacing(5);
    this->switchFocusHBoxLayout->addWidget(this->switchFocusLabel,0);
    this->switchFocusHBoxLayout->addWidget(this->switchFocusComboBox,1);

    // 语言
    this->languageButtonGroup->addButton(this->languageChineseRadioButton);
    this->languageButtonGroup->addButton(this->languageEnglishRadioButton);
    this->languageHBoxLayout->addWidget(this->languageTipLabel);
    this->languageHBoxLayout->addWidget(this->languageChineseRadioButton);
    this->languageHBoxLayout->addWidget(this->languageEnglishRadioButton);

    // 开机自启动
    this->autoRunHBoxLayout->addWidget(this->autoRunTipLabel);
    this->autoRunHBoxLayout->addWidget(this->autoRunCheckBox);

    // 快捷键模块
    this->focusVBox->addLayout(this->lockFocusHBoxLayout);
    this->focusVBox->addLayout(this->switchFocusHBoxLayout);
    this->focusGroupBox->setLayout(this->focusVBox);

    // 应用设置模块
    this->appSetVBox->addLayout(this->languageHBoxLayout);
    this->appSetVBox->addLayout(this->autoRunHBoxLayout);
    this->appSetGroupBox->setLayout(this->appSetVBox);

    // 顶部水平布局
    this->topHbox->addWidget(this->focusGroupBox,2);
    this->topHbox->addStretch();
    this->topHbox->addWidget(this->appSetGroupBox,1);

    // 绑定焦点信息模块
    this->lockFocusOnProcessIdHboxLayout->addWidget(this->lockFocusOnProcessIdTipLabel);
    this->lockFocusOnProcessIdHboxLayout->addWidget(this->lockFocusOnProcessIdInfoLabel);
    this->lockFocusOnHandleHboxLayout->addWidget(this->lockFocusOnHandleTipLabel);
    this->lockFocusOnHandleHboxLayout->addWidget(this->lockFocusOnHandleInfoLabel);
    this->lockFocusOnProgramNameHboxLayout->addWidget(this->lockFocusOnProgramNameTipLabel);
    this->lockFocusOnProgramNameHboxLayout->addWidget(this->lockFocusOnProgramNameInfoLabel);
    this->lockFocusOnInfoHBboxLayout->addLayout(this->lockFocusOnProcessIdHboxLayout);
    this->lockFocusOnInfoHBboxLayout->addLayout(this->lockFocusOnHandleHboxLayout);
    this->lockFocusOnInfoHBboxLayout->addLayout(this->lockFocusOnProgramNameHboxLayout);
    this->lockFocusOnProgramPathHboxLayout->addWidget(this->lockFocusOnProgramPathTipLabel);
    this->lockFocusOnProgramPathHboxLayout->addWidget(this->lockFocusOnProgramPathInfoLineEdit);
    this->lockFocusOnVBoxLayout->addLayout(this->lockFocusOnInfoHBboxLayout);
    this->lockFocusOnVBoxLayout->addLayout(this->lockFocusOnProgramPathHboxLayout);
    this->lockFocusOnProgramNameGroupBox->setLayout(this->lockFocusOnVBoxLayout);

    // 当前焦点信息模块
    this->currentFocusOnProcessIdHboxLayout->addWidget(this->currentFocusOnProcessIdTipLabel);
    this->currentFocusOnProcessIdHboxLayout->addWidget(this->currentFocusOnProcessIdInfoLabel);
    this->currentFocusOnHandleHboxLayout->addWidget(this->currentFocusOnHandleTipLabel);
    this->currentFocusOnHandleHboxLayout->addWidget(this->currentFocusOnHandleInfoLabel);
    this->currentFocusOnProgramNameHboxLayout->addWidget(this->currentFocusOnProgramNameTipLabel);
    this->currentFocusOnProgramNameHboxLayout->addWidget(this->currentFocusOnProgramNameInfoLabel);
    this->currentFocusOnInfoHBboxLayout->addLayout(this->currentFocusOnProcessIdHboxLayout);
    this->currentFocusOnInfoHBboxLayout->addLayout(this->currentFocusOnHandleHboxLayout);
    this->currentFocusOnInfoHBboxLayout->addLayout(this->currentFocusOnProgramNameHboxLayout);
    this->currentFocusOnProgramPathHboxLayout->addWidget(this->currentFocusOnProgramPathTipLabel);
    this->currentFocusOnProgramPathHboxLayout->addWidget(this->currentFocusOnProgramPathInfoLineEdit);
    this->currentFocusOnVBoxLayout->addLayout(this->currentFocusOnInfoHBboxLayout);
    this->currentFocusOnVBoxLayout->addLayout(this->currentFocusOnProgramPathHboxLayout);
    this->currentFocusOnProgramNameGroupBox->setLayout(this->currentFocusOnVBoxLayout);

    // 程序开关
    this->appSwitchButtonGroup->addButton(this->appOnRadioButton);
    this->appSwitchButtonGroup->addButton(this->appOffRadioButton);
    this->appSwitchHBoxLayout->addStretch();
    this->appSwitchHBoxLayout->addWidget(this->appOnRadioButton);
    this->appSwitchHBoxLayout->addWidget(this->appOffRadioButton);
    this->appOnRadioButton->setChecked(true);

    // 整体垂直布局
    this->mainBox->addLayout(this->topHbox);
    this->mainBox->addWidget(this->lockFocusOnProgramNameGroupBox);
    this->mainBox->addWidget(this->currentFocusOnProgramNameGroupBox);
    this->mainBox->addLayout(this->appSwitchHBoxLayout);

    // 设置间距
    this->mainBox->setSpacing(15);
    this->setLayout(this->mainBox);
    this->setTrayIcon();        // 设置托盘
}

void FocusManager::initConfiguration()
{
    if (!this->configFilePath.exists("FocusManager"))
    {
        this->configFilePath.mkdir("FocusManager");
    }

    QFile file(this->configFilePath.absoluteFilePath("FocusManager/config.json"));              // 不存在会自动创建
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this, tr("错误"), "配置文件无法打开");
        return;
    }

    // 读取配置文件
    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(file.readAll(), &jsonError));
    file.close();
    if (jsonError.error != QJsonParseError::NoError || jsonDoc.isEmpty())
    {
        // json格式错误或内容为空则重新生成
        this->recordConfiguration();
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    this->lockFocusComboBox->setCurrentText(jsonObject["lock_focus_shortcut"].toString());
    this->switchFocusComboBox->setCurrentText(jsonObject["switch_focus_shortcut"].toString());
    // 开机自启动
    if (jsonObject["autoRun"].toBool())
    {
        this->autoRunCheckBox->setChecked(true);
    }
    else
    {
        this->autoRunCheckBox->setChecked(false);
    }
    // 切换中英文
    if (jsonObject["language"].toString().toLower() == "english")
    {
        this->languageEnglishRadioButton->setChecked(true);
    }
    else
    {
        this->languageChineseRadioButton->setChecked(true);
    }
    // 应用开关
    if (jsonObject["app_switch"].toBool())
    {
        this->appOnRadioButton->setChecked(true);
        this->switchAction->setText(tr("关闭"));
    }
    else
    {
        this->appOffRadioButton->setChecked(true);
        this->switchAction->setText("启用");
    }
}

void FocusManager::recordConfiguration()
{
    QFile file(this->configFilePath.absoluteFilePath("FocusManager/config.json"));
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("错误"), "配置文件无法打开");
        return;
    }

    // json格式错误，则生成
    QJsonObject jsonObject;
    jsonObject.insert(tr("lock_focus_shortcut"), this->lockFocusComboBox->currentText());
    jsonObject.insert(tr("switch_focus_shortcut"), this->switchFocusComboBox->currentText());
    jsonObject.insert(tr("app_switch"), this->appOnRadioButton->isChecked());
    if (this->languageChineseRadioButton->isChecked())
    {
        jsonObject.insert(tr("language"), tr("chinese"));
    }
    else if (this->languageEnglishRadioButton->isChecked())
    {
        jsonObject.insert(tr("language"), tr("english"));
    }
    else
    {
        jsonObject.insert(tr("language"), tr(""));
    }
    jsonObject.insert(tr("autoRun"), this->autoRunCheckBox->isChecked());

    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObject);

    file.write(jsonDoc.toJson());
    file.close();
    this->switchAction->setText(this->appOnRadioButton->isChecked()? tr("关闭"): tr("开启"));
}


FocusManager::~FocusManager()
{
    this->recordConfiguration();
    
    // 释放快捷键内存
    switchFocusShortcut->deleteLater();
    lockFocusShortcut->deleteLater();

    /********************************
    此处主要释放GUI控件所分配的内存
    *********************************/

    //释放trayIcon
    trayIcon->deleteLater();
    minimizeAction->deleteLater();
    restoreAction->deleteLater();
    quitAction->deleteLater();
    trayIconMenu->deleteLater();

    // 定义主体布局
    mainBox->deleteLater();
    topHbox->deleteLater();

    // 快捷键设置
    focusGroupBox->deleteLater();
    focusVBox->deleteLater();

    // 定义绑定焦点快捷键
    lockFocusHBoxLayout->deleteLater();
    lockFocusLabel->deleteLater();
    lockFocusComboBox->deleteLater();

    // 定义焦点切换快捷键
    switchFocusHBoxLayout->deleteLater();
    switchFocusLabel->deleteLater();
    switchFocusComboBox->deleteLater();

    //定义设置功能按钮
    appSetGroupBox->deleteLater();
    appSetVBox->deleteLater();
    // 语言设置
    languageHBoxLayout->deleteLater();
    languageTipLabel->deleteLater();
    languageButtonGroup->deleteLater();
    languageChineseRadioButton->deleteLater();
    languageEnglishRadioButton->deleteLater();

    // 开机自启动
    autoRunHBoxLayout->deleteLater();
    autoRunTipLabel->deleteLater();
    autoRunCheckBox->deleteLater();


    // 显示绑定焦点信息
    lockFocusOnVBoxLayout->deleteLater();
    lockFocusOnProgramNameGroupBox->deleteLater();
    // 句柄号与进程名水平布局
    lockFocusOnInfoHBboxLayout->deleteLater();
    //显示进程号
    lockFocusOnProcessIdHboxLayout->deleteLater();
    lockFocusOnProcessIdTipLabel->deleteLater();
    lockFocusOnProcessIdInfoLabel->deleteLater();
    // 显示句柄号
    lockFocusOnHandleHboxLayout->deleteLater();
    lockFocusOnHandleTipLabel->deleteLater();
    lockFocusOnHandleInfoLabel->deleteLater();
    // 显示进程名
    lockFocusOnProgramNameHboxLayout->deleteLater();
    lockFocusOnProgramNameTipLabel->deleteLater();
    lockFocusOnProgramNameInfoLabel->deleteLater();
    // 显示进程进程
    lockFocusOnProgramPathHboxLayout->deleteLater();
    lockFocusOnProgramPathTipLabel->deleteLater();
    lockFocusOnProgramPathInfoLineEdit->deleteLater();

    // 显示当前焦点信息
    currentFocusOnVBoxLayout->deleteLater();
    currentFocusOnProgramNameGroupBox->deleteLater();
    // 句柄号与进程名水平布局
    currentFocusOnInfoHBboxLayout->deleteLater();
    //显示进程号
    currentFocusOnProcessIdHboxLayout->deleteLater();
    currentFocusOnProcessIdTipLabel->deleteLater();
    currentFocusOnProcessIdInfoLabel->deleteLater();
    // 显示句柄号
    currentFocusOnHandleHboxLayout->deleteLater();
    currentFocusOnHandleTipLabel->deleteLater();
    currentFocusOnHandleInfoLabel->deleteLater();
    // 显示进程名
    currentFocusOnProgramNameHboxLayout->deleteLater();
    currentFocusOnProgramNameTipLabel->deleteLater();
    currentFocusOnProgramNameInfoLabel->deleteLater();
    // 显示进程进程
    currentFocusOnProgramPathHboxLayout->deleteLater();
    currentFocusOnProgramPathTipLabel->deleteLater();
    currentFocusOnProgramPathInfoLineEdit->deleteLater();
    // 程序开关
    appSwitchButtonGroup->deleteLater();
    appSwitchHBoxLayout->deleteLater();
    appOnRadioButton->deleteLater();
    appOffRadioButton->deleteLater();
}
