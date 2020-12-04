#include <QFile>
#include <QApplication>


#include "CMvTestWidget.h"

#ifndef NDEBUG
//#include "vld.h"
#endif

int main(int argc, char *argv[])
{
	//int widgetType = 6;
	QWidget *pTestWidget = nullptr;
    QApplication a(argc, argv);

#if 0
	//加载控件显示样式
	QFile file(":/css/BlackCss2/Black2.css");
	if (file.open(QFile::ReadOnly))
	{
		QString qss = QLatin1String(file.readAll());
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		file.close();
	}//if (file.open(QFile::ReadOnly))
#endif
	pTestWidget = CMvTestWidget::Instance();

	pTestWidget->show();
    return a.exec();
}
