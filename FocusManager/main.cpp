#include <QtWidgets/QApplication>
#include "FocusManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FocusManager w;
    w.trayIcon->show();

    //// 未知原因，自启动无法加载托盘, 尝试强制修复
    //for (int i = 0; i < 10; i++)
    //{
    //    if (!w.trayIcon->isSystemTrayAvailable())
    //    {
    //        w.trayIcon->setIcon(QIcon("./icon/program.ico"));
    //        w.trayIcon->show();
    //    }
    //    else
    //    {
    //        break;
    //    }

    //    if (i == 9)
    //    {
    //        QMessageBox::information(&w, "error", "false to load the tray icon, the program will be close automatically!");
    //        qApp->exit();
    //    }
    //}

    return a.exec();
}
