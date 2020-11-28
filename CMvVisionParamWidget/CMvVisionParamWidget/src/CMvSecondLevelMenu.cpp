#include <time.h>
#include <QDebug>
#include "CMvSecondLevelMenu.h"


#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvSecondLevelMenu::CMvSecondLevelMenu(QWidget *parent)
	: QWidget(parent)
{
	
}

CMvSecondLevelMenu::~CMvSecondLevelMenu()
{

}

QMenu* CMvSecondLevelMenu::initMenu(QWidget* parent, const QVector<cyLinkInfo> &funcLinkList, QVector<CMvSecondLevelMenu::cyAction*> &menuActionList)
{
	QMenu* pMenu = new QMenu(parent);//创建菜单
	CMvSecondLevelMenu::cyAction* pMenuAction;
	QVector<cyPortInfo>::const_iterator ppPortIterator;
	QVector<cyPortInfo>::const_iterator ppEndPortIterator;
	QVector<cyLinkInfo>::const_iterator ppFuncIterator = funcLinkList.cbegin();
	QVector<cyLinkInfo>::const_iterator ppFuncEndIterator = funcLinkList.cend();

	//解析传入数据创建菜单
	for (; ppFuncIterator != ppFuncEndIterator; ++ppFuncIterator)
	{
		//创建算法子菜单,并命名
		const QVector<cyPortInfo> &portInfoList = (*ppFuncIterator).portInfoList;
		QMenu* pChildMenu = new QMenu((*ppFuncIterator).funcName);

		ppPortIterator = portInfoList.cbegin();
		ppEndPortIterator = portInfoList.cend();
		for (; ppPortIterator != ppEndPortIterator; ++ppPortIterator)
		{
			pMenuAction = new cyAction;
			pMenuAction->funcId = (*ppFuncIterator).funcId;
			pMenuAction->funcName = (*ppFuncIterator).funcName;
			pMenuAction->portId = (*ppPortIterator).portId;
			pMenuAction->portName = (*ppPortIterator).portName;
			pMenuAction->pAction = new QAction((*ppPortIterator).portName);

			pChildMenu->addAction(pMenuAction->pAction);
			menuActionList.push_back(pMenuAction);
		}//for (; ppPortIterator != ppEndPortIterator; ++ppPortIterator)

		pMenu->addMenu(pChildMenu);
	}//for (; ppFuncIterator != ppFuncEndIterator; ++ppFuncIterator)

	return pMenu;
}

QMenu* CMvSecondLevelMenu::initMenuByTest(QWidget* parent, QVector<CMvSecondLevelMenu::cyAction*> &menuActionList)
{
	int portId;
	QString portName, funcName;
	QString initPortName = tr("输出端口");
	QString initFuncName = tr("测量算法");
	CMvSecondLevelMenu::cyAction* pMenuAction;
	QMenu* pMenu = new QMenu(parent);//创建菜单
	
	//随机数种子
	srand(time(NULL));
	for (int iIndex = 0; iIndex < 5; ++iIndex)
	{
		//创建算法子菜单,并命名
		funcName = initFuncName + tr("%1").arg(iIndex + 1);
		QMenu* pChildMenu = new QMenu(funcName, parent);

		for (int jIndex = 0; jIndex < 4; ++jIndex)
		{
			portId = rand() % 3;//生成随机间隔1-4以内的随机id)
			portName = initPortName + tr("%1").arg(portId + 1);


			pMenuAction = new cyAction;
			pMenuAction->funcId = iIndex;
			pMenuAction->funcName = funcName;
			pMenuAction->portId = jIndex;
			pMenuAction->portName = portName;
			pMenuAction->pAction = new QAction(portName);

			pChildMenu->addAction(pMenuAction->pAction);
			menuActionList.push_back(pMenuAction);
		}//for (int jIndex = 0; jIndex < 4; ++jIndex)
		pMenu->addMenu(pChildMenu);
		//delete pChildMenu;
	}//for (int iIndex = 0; iIndex < 4; ++iIndex)

	return pMenu;
}
