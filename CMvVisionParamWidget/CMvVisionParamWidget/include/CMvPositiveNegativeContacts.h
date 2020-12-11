#ifndef CMV_POSITIVE_NEGATIVE_CONTACTS
#define CMV_POSITIVE_NEGATIVE_CONTACTS

#include "CMvSecondLevelMenu.h"
#include <QMenu>

namespace Ui {
	class CMvPositiveNegativeContacts;
}

class CMvPositiveNegativeContacts : public QWidget
{
    Q_OBJECT

public:
	//单例化
	static CMvPositiveNegativeContacts* Instance();
	//释放内存
	static void destroy();

	//初始化菜单
	void initMenu();
	void initMenuByTest();


	//初始化数据
	void initCMvPositiveNegativeContacts();
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
	//获取计算模式
	void slotGetColorSpaceValue(int index);

	//获取检测方向
	void slotGetCorrosiveCoreValue(int index);

	//获取面积上限 数值
	void slotGetMaxAreaValue(int Value);

	//获取面积下限 数值
	void slotGetMinAreaValue(int Value);

	//点击显示面积信息
	void slotGetDisplayAreaInformationIsClick();

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
	
private:
	Ui::CMvPositiveNegativeContacts *ui;

	static CMvPositiveNegativeContacts* s_pCMvPositiveNegativeContacts;

	CMvPositiveNegativeContacts(QWidget *parent = Q_NULLPTR);
	~CMvPositiveNegativeContacts();

	bool m_signalEnable;
	
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