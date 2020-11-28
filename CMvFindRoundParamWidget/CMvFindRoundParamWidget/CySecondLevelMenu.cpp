#include "CySecondLevelMenu.h"
#include <QCheckBox>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QList>
#include <QAction>
#include <time.h>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CySecondLevelMenu::CySecondLevelMenu(QWidget *parent)
	: QWidget(parent)
{

}

/*========================================二级菜单=================================================*/
//初始化菜单
//void CySecondLevelMenu::InitMenu(QWidget* cyWidget)
//{
//	//初始化图片来源菜单
//	GetDataToInitMenuData(m_AllImageSourceMenuData);
//	m_ImageSourceMenu = GetDataToInitMenu(m_AllImageSourceMenuData, cyWidget);
//
//	//初始化ROI来源菜单
//	GetDataToInitMenuData(m_AllROISourceMenuData);
//	m_ROISourceMenu = GetDataToInitMenu(m_AllROISourceMenuData, cyWidget);
//
//	//初始化ROI位置修正菜单
//	GetDataToInitMenuData(m_AllROIPositionUpdatingMenuData);
//	m_ROIPositionUpdatingMenu = GetDataToInitMenu(m_AllROIPositionUpdatingMenuData, cyWidget);
//
//	//初始化掩膜来源菜单
//	GetDataToInitMenuData(m_AllMaskSourceMenuData);
//	m_MaskSourceMenu = GetDataToInitMenu(m_AllMaskSourceMenuData, cyWidget);
//}

/*-----------------------------------------------------------------
函数说明：初始化菜单
AllData：包含有id name 子动作的菜单结构体数组动态AllData 用于初始化菜单的数据
cyWidget：此菜单包含于cyWidget控件
-------------------------------------------------------------------*/
QMenu* CySecondLevelMenu::initSecondLevelMenu(QVector<cyMenu*> &AllData, QWidget* cyWidget)
{
	QMenu * TempMenu = new QMenu;
	//初始化菜单
	getDataToInitMenuData(AllData);
	TempMenu = getDataToInitMenu(AllData, cyWidget);

	return TempMenu;
}

//初始化菜单数据AllData(测试用例)
void CySecondLevelMenu::getDataToInitMenuData(QVector<cyMenu*> &AllData)
{
	//测试相关变量定义
	QString Str = tr("算法");
	QString Str1 = tr("参数");
	char Ch = '1';
	static int Count = 4;
	
	//随机数种子
	srand(time(NULL));

	//创建测试菜单数据
	for (int index = 0; index < Count; index++)
	{
		char Ch1 = '1';
		int nId = 0;

		cyMenu *myMenuData = new cyMenu;
		myMenuData->MenuName = Str + Ch;
		myMenuData->MenuId = Ch - '0';
		for (size_t i = 0; i < 4; i++)
		{
			nId += rand() % 3 + 1;//生成随机间隔1-4以内的随机id
			cyAction *myActionData = new cyAction;
			myActionData->ActionName = Str1 + Ch1;
			myActionData->ActionId = nId;
			myMenuData->childenAction.push_back(myActionData);
			Ch1++;

		}
		Ch++;
		AllData.push_back(myMenuData);

	}
	Count++;

	qDebug() << AllData[1]->MenuName << ":" << AllData[1]->childenAction[0]->ActionName << endl;

	//int row = AllData[1]->childenAction.indexOf("参数1");

	//qDebug() << row << endl;
}

//根据菜单数据AllData初创建菜单
QMenu * CySecondLevelMenu::getDataToInitMenu(QVector<cyMenu*> AllData, QWidget* cyWidget)
{
	QMenu * Menu = new QMenu(cyWidget);//创建菜单

	//解析传入数据创建菜单
	for (int indexI = 0; indexI < AllData.size(); indexI++)
	{
		QMenu * ChildMenu = new QMenu(AllData[indexI]->MenuName);//创建算法子菜单,并命名

		for (int indexJ = 0; indexJ < AllData[indexI]->childenAction.size(); indexJ++)
		{
			AllData[indexI]->childenAction[indexJ]->pAction = new QAction(AllData[indexI]->childenAction[indexJ]->ActionName);//创建动作

			ChildMenu->addAction(AllData[indexI]->childenAction[indexJ]->pAction);

			qDebug() << "menu " << AllData[indexI]->childenAction[indexJ]->pAction->parentWidget();
		}

		//m_ImageSourceMenuList.push_back(ChildMenu);
		Menu->addMenu(ChildMenu);
	}

	return Menu;
}

////右键事件
//void CMvFindLineParamWidget::contextMenuEvent(QContextMenuEvent *event)
//{
//    if(ui->pushButton->hasFocus()){
//		m_ImageSourceMenu->move(cursor().pos());
//		m_ImageSourceMenu->show();
//    }
//}



CySecondLevelMenu::~CySecondLevelMenu()
{
}
