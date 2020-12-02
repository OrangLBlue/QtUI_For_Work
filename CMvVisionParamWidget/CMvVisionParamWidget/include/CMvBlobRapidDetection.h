#ifndef CMV_BLOB_RAPID_DETECTOION
#define CMV_BLOB_RAPID_DETECTOION 

#include "CMvSecondLevelMenu.h"
#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QMutex>

namespace Ui {
	class CMvBlobRapidDetection;
}

class CMvBlobRapidDetection : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvBlobRapidDetection* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();

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
	////获取边缘阈值 数值
	//获取灰度上限
	void slotGetGrayLevelMaxValue(int value);

	//获取灰度下限
	void slotGetGrayLevelMinValue(int value);

	//获取面积上限
	void slotGetAreaMaxValue(int value);

	//获取面积下限
	void slotGetAreaMinValue(int value);

	//获取中心x上限
	void slotGetCenterXMaxValue(int value);

	//获取中心x下限
	void slotGetCenterXMinValue(int value);

	//获取中心y上限
	void slotGetCenterYMaxValue(int value);

	//获取中心y下限
	void slotGetCenterYMinValue(int value);

	//获取最小矩形宽度上限
	void slotGetRectangleMaxWidthValue(int value);

	//获取最小矩形宽度下限
	void slotGetRectangleMinWidthValue(int value);

	//获取最小矩形高度上限
	void slotGetRectangleMaxHightValue(int value);

	//获取最小矩形高度下限
	void slotGetRectangleMinHightValue(int value);

	//获取个数上限
	void slotGetNumberMaxValue(int value);

	//获取个数下限
	void slotGetNumberMinValue(int value);

	//获取总面积上限
	void slotGetGrossAreaMaxValue(int value);

	//获取总面积下限
	void slotGetGrossAreaMinValue(int value);

	//开启面积筛选
	void slotGetAreaMinIsChecked(bool state);

	//开启中心x筛选
	void slotGetCenterXMaxIsChecked(bool state);

	//开启中心y筛选
	void slotGetCenterYMaxIsChecked(bool state);

	//开启矩形宽度筛选
	void slotGetRectangleMaxWidthIsChecked(bool state);

	//开启矩形高度筛选
	void slotGetRectangleMaxHightIsChecked(bool state);

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
	Ui::CMvBlobRapidDetection *ui;

	static CMvBlobRapidDetection* s_pBlobRapidDetection;

	CMvBlobRapidDetection(QWidget *parent = Q_NULLPTR);
	~CMvBlobRapidDetection();

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