#ifndef CMV_BLOB_CUMULATIVE_AREA
#define CMV_BLOB_CUMULATIVE_AREA

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvBlobCumulativeArea;
}

class CMvBlobCumulativeArea : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvBlobCumulativeArea * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据
	void initCMvBlobCumulativeArea();

	void initMenuByTest();

private slots:

	//获取面积限定上限
	void slotGetMaxAreaValue(int value);

	//获取面积限定下限
	void slotGetMinAreaValue(int value);

	//根据点击位置选择弹框
	void slotClickPushButton(int row, int col);

	//菜单动作点击
	void soltMenuTriggered(QAction* action);


	/*===============================================================================================*\
	**======================================功能栏槽函数=============================================**
	\*===============================================================================================*/

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
    Ui::CMvBlobCumulativeArea * ui;

	static CMvBlobCumulativeArea * s_pCMvBlobCumulativeArea;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImageMenu;//彩色图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pColorImageMenuData;//彩色图像菜单数据

	CMvBlobCumulativeArea(QWidget *parent = Q_NULLPTR);
	~CMvBlobCumulativeArea();
};

#endif