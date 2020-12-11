#ifndef CMV_CHIP_DEFECT
#define CMV_CHIP_DEFECT

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvChipDefect;
}

class CMvChipDefect : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvChipDefect * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据
	void initCMvChipDefect();

	void initMenuByTest();

private slots:
	//选择二值化类型
	void slotChangeBinaryDetection(int index);

	//获取晶片灰度阈值
	void slotGetGrayLevelValue(int value);

	//获取晶片宽度上限
	void slotGetRectangleMaxWidthValue(int value);

	//获取晶片宽度下限
	void slotGetRectangleMinWidthValue(int value);

	//获取晶片高度上限
	void slotGetRectangleMaxHightValue(int value);

	//获取晶片高度下限
	void slotGetRectangleMinHightValue(int value);

	//开启检测外凸缺陷
	void slotGetEvaginationIsChecked(bool state);

	//开启检测内陷缺陷
	void slotGetInvaginationIsChecked(bool state);

	//开启检测切角缺陷
	void slotGetCornerCutIsChecked(bool state);

	//获取外凸最小长度
	void slotGetMinimumLengthConvexValue(double value);

	//获取外凸边缘不平整度
	void slotGetEdgeUnevenEvaginationValue(double value);

	//获取内陷最小深度
	void slotGetMinimumDepthSubsidenceValue(double value);

	//获取内陷边缘不平整度
	void slotGetEdgeUnevenInvaginationValue(double value);

	//获取与顶点最小距离
	void slotGetMinimumRangeValue(int value);

	//获取与顶点最大距离
	void slotGetMaximumRangeValue(int value);

	//开启检测空洞缺陷
	void slotGetCavityIsChecked(bool state);

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
    Ui::CMvChipDefect * ui;

	static CMvChipDefect * s_pCMvChipDefect;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImageMenu;//彩色图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pColorImageMenuData;//彩色图像菜单数据

	CMvChipDefect(QWidget *parent = Q_NULLPTR);
	~CMvChipDefect();
};

#endif