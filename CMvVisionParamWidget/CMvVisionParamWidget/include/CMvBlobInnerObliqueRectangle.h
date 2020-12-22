﻿#ifndef CMV_BLOB_INNER_OBLIQUE_RECTANGLE
#define CMV_BLOB_INNER_OBLIQUE_RECTANGLE 

#include "CMvSecondLevelMenu.h"
#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QMutex>

namespace Ui {
	class CMvBlobInnerObliqueRectangle;
}

class CMvBlobInnerObliqueRectangle : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvBlobInnerObliqueRectangle* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();

	//初始化界面
	void initBlobRapidDetection();

	//void testInit();
	
private slots:
	/*===============================================================================================*\
	**======================================输入设置槽函数===========================================**
	\*===============================================================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

	//获取ROI来源
	void slotGetROISourcesValue(int index);

	//获取自己创建选中信息
	void slotGetCreateYourselfValue(bool state);

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
	//获取灰度上限
	void slotGetGrayLevelMaxValue(int value);

	//获取灰度下限
	void slotGetGrayLevelMinValue(int value);

	//获取面积上限
	void slotGetAreaMaxValue(double value);

	//获取面积下限
	void slotGetAreaMinValue(double value);

	//获取最小矩形宽度上限
	void slotGetRectangleMaxWidthValue(double value);

	//获取最小矩形宽度下限
	void slotGetRectangleMinWidthValue(double value);

	//获取最小矩形高度上限
	void slotGetRectangleMaxHightValue(double value);

	//获取最小矩形高度下限
	void slotGetRectangleMinHightValue(double value);

	//开启面积筛选
	void slotGetAreaMinIsChecked(bool state);

	//开启矩形宽度筛选
	void slotGetRectangleMaxWidthIsChecked(bool state);

	//开启矩形高度筛选
	void slotGetRectangleMaxHightIsChecked(bool state);

	//点击显示BLOB信息(面积)
	void slotAreaShowIsClick();

	//点击显示BLOB信息(宽度)
	void slotWidthShowIsClick();

	//点击显示BLOB信息(高度)
	void slotHightShowIsClick();

	//获取blob形状
	void slotGetFormValue(int index);

	//获取宽度上限
	void slotGetMaxWidthValue(double value);

	//获取宽度下限
	void slotGetMinWidthValue(double value);

	//获取高度上限
	void slotGetMaxHightValue(double value);

	//获取高度下限
	void slotGetMinHightValue(double value);

	/*===============================================================================================*\
	**=======================================掩膜设置槽函数==========================================**
	\*===============================================================================================*/
	//检测区域的掩膜 数值
	void slotMaskOfDetectionAreaValue(int Index);

	//获取编辑方式 数值
	void slotEditModeValue(int Index);

	//获取画笔尺寸 数值
	void slotBrushSizeValue(int Value);

	//点击清空掩膜
	void slotEmptyMaskIsClick();

	//点击掩盖所有
	void slotCoverUpEverythingClick();

	//点击保存修改
	void slotSaveChangesClick();


	/*===============================================================================================*\
	**=======================================结果绘制页面槽函数======================================**
	\*===============================================================================================*/
	//获取线条宽度 数值
	void slotGetLineWidthValue(int Value);

	//获取启动绘制选中信息
	void slotGetStartUpDrawingValue(bool State);

	//获取线条颜色 数值
	void slotGetLineColourValue(int Index);


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
	Ui::CMvBlobInnerObliqueRectangle *ui;

	static CMvBlobInnerObliqueRectangle* s_pCMvBlobInnerObliqueRectangle;

	CMvBlobInnerObliqueRectangle(QWidget *parent = Q_NULLPTR);
	~CMvBlobInnerObliqueRectangle();

	bool m_signalEnable;

	int m_maskCount;//记录掩膜数量
	
	/*===============================================================================================*\
	**===============================二级菜单相关成员变量定义========================================**
	\*===============================================================================================*/
	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;
	
	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pImageSourceMenu;//图片来源菜单
	QMenu* m_pROISourceMenu;//ROI来源菜单
	QMenu* m_pROIPositionUpdatingMenu;//ROI位置修正菜单
	QMenu* m_pMaskSourceMenu;//掩膜来源菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_allImageSourceMenuData;//图片来源菜单数据
	QVector<CMvSecondLevelMenu::cyAction*>  m_allROISourceMenuData;////ROI来源菜单数据
	QVector<CMvSecondLevelMenu::cyAction*>  m_allROIPositionUpdatingMenuData;//ROI位置修正菜单数据
	QVector<CMvSecondLevelMenu::cyAction*>  m_allMaskSourceMenuData;//掩膜来源菜单数据
};

#endif // _DEBUG