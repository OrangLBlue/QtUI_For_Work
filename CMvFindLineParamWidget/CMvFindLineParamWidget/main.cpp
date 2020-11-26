#include "CMvFindLineParamWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMvFindLineParamWidget w;
    w.show();
    return a.exec();
}
