#include <QFile>
#include <QApplication>

#include "CMvFindRoundParamWidget.h"
#include "CMvFindLineParamWidget.h"
#include "CMvColorImagesCut.h"
#include "CMvBlackAndWhiteConversionColor.h"
#include "CMvColorConversionBlackAndWhite.h"
#include "CMvFourArithmeticOperation.h"

#ifndef NDEBUG
#include "vld.h"
#endif


int main(int argc, char *argv[])
{
	int widgetType = 5;
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

	switch (widgetType)
	{
	case 0 ://find line
	{
		pTestWidget = CMvFindLineParamWidget::Instance();
		////pTestWidget->setWindowTitle("查找直线");
	}break;
	case 1://find round
	{
		pTestWidget = CMvFindRoundParamWidget::Instance();
		//pTestWidget->setWindowTitle("查找圆");
	}break;
	case 2://find line
	{
		pTestWidget = CMvColorImagesCut::Instance();
		//pTestWidget->setWindowTitle("裁剪图片");
	}break;
	case 3://find line
	{
		pTestWidget = CMvColorConversionBlackAndWhite::Instance();
		//pTestWidget->setWindowTitle("彩色转黑白");
	}break;
	case 4://find line
	{
		pTestWidget = CMvBlackAndWhiteConversionColor::Instance();
		//pTestWidget->setWindowTitle("黑白转彩色");
	}break;
	case 5://find line
	{
		pTestWidget = CMvFourArithmeticOperation::Instance();
		//pTestWidget->setWindowTitle("黑白转彩色");
	}break;
	default:
		break;
	}//switch (widgetType)

	if (pTestWidget)
	{
		pTestWidget->show();
	}//if (pTestWidget)
    return a.exec();
}
