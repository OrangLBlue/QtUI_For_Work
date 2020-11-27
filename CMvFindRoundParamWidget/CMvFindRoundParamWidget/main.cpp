#include "CMvFindRoundParamWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMvFindRoundParamWidget w;
    w.show();
    return a.exec();
}
