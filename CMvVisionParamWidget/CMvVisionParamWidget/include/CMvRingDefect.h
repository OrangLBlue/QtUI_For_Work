#ifndef CMV_RING_DEFECT
#define CMV_RING_DEFECT

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvRingDefect;
}

class CMvRingDefect : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvRingDefect * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据
	void initCMvRingDefect();

	void initMenuByTest();

private slots:
	//选择二值化类型
	void slotChangeBinaryDetection(int index);

	//获取灰度阈值
	void slotGetGrayLevelValue(int value);

	//获取面积上限
	void slotGetAreaMaxValue(int value);

	//获取面积下限
	void slotGetAreaMinValue(int value);

	//点击显示面积信息
	void slotGetAreaInformationIsClicked();

	//获取曲率上限
	void slotGetCurvatureMaxValue(int value);

	//获取曲率下限
	void slotGetCurvatureMinValue(int value);

	//获取尺度上限
	void slotGetDimensionMaxValue(int value);

	//获取尺度下限
	void slotGetDimensionMinValue(int value);

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
    Ui::CMvRingDefect * ui;

	static CMvRingDefect * s_pCMvRingDefect;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImageMenu;//彩色图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pColorImageMenuData;//彩色图像菜单数据

	CMvRingDefect(QWidget *parent = Q_NULLPTR);
	~CMvRingDefect();
};

#endif