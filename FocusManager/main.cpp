#include <QtWidgets/QApplication>
#include "FocusManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FocusManager w;
    w.show();
    return a.exec();
}
