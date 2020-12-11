#ifndef CMV_BAR_CODE_DEFECT
#define CMV_BAR_CODE_DEFECT 

#include "CMvSecondLevelMenu.h"
#include <QMenu>

namespace Ui {
	class CMvBarCodeDefect;
}

class CMvBarCodeDefect : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvBarCodeDefect* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();

	//初始化数据
	void initCMvBarCodeDefect();
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
	//获取边缘规避大小
	void slotGetEdgeCircumventionSizeValue(double value);

	//获取缺陷最小面积
	void slotGetDefectiveAreaValue(double value);

	//点击显示条码信息
	void slotGetBarCodeInformationIsClick();

	//获取二值化高阈值
	void slotGetBinaryThresholdMaxValue(int value);

	//获取二值化低阈值
	void slotGetBinaryThresholdMinValue(int value);

	//获取单个条码面积上限
	void slotGetAreaMaxValue(int value);
	//获取单个条码面积下限
	void slotGetAreaMinValue(int value);

	//获取单个条码宽度上限
	void slotGetRectangleMaxWidthValue(int value);

	//获取单个条码宽度下限
	void slotGetRectangleMinWidthValue(int value);

	//获取单个条码高度上限
	void slotGetRectangleMaxHightValue(int value);

	//获取单个条码高度下限
	void slotGetRectangleMinHightValue(int value);

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
	Ui::CMvBarCodeDefect *ui;

	static CMvBarCodeDefect* s_pCMvBarCodeDefect;

	CMvBarCodeDefect(QWidget *parent = Q_NULLPTR);
	~CMvBarCodeDefect();

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