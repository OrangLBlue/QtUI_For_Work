#include "CMvFourArithmeticOperation.h"
#include "ui_CMvFourArithmeticOperation.h"
#include <QStringList>
#include <QDebug>
#include <QTableWidgetItem>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvFourArithmeticOperation * CMvFourArithmeticOperation::s_pFourArithmeticOperation = nullptr;

CMvFourArithmeticOperation::CMvFourArithmeticOperation(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvFourArithmeticOperation)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);
	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置单元格 等宽
	ui->tableWidget_input->setItem(0, 0, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 0)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 0)->setText("未连接");

	ui->tableWidget_input->setItem(0, 2, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 2)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 2)->setText("未连接");

	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	m_signalEnable = true;

	m_iCol = -1;
	m_iRow = -1;

	initcomboBoxOfOperationChange();

	initMenuByTest();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据输入数值一菜单动作选择，设置单元格显示内容
	connect(m_pvalue1Menu, SIGNAL(triggered(QAction*)), this, SLOT(slotMenuTriggered(QAction*)));

	//根据输入数值二菜单动作选择，设置单元格显示内容
	connect(m_pvalue2Menu, SIGNAL(triggered(QAction*)), this, SLOT(slotMenuTriggered(QAction*)));

	
//选择四则运算
	connect(m_comboBox_operationChange, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeOperation(int)));
	//设置关闭窗体时释放资源
	setAttribute(Qt::WA_DeleteOnClose);
}

//析构函数
CMvFourArithmeticOperation::~CMvFourArithmeticOperation()
{
	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_value1MenuData.size() != 0)
	{
		for (int index = 0; index < m_value1MenuData.size(); index++)
		{
			delete m_value1MenuData[index]->pAction;
			delete m_value1MenuData[index];
		}
		m_value1MenuData.clear();
	}

	if (m_value2MenuData.size() != 0)
	{
		for (int index = 0; index < m_value2MenuData.size(); index++)
		{
			delete m_value2MenuData[index]->pAction;
			delete m_value2MenuData[index];
		}
		m_value2MenuData.clear();
	}

	delete ui;
}

//单例化
CMvFourArithmeticOperation * CMvFourArithmeticOperation::Instance()
{
	if (s_pFourArithmeticOperation == nullptr)
	{
		s_pFourArithmeticOperation = new CMvFourArithmeticOperation;
	}
	return s_pFourArithmeticOperation;
}

//释放内存
void CMvFourArithmeticOperation::destroy()
{
	if (s_pFourArithmeticOperation)
	{
		delete s_pFourArithmeticOperation;
		s_pFourArithmeticOperation = nullptr;
	}
}

//初始化四则运算选择框
void CMvFourArithmeticOperation::initcomboBoxOfOperationChange()
{
	m_comboBox_operationChange = new QComboBox(this);
	m_comboBox_operationChange->setObjectName(QStringLiteral("算法"));

	m_comboBox_operationChange->clear();
	QStringList fonts;
	fonts << tr("未选中算法") << "+" << "-" << "*" << "/";
	m_comboBox_operationChange->addItems(fonts);

	ui->tableWidget_input->setCellWidget(0, 1, m_comboBox_operationChange);
}


void CMvFourArithmeticOperation::initMenuByTest()
{
	//初始化数值一菜单
	m_pvalue1Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_value1MenuData);

	//初始化数值二菜单
	m_pvalue2Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_value2MenuData);

}

//根据点击位置选择弹框
void CMvFourArithmeticOperation::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (row == 0)
	{
		switch (col)
		{
		case 0:
			m_pvalue1Menu->move(cursor().pos());
			m_pvalue1Menu->show();

			qDebug() << "m_pvalue1Menu " << m_pvalue1Menu->isEmpty();

			break;

		case 2:
			m_pvalue2Menu->move(cursor().pos());
			m_pvalue2Menu->show();
			break;

		default:
			break;
		}
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvFourArithmeticOperation::slotMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";
	switch (m_iCol)
	{
	case 0:
		allMenuData = m_value1MenuData;
		break;

	case 2:
		allMenuData = m_value2MenuData;
		break;

	default:
		break;
	}
	ui->tableWidget_input->item(m_iRow, m_iCol)->setBackground(Qt::yellow);

	for (auto it = allMenuData.cbegin(); it != allMenuData.cend(); ++it)
	{
		if ((*it)->pAction == action)
		{
			showInfoText = (*it)->funcName + "-" + (*it)->portName;
			qDebug() << "MenuName:  " << (*it)->funcName << " MenuId: " << (*it)->funcId
				<< " ActionName: " << (*it)->portName << " ActionId: " << (*it)->portId;
		}//if ((*it)->pAction.get() == action)
	}//for (auto it = allMenuData.cbegin(); it != allMenuData.cend(); ++it)

	 //设置显示内容为选中内容
	pTableItem->setText(showInfoText);

	//初始化行列数据
	m_iRow = -1;
	m_iCol = -1;
}

//选择四则运算
void CMvFourArithmeticOperation::slotChangeOperation(int index)
{
	if (m_signalEnable)
	{
		qDebug() << "选择四则运算" << m_comboBox_operationChange->itemText(index);
	}
}

