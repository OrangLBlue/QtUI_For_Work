#ifndef CMV_BLOB_SORT_OUTPUT
#define CMV_BLOB_SORT_OUTPUT

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvBlobSortOutput;
}

class CMvBlobSortOutput : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvBlobSortOutput * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据 
	void initCMvBlobSortOutput();

	//初始化二级菜单
	void initMenuByTest();

private slots:

	//获取排序标准 数值
	void slotGetSortingCriteriaValue(int index);

	//获取排序类型
	void slotGetSortTypeValue(int index);

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
    Ui::CMvBlobSortOutput * ui;

	static CMvBlobSortOutput * s_pCMvBlobSortOutput;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImageMenu;//彩色图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pColorImageMenuData;//彩色图像菜单数据

	CMvBlobSortOutput(QWidget *parent = Q_NULLPTR);
	~CMvBlobSortOutput();
};

#endif