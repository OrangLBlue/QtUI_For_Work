#ifndef CYSENCONDLEVELMENU
#define CYSENCONDLEVELMENU

#include "ui_CMvFindLineParamWidget.h"
//#include "CMvFindLineParamWidget.h"
#include <QWidget>
#include <QVector>
#include <QString>
#include <QMenu>
#include <QAction>

class CySecondLevelMenu : public QWidget
{
	Q_OBJECT
public:
	explicit CySecondLevelMenu(QWidget *parent = 0);
	~CySecondLevelMenu();

	//定义Action结构体
	struct cyAction
	{
		QAction* pAction;
		int ActionId;
		QString ActionName;
	};

	//定义Menu结构体
	struct cyMenu
	{
		int MenuId;
		QString MenuName;
		QVector<cyAction*> childenAction;
	};

	/*==============================二级菜单相关函数声明===========================================*/
	//初始化所有菜单
	QMenu* initSecondLevelMenu(QVector<cyMenu*> &AllData, QWidget* cyWidget);

	//根据获得的数据进行菜单数据初始化
	void getDataToInitMenuData(QVector<cyMenu*> &AllData);

	//根据菜单数据数据初始化菜单
	QMenu * getDataToInitMenu(QVector<cyMenu*> AllData, QWidget* cyWidget);
	/*=============================================================================================*/

protected:
	//void CMvFindLineParamWidget::contextMenuEvent(QContextMenuEvent *event);//右键按钮弹出菜单

private slots :

	/*==============================二级菜单相关槽函数声明========================================*/
	//菜单动作点击
	//void soltMenuTriggered(QAction*);

	//根据点击位置选择弹框
	//void slotClickPushButton(int, int);
	/*============================================================================================*/
private:

};

#endif
