﻿#ifndef CMV_ADDITION_AND_SUBTRACTION
#define CMV_ADDITION_AND_SUBTRACTION

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvAdditionAndSubtraction;
}

class CMvAdditionAndSubtraction : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvAdditionAndSubtraction * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据 
	void initCMvAdditionAndSubtraction();

	//初始化二级菜单
	void initMenuByTest();

private slots:

	//获取当前算法选择 数值
	void slotGetAlgorithmSelectionValue(int index);

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
	//点击 放大
	void slotAmplifyThePictureIsClick();

	//点击 缩小
	void slotShrinkThePictureIsClick();

	//点击 最好尺寸
	void slotBestSizeOfPictureIsClick();

	//点击 锁定ROI
	void slotLockROIIsClick();

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
    Ui::CMvAdditionAndSubtraction * ui;

	static CMvAdditionAndSubtraction * s_pCMvAdditionAndSubtraction;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	int m_AlgorithmSelectionIndex;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pMakeImageMenu;//被处理图像菜单
	QMenu* m_pPendingImageMenu;//待处理图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pMakeImageMenuData;//被处理图像菜单数据
	QVector<CMvSecondLevelMenu::cyAction*>  m_pPendingImageMenuData;//待处理图像菜单数据

	CMvAdditionAndSubtraction(QWidget *parent = Q_NULLPTR);
	~CMvAdditionAndSubtraction();
};

#endif