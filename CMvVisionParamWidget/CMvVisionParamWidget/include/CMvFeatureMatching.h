#ifndef CMV_FEATURE_MATCHING
#define CMV_FEATURE_MATCHING 

#include "CMvSecondLevelMenu.h"
#include <QMenu>
#include <QWidget>

namespace Ui {
	class CMvFeatureMatching;
}

class CMvFeatureMatching : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvFeatureMatching* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();

	//初始化数据
	void initCMvFeatureMatching();
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

	//点击编辑轮廓
	void slotGetEditingContoursIsClick();

	//获取检测模式 数值
	void slotGetDetectionModeValue(int index);

	//获取边缘阈值
	void slotGetEdgeThresholdtValue(int index);

	//获取边缘梯度阈值 数值
	void slotGetEdgeGradientThresholdtValue(int Value);

	//获取边缘极性检测方式 数值
	void slotGetEdgePolarityValue(int index);

	//获取检测尺度 数值
	void slotGetDetectionScaleValue(double Value);

	//获取定位尺度
	void slotGetPositioningScalesValue(int index);

	//获取尺度参数 数值
	void slotGetScaleParameterValue(double Value);

	//获取滤波尺寸 数值
	void slotGetFilterSizeValue(int index);

	//获取相邻目标最小距离 数值
	void slotGetMinimumRangeValue(int Value);

	//获取最小匹配度 数值
	void slotGetMinimumMatchingValue(double Value);

	//获取最小角度 数值
	void slotGetMinimumAngleValue(double Value);

	//获取最大角度 数值
	void slotGetMaximumAngleValue(double Value);

	//获取比例下限 数值
	void slotGetMinScaleValue(double Value);

	//获取比例上限 数值
	void slotGetMaxScaleValue(double Value);

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
	Ui::CMvFeatureMatching *ui;

	static CMvFeatureMatching* s_pCMvFeatureMatching;

	CMvFeatureMatching(QWidget *parent = Q_NULLPTR);
	~CMvFeatureMatching();

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