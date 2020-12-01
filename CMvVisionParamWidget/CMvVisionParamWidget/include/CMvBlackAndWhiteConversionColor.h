#pragma once

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvBlackAndWhiteConversionColor;
}

class CMvBlackAndWhiteConversionColor : public QWidget
{
    Q_OBJECT

public:
	static CMvBlackAndWhiteConversionColor* Instance();

	static void destroy();

	void initMenuByTest();

private slots:

	//根据点击位置选择弹框
	void slotClickPushButton(int row, int col);

	//菜单动作点击
	void soltMenuTriggered(QAction* action);


	/*===============================================================================================*\
	**=======================================结果绘制页面槽函数======================================**
	\*===============================================================================================*/
	//获取启动绘制选中信息
	void slotGetStartUpDrawingValue(bool State);

	/*===============================================================================================*\
	**======================================功能栏槽函数=============================================**
	\*===============================================================================================*/

	//点击 单次
	void slotOnceIsClick();

	//点击 确定
	void slotMakeSureIsClick();

	//点击 取消
	void slotCancelIsClick();

	/*===============================================================================================*\
	**======================================输入设置槽函数===========================================**
	\*===============================================================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

private:
    Ui::CMvBlackAndWhiteConversionColor *ui;

	static CMvBlackAndWhiteConversionColor * s_pBlackAndWhiteConversionColor;

	CMvBlackAndWhiteConversionColor(QWidget *parent = Q_NULLPTR);
	~CMvBlackAndWhiteConversionColor();

	bool m_signalEnable;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pBlackAndWhiteImageMenu;//黑白图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pBlackAndWhiteImageMenuData;//黑白图像菜单数据

};
