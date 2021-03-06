﻿#ifndef CMV_COLOR_SELECTION
#define CMV_COLOR_SELECTION 

#include "CMvSecondLevelMenu.h"
#include <QMenu>

namespace Ui {
	class CMvColorSelection;
}

class CMvColorSelection : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvColorSelection* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();


	//初始化数据
	void initCMvColorSelection();
	//void testInit();

private slots:
	/*===============================================================================================*\
	**======================================输入设置槽函数===========================================**
	\*===============================================================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

	/*===============================================================================================*\
	**=================================二级菜单相关槽函数声明========================================**
	\*===============================================================================================*/
	//菜单动作点击
	void soltMenuTriggered(QAction*);

	//根据点击位置选择弹框
	void slotClickPushButton(int, int);

	/*===============================================================================================*\
	**=======================================结果判断槽函数==========================================**
	\*===============================================================================================*/
	//获取颜色空间
	void slotGetColorSpaceValue(int index);

	//点击显示颜色直方图
	void slotGetUnqualifiedPiontIsClick();

	//获取启用杂点剔除选中信息
	void slotGetMiscellaneousEliminationIsChecked(bool State);

	//获取面积上限 数值
	void slotGetMaxAreaValue(double Value);

	//获取面积下限 数值
	void slotGetMinAreaValue(double Value);

	//获取背景图像类型 数值
	void slotGetBackgroundTypeValue(int index);

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
	
private:
	Ui::CMvColorSelection *ui;

	static CMvColorSelection* s_pColorSelection;

	CMvColorSelection(QWidget *parent = Q_NULLPTR);
	~CMvColorSelection();

	bool m_signalEnable;
	
	/*===============================================================================================*\
	**===============================二级菜单相关成员变量定义========================================**
	\*===============================================================================================*/
	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;
	
	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pImageSourceMenu;//图片来源菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_allImageSourceMenuData;//图片来源菜单数据

};

#endif // _DEBUG