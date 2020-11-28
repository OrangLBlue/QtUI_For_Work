#ifndef CYSENCONDLEVELMENU
#define CYSENCONDLEVELMENU


#include <QMenu>
#include <QAction>
#include <QVector>
#include <QString>

class CMvSecondLevelMenu : public QWidget
{
	Q_OBJECT
public:
	explicit CMvSecondLevelMenu(QWidget *parent = 0);
	~CMvSecondLevelMenu();

	//定义Action结构体
	typedef struct _cyAction
	{
		short portId;
		short funcId;
		QString portName;
		QString funcName;
		QAction* pAction;
	}cyAction;

	typedef struct _cyPortInfo
	{
		short portId;
		QString portName;
	}cyPortInfo;

	typedef struct _cyLinkInfo
	{
		short funcId;
		QString funcName;
		QVector<cyPortInfo> portInfoList;
	}cyLinkInfo;


	/***********************************************************************\
	*  @fn     initMenu
	*  @brief  根据菜单数据初始化菜单
	*  @param  funcLinkList:		[IN]		此菜单初始信息
	*  @param  parent:				[IN]		此菜单依赖的上层控件
	*  @param  menuActionList:		[OUT]		此菜单包含的动作信息
	*  @return 菜单指针
	************************************************************************/
	QMenu* initMenu(QWidget* parent, const QVector<cyLinkInfo> &funcLinkList, QVector<CMvSecondLevelMenu::cyAction*> &menuActionList);


	/***********************************************************************\
	*  @fn     initMenuByTest
	*  @brief  测试时根据菜单数据初始化菜单
	*  @param  parent:				[IN]		此菜单依赖的上层控件
	*  @param  menuActionList:		[OUT]		此菜单包含的动作信息
	*  @return 菜单指针
	************************************************************************/
	QMenu* initMenuByTest(QWidget* parent, QVector<CMvSecondLevelMenu::cyAction*> &menuActionList);
};

#endif
