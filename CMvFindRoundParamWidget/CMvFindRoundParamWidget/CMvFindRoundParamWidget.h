#ifndef CMV_FIND_ROUND_PARAM
#define CMV_FIND_ROUND_PARAM 

#include "ui_CMvFindRoundParamWidget.h"
#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>
#include "CySecondLevelMenu.h"

namespace Ui {
	class CMvFindRoundParamWidget;
}

class CMvFindRoundParamWidget : public QWidget
{
    Q_OBJECT

private:
	Ui::CMvFindRoundParamWidget *ui;

	bool m_SignalEnable;

	/*==============================二级菜单相关成员变量定义========================================*/
	// 记录当前点击的位置
	int m_Row;
	int m_Col;
	CySecondLevelMenu *SecondLevelMenu;//定义类

	QVector<CySecondLevelMenu::cyMenu*>  m_AllImageSourceMenuData;//图片来源菜单数据
	QVector<CySecondLevelMenu::cyMenu*>  m_AllROISourceMenuData;////ROI来源菜单数据
	QVector<CySecondLevelMenu::cyMenu*>  m_AllROIPositionUpdatingMenuData;//ROI位置修正菜单数据
	QVector<CySecondLevelMenu::cyMenu*>  m_AllMaskSourceMenuData;//掩膜来源菜单数据

	QMenu * m_ImageSourceMenu;//图片来源菜单
	QMenu * m_ROISourceMenu;//ROI来源菜单
	QMenu * m_ROIPositionUpdatingMenu;//ROI位置修正菜单
	QMenu * m_MaskSourceMenu;//掩膜来源菜单
							 /*==============================================================================================*/

public:
    CMvFindRoundParamWidget(QWidget *parent = Q_NULLPTR);
	~CMvFindRoundParamWidget();

	//初始化菜单
	void initMenu();

	//void testInit();

private slots:
	/*====================================输入设置槽函数=================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

	//获取ROI来源
	void slotGetROISourcesValue(int index);

	//获取自己创建选中信息
	void slotGetCreateYourselfValue(bool state);

	/*==============二级菜单相关槽函数声明================*/
	////菜单动作点击
	//void soltMenuTriggered(QAction*);

	////根据点击位置选择弹框
	//void slotClickPushButton(int, int);
	/*===================================================*/
	/*============================================================================================*/

	///*===================================参数设置槽函数==================================================*/
	////获取边缘阈值 数值
	//void slotGetEdgeThresholdtValue(int index);

	////获取边缘梯度阈值 数值
	//void slotGetEdgeGradientThresholdtValue(int Value);

	////获取边缘极性 数值
	//void slotGetCoordinateInputValue(int index);

	////获取扫描点数
	//void slotGetScanPointsValue(int Value);

	////获取抽样点数 数值
	//void slotGetSamplingPointsValue(int Value);

	////获取检测方向 数值
	//void slotGetDirectionOfDetectionValue(int index);

	////获取拟合范围 数值
	//void slotGetScopeOfFitValue(int Value);

	////获取拟合误差限制 数值
	//void slotGetFittingErrorlimitsValue(int Value);

	////获取最小直线长度 数值
	//void slotGetMinimumLineLengthValue(int Value);

	////获取最大直线长度 数值
	//void slotGetMaximumLineLengthValue(int Value);
	///*============================================================================================*/

	///*================================掩膜设置槽函数==========================================*/

	////检测区域的掩膜 数值
	//void slotMaskOfDetectionAreaValue(int Index);

	////获取编辑方式 数值
	//void slotEditModeValue(int Index);

	////获取画笔尺寸 数值
	//void slotBrushSizeValue(int Value);

	////点击清空掩膜
	//void slotEmptyMaskIsClick();

	////点击掩盖所有
	//void slotCoverUpEverythingClick();

	////点击保存修改
	//void slotSaveChangesClick();

	///*============================================================================================*/

	///*===================================结果绘制槽函数=============================================*/
	////获取线条宽度 数值
	//void slotGetLineWidthValue(int Value);

	////获取启动绘制选中信息
	//void slotGetStartUpDrawingValue(bool state);

	////获取线条颜色 数值
	//void slotGetLineColourValue(int index);
	///*============================================================================================*/

	///*===================================功能栏槽函数==============================================*/
	////点击 放大
	//void slotAmplifyThePictureIsClick();

	////点击 缩小
	//void slotShrinkThePictureIsClick();

	////点击 最好尺寸
	//void slotBestSizeOfPictureIsClick();

	////点击 锁定ROI
	//void slotLockROIIsClick();

	////点击 单次
	//void slotOnceIsClick();

	////点击 确定
	//void slotMakeSureIsClick();

	////点击 取消
	//void slotCancelIsClick();
	///*=========================================================================================================*/
private:
 
};

#endif // _DEBUG