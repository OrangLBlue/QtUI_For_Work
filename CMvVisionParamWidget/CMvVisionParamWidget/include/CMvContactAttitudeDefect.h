#ifndef CMV_CONTACT_ATTITUDE_DEFECT
#define CMV_CONTACT_ATTITUDE_DEFECT 

#include "CMvSecondLevelMenu.h"
#include <QWidget>

namespace Ui {
	class CMvContactAttitudeDefect;
}

class CMvContactAttitudeDefect : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvContactAttitudeDefect* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();

	//初始化界面
	void initCMvContactAttitudeDefect();

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
	//选择二值化类型
	void slotChangeBinaryDetection(int index);

	//获取灰度阈值
	void slotGetGrayLevelValue(int value);

	//开启开启灰尘检测
	void slotGetDustIsChecked(bool state);

	//获取载片灰度上限
	void slotGetGrayLevelMaxValue(int value);

	//获取载片灰度下限
	void slotGetGrayLevelMinValue(int value);

	//获取灰尘梯度上限
	void slotGetDustMaxValue(int value);

	//获取灰尘梯度下限
	void slotGetDustMinValue(int value);

	//获取查找范围
	void slotGetSeekScopeValue(int value);

	//获取灰尘最少点数
	void slotGetMinimumPointsNumberValue(int value);

	//开启杂点剔除参数
	void slotGetMiscellaneousIsChecked(bool state);

	//获取杂点面积上限
	void slotGetAreaMaxValue(double value);

	//获取杂点面积下限
	void slotGetAreaMinValue(double value);

	//点击显示杂点信息
	void slotGetMiscellaneousInformationIsClicked();

	//开启触点面积限定
	void slotGetContactAreaIsChecked(bool state);

	//获取触点面积上限
	void slotGetContactAreaMaxValue(double value);

	//获取触点面积下限
	void slotGetContactAreaMinValue(double value);

	//获取触点宽度上限
	void slotGetWidthMaxValue(double value);

	//获取触点宽度下限
	void slotGetWidthMinValue(double value);

	//获取触点高度上限
	void slotGetHightMaxValue(double value);

	//获取触点高度下限
	void slotGetHightMinValue(double value);

	//点击显示面积信息
	void slotGetAreaInformationIsClicked();

	//获取偏移距离阈值
	void slotGetOffsetDistanceValue(double value);

	//获取缺失距离阈值
	void slotGetMissingDistanceValue(double value);

	//获取偏移角度阈值
	void slotGetOffsetAngleValue(double value);

	//获取特征范围
	void slotGetCharacteristicValue(double value);

	//点击学习一次
	void slotGetStudyIsClicked();

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


	//绘制边缘轮廓
	void slotGetDrawEdgesValue(bool State);

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
	Ui::CMvContactAttitudeDefect *ui;

	static CMvContactAttitudeDefect* s_pCMvContactAttitudeDefect;

	CMvContactAttitudeDefect(QWidget *parent = Q_NULLPTR);
	~CMvContactAttitudeDefect();

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