#include "CMvBlobSortOutput.h"
#include "ui_CMvBlobSortOutput.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QDebug>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

////屏蔽QComboBox控件的鼠标滚动监听
//void QComboBox::wheelEvent(QWheelEvent *e)
//{
//
//}
//
////屏蔽SpinBox控件的鼠标滚动监听
//void QAbstractSpinBox::wheelEvent(QWheelEvent *e)
//{
//
//}

CMvBlobSortOutput * CMvBlobSortOutput::s_pCMvBlobSortOutput = nullptr;

CMvBlobSortOutput::CMvBlobSortOutput(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvBlobSortOutput)
{ 
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	//ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置单元格 等宽

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	m_signalEnable = true;
	//初始化数据 
	initCMvBlobSortOutput();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据彩色图像菜单动作选择，设置单元格显示内容
	connect(m_pColorImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取排序标准 数值
	connect(ui->comboBox_SortingCriteria, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetSortingCriteriaValue(int)));

	//获取排序类型
	connect(ui->comboBox_SortType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetSortTypeValue(int)));
	
	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	/*===============================================================================================*\
	**====================================功能栏信号与槽的链接=======================================**
	\*===============================================================================================*/

	//点击 单次
	connect(ui->pushButton_ones, SIGNAL(clicked()), this, SLOT(slotOnceIsClick()));

	//点击 确定
	connect(ui->pushButton_affirm, SIGNAL(clicked()), this, SLOT(slotMakeSureIsClick()));

	//点击 取消
	connect(ui->pbPrev_cancel, SIGNAL(clicked()), this, SLOT(slotCancelIsClick()));



	//设置关闭时释放内存
	//setAttribute(Qt::WA_DeleteOnClose);
}

CMvBlobSortOutput::~CMvBlobSortOutput()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_pColorImageMenuData.size() != 0)
	{
		for (int index = 0; index < m_pColorImageMenuData.size(); index++)
		{
			delete m_pColorImageMenuData[index]->pAction;
			delete m_pColorImageMenuData[index];
		}
		m_pColorImageMenuData.clear();
	}

	delete ui;
}


//单例
CMvBlobSortOutput * CMvBlobSortOutput::Instance()
{
	if (s_pCMvBlobSortOutput == nullptr)
	{
		s_pCMvBlobSortOutput = new CMvBlobSortOutput;
	}
	return s_pCMvBlobSortOutput;

}

//释放内存
void CMvBlobSortOutput::destroy()
{
	if (s_pCMvBlobSortOutput)
	{
		delete s_pCMvBlobSortOutput;
		s_pCMvBlobSortOutput = nullptr;
	}
}

//初始化数据 
void CMvBlobSortOutput::initCMvBlobSortOutput()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");

	//设置启用检测器
	ui->checkBox_enableFunc->setChecked(true);


	//获取排序标准 数值
	ui->comboBox_SortingCriteria->setCurrentIndex(0);
	
	//获取排序类型
	ui->comboBox_SortType->setCurrentIndex(0);


	m_signalEnable = true;
}

//获取排序标准 数值
void CMvBlobSortOutput::slotGetSortingCriteriaValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取排序标准" << ui->comboBox_SortingCriteria->itemText(index);
	}
}

//获取排序类型
void CMvBlobSortOutput::slotGetSortTypeValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取排序类型" << ui->comboBox_SortType->itemText(index);
	}
}




//初始化图片来源菜单
void CMvBlobSortOutput::initMenuByTest()
{
	m_pColorImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pColorImageMenuData);
}

void CMvBlobSortOutput::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pColorImageMenu->move(cursor().pos());
		m_pColorImageMenu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvBlobSortOutput::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";

	if (m_iCol == 1 && m_iRow == 0)
	{
		allMenuData = m_pColorImageMenuData ;
		ui->tableWidget_input->item(m_iRow, m_iCol)->setBackground(Qt::transparent);
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
void CMvBlobSortOutput::slotGetDetectorNameValue()
{
	if (m_signalEnable) {
		QString strText = ui->plainTextEdit_funcName->toPlainText();
		int nLength = strText.length();
		for (int index = 0; index < nLength; index++)
		{
			if (strText[index] == '\n') {
				ui->plainTextEdit_funcName->blockSignals(true);
				strText.remove("\n");
				qDebug() << "获取检测器名称" << strText;
				ui->plainTextEdit_funcName->setPlainText(strText);
				ui->plainTextEdit_funcName->blockSignals(false);
			}
		}
	}
}

//获取启用检测器选中信息
void CMvBlobSortOutput::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 单次
void CMvBlobSortOutput::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvBlobSortOutput::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvBlobSortOutput::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}

