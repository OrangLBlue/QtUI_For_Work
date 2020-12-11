#ifndef CMV_CHIP_MAIN_GRID
#define CMV_CHIP_MAIN_GRID

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvChipMainGrid;
}

class CMvChipMainGrid : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvChipMainGrid * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据
	void initCMvChipMainGrid();

	void initMenuByTest();

private slots:
	//选择二值化类型
	void slotChangeBinaryDetection(int index);

	//获取晶片灰度阈值
	void slotGetGrayLevelValue(int value);

	//获取主栅线条数
	void slotGetBranchesNumberValue(int value);

	//获取每条栅线面积上限
	void slotGetAreaMaxValue(int value);

	//获取每条栅线面积下限
	void slotGetAreaMinValue(int value);

	//开启图像预处理
	void slotGetImagePreprocessingIsChecked(bool state);

	//选择腐蚀内核
	void slotChangeCorrosiveCore(int index);

	//开启显示预处理图像
	void slotGetDisplayImageIsChecked(bool state);

	//点击学习当前值
	void slotGetDisplayImageIsClicked();

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
    Ui::CMvChipMainGrid * ui;

	static CMvChipMainGrid * s_pCMvChipMainGrid;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImageMenu;//彩色图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pColorImageMenuData;//彩色图像菜单数据

	CMvChipMainGrid(QWidget *parent = Q_NULLPTR);
	~CMvChipMainGrid();
};

#endif