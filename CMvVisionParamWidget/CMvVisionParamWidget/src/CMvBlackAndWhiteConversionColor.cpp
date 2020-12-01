#include "CMvBlackAndWhiteConversionColor.h"
#include "ui_CMvBlackAndWhiteConversionColor.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QDebug>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvBlackAndWhiteConversionColor * CMvBlackAndWhiteConversionColor::s_pBlackAndWhiteConversionColor = nullptr;

CMvBlackAndWhiteConversionColor::CMvBlackAndWhiteConversionColor(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvBlackAndWhiteConversionColor)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;
	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置单元格 等宽

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	//初始化所有二级菜单
	initMenuByTest();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据黑白图像单动作选择，设置单元格显示内容
	connect(m_pBlackAndWhiteImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName_2, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc_2, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	/*===============================================================================================*\
	**====================================功能栏信号与槽的链接=======================================**
	\*===============================================================================================*/

	//点击 单次
	connect(ui->pushButton_ones, SIGNAL(clicked()), this, SLOT(slotOnceIsClick()));

	//点击 确定
	connect(ui->pushButton_affirm, SIGNAL(clicked()), this, SLOT(slotMakeSureIsClick()));

	//点击 取消
	connect(ui->pbPrev_cancel, SIGNAL(clicked()), this, SLOT(slotCancelIsClick()));

	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig_4, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));


	//设置关闭时释放内存
	setAttribute(Qt::WA_DeleteOnClose);
}

CMvBlackAndWhiteConversionColor::~CMvBlackAndWhiteConversionColor()
{

	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_pBlackAndWhiteImageMenuData.size() != 0)
	{
		for (int index = 0; index < m_pBlackAndWhiteImageMenuData.size(); index++)
		{
			delete m_pBlackAndWhiteImageMenuData[index]->pAction;
			delete m_pBlackAndWhiteImageMenuData[index];
		}
		m_pBlackAndWhiteImageMenuData.clear();
	}

	delete ui;
}

CMvBlackAndWhiteConversionColor* CMvBlackAndWhiteConversionColor::Instance()
{
	if (s_pBlackAndWhiteConversionColor == nullptr)
	{
		s_pBlackAndWhiteConversionColor = new CMvBlackAndWhiteConversionColor;
	}
	return s_pBlackAndWhiteConversionColor;
}

void CMvBlackAndWhiteConversionColor::destroy()
{
	if (s_pBlackAndWhiteConversionColor)
	{
		delete s_pBlackAndWhiteConversionColor;
		s_pBlackAndWhiteConversionColor = nullptr;
	}
}

void CMvBlackAndWhiteConversionColor::initMenuByTest()
{
	//初始化图片来源菜单
	m_pBlackAndWhiteImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pBlackAndWhiteImageMenuData);
}

void CMvBlackAndWhiteConversionColor::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pBlackAndWhiteImageMenu->move(cursor().pos());
		m_pBlackAndWhiteImageMenu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvBlackAndWhiteConversionColor::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";

	if (m_iCol == 1)
	{
		allMenuData = m_pBlackAndWhiteImageMenuData;
	}

	for (auto it = allMenuData.cbegin(); it != allMenuData.cend(); ++it)
	{
		if ((*it)->pAction == action)
		{
			showInfoText = (*it)->funcName + "-" + (*it)->portName;
			qDebug() << "MenuName:  " << (*it)->funcName << " MenuId: " << (*it)->funcId
				<< " ActionName: " << (*it)->portName << " ActionId: " << (*it)->portId;
		}//if ((*it)->pAction.get() == action)
	}//for (auto it = allMenuData.cbegin(); it != allMenuData.cend(); ++it)

	ui->tableWidget_input->item(m_iRow, m_iCol)->setBackground(Qt::transparent);
	 //设置显示内容为选中内容
	pTableItem->setText(showInfoText);

	//初始化行列数据
	m_iRow = -1;
	m_iCol = -1;
}

/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvBlackAndWhiteConversionColor::slotGetDetectorNameValue()
{
	if (m_signalEnable) {
		QString strText = ui->plainTextEdit_funcName_2->toPlainText();
		int nLength = strText.length();
		for (int index = 0; index < nLength; index++)
		{
			if (strText[index] == '\n') {
				ui->plainTextEdit_funcName_2->blockSignals(true);
				strText.remove("\n");
				qDebug() << "获取检测器名称" << strText;
				ui->plainTextEdit_funcName_2->setPlainText(strText);
				ui->plainTextEdit_funcName_2->blockSignals(false);
			}
		}
	}
}


//获取启用检测器选中信息
void CMvBlackAndWhiteConversionColor::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc_2->isChecked();
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvBlackAndWhiteConversionColor::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig_4->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/

//点击 单次
void CMvBlackAndWhiteConversionColor::slotOnceIsClick()
{
	qDebug() << "单次被点了";
	//pushButton_ones
}

//点击 确定
void CMvBlackAndWhiteConversionColor::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
	//pushButton_ensure
}

//点击 取消
void CMvBlackAndWhiteConversionColor::slotCancelIsClick()
{
	qDebug() << "取消被点了";
	//pbPrev_cancel
}


