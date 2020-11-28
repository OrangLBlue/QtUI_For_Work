#include "CMvFindRoundParamWidget.h"
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMvFindRoundParamWidget* w = CMvFindRoundParamWidget::Instance() ;
    w->show();
    return a.exec();
}
