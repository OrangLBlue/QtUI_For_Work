#ifndef CMV_BLOB_SCREEN
#define CMV_BLOB_SCREEN 

#include "CMvSecondLevelMenu.h"
#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QMutex>

namespace Ui {
	class CMvBlobScreen;
}

class CMvBlobScreen : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvBlobScreen* Instance();
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

	//获取面积上限
	void slotGetAreaMaxValue(double value);

	//获取面积下限
	void slotGetAreaMinValue(double value);

	//获取中心x上限
	void slotGetCenterXMaxValue(double value);

	//获取中心x下限
	void slotGetCenterXMinValue(double value);

	//获取中心y上限
	void slotGetCenterYMaxValue(double value);

	//获取中心y下限
	void slotGetCenterYMinValue(double value);

	//获取最小矩形宽度上限
	void slotGetRectangleMaxWidthValue(double value);

	//获取最小矩形宽度下限
	void slotGetRectangleMinWidthValue(double value);

	//获取最小矩形高度上限
	void slotGetRectangleMaxHightValue(double value);

	//获取最小矩形高度下限
	void slotGetRectangleMinHightValue(double value);

	//开启斜矩形长宽比筛选
	void slotGetLengthWidthRatioIsChecked(bool state);

	//获取最小矩形长宽比上限
	void slotGetMaxLengthWidthRatioValue(double value);

	//获取最小矩形长宽比下限
	void slotGetMinLengthWidthRatioValue(double value);

	//获取个数上限
	void slotGetNumberMaxValue(int value);

	//获取个数下限
	void slotGetNumberMinValue(int value);

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

	//点击显示Blob信息
	void slotShowIsClick();


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
	Ui::CMvBlobScreen *ui;

	static CMvBlobScreen* s_pCMvBlobScreen;

	CMvBlobScreen(QWidget *parent = Q_NULLPTR);
	~CMvBlobScreen();

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

	QVector<CMvSecondLevelMenu::cyAction*>  m_allImageSourceMenuData;//图片来源菜单数据

};

#endif // _DEBUG