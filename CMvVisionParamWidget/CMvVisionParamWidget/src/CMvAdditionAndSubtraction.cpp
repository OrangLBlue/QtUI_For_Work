#include "CMvAdditionAndSubtraction.h"
#include "ui_CMvAdditionAndSubtraction.h"
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

CMvAdditionAndSubtraction * CMvAdditionAndSubtraction::s_pCMvAdditionAndSubtraction = nullptr;

CMvAdditionAndSubtraction::CMvAdditionAndSubtraction(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvAdditionAndSubtraction)
{ 
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置单元格 等宽

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	ui->tableWidget_input->setItem(1, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(1, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(1, 1)->setText("某个检测器的输出");

	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	m_AlgorithmSelectionIndex = 0;//初始化算法选择为index 0

	m_signalEnable = true;
	//初始化数据 
	initCMvAdditionAndSubtraction();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据被处理菜单动作选择，设置单元格显示内容
	connect(m_pMakeImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//根据待处理菜单动作选择，设置单元格显示内容
	connect(m_pPendingImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取算法选择 数值
	connect(ui->comboBox_algorithmSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetAlgorithmSelectionValue(int)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	/*===============================================================================================*\
	**====================================功能栏信号与槽的链接=======================================**
	\*===============================================================================================*/
	//点击 放大
	connect(ui->pushButton_zoomIn, SIGNAL(clicked()), this, SLOT(slotAmplifyThePictureIsClick()));

	//点击 缩小
	connect(ui->pushButton_zoomOut, SIGNAL(clicked()), this, SLOT(slotShrinkThePictureIsClick()));

	//点击 最好尺寸
	connect(ui->pushButton_zoomBest, SIGNAL(clicked()), this, SLOT(slotBestSizeOfPictureIsClick()));

	//点击 锁定ROI
	connect(ui->pushButton_lockRoiMove, SIGNAL(clicked()), this, SLOT(slotLockROIIsClick()));

	//点击 单次
	connect(ui->pushButton_ones, SIGNAL(clicked()), this, SLOT(slotOnceIsClick()));

	//点击 确定
	connect(ui->pushButton_affirm, SIGNAL(clicked()), this, SLOT(slotMakeSureIsClick()));

	//点击 取消
	connect(ui->pbPrev_cancel, SIGNAL(clicked()), this, SLOT(slotCancelIsClick()));


	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//设置关闭时释放内存
	//setAttribute(Qt::WA_DeleteOnClose);
}

CMvAdditionAndSubtraction::~CMvAdditionAndSubtraction()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_pMakeImageMenuData.size() != 0)
	{
		for (int index = 0; index < m_pMakeImageMenuData.size(); index++)
		{
			delete m_pMakeImageMenuData[index]->pAction;
			delete m_pMakeImageMenuData[index];
		}
		m_pMakeImageMenuData.clear();
	}

	if (m_pPendingImageMenuData.size() != 0)
	{
		for (int index = 0; index < m_pPendingImageMenuData.size(); index++)
		{
			delete m_pPendingImageMenuData[index]->pAction;
			delete m_pPendingImageMenuData[index];
		}
		m_pPendingImageMenuData.clear();
	}

	delete ui;
}

//单例
CMvAdditionAndSubtraction * CMvAdditionAndSubtraction::Instance()
{
	if (s_pCMvAdditionAndSubtraction == nullptr)
	{
		s_pCMvAdditionAndSubtraction = new CMvAdditionAndSubtraction;
	}
	return s_pCMvAdditionAndSubtraction;

}

//释放内存
void CMvAdditionAndSubtraction::destroy()
{
	if (s_pCMvAdditionAndSubtraction)
	{
		delete s_pCMvAdditionAndSubtraction;
		s_pCMvAdditionAndSubtraction = nullptr;
	}
}

//初始化数据 
void CMvAdditionAndSubtraction::initCMvAdditionAndSubtraction()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");

	//设置启用检测器
	ui->checkBox_enableFunc->setChecked(true);
	
	//设置处理算法选择
	ui->comboBox_algorithmSelection->setCurrentIndex(0);//设置位加法

	m_AlgorithmSelectionIndex = ui->comboBox_algorithmSelection->currentIndex();//记录当前选择的算法

	//设置算法选择
	if (m_AlgorithmSelectionIndex == 0)
	{
		ui->tableWidget_input->item(0, 0)->setText("被加图像");
		ui->tableWidget_input->item(1, 0)->setText("待加图像");
	
	} 
	else if (m_AlgorithmSelectionIndex == 1)
	{
		ui->tableWidget_input->item(0, 0)->setText("被减图像");
		ui->tableWidget_input->item(1, 0)->setText("待减图像");

	}
	
	//设置启用绘制
	ui->checkBox_valuTrig->setChecked(true);



	m_signalEnable = true;
}

//获取算法选择 数值
void CMvAdditionAndSubtraction::slotGetAlgorithmSelectionValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取算法选择" << ui->comboBox_algorithmSelection->itemText(index) << index;

		m_AlgorithmSelectionIndex = index;//记录当前选择的算法

		if (m_AlgorithmSelectionIndex == 0)
		{
			ui->tableWidget_input->item(0, 0)->setText("被加图像");
			ui->tableWidget_input->item(1, 0)->setText("待加图像");
			//ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
			//ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");
			//ui->tableWidget_input->item(1, 1)->setBackground(Qt::red);
			//ui->tableWidget_input->item(1, 1)->setText("某个检测器的输出");
		}
		else if (m_AlgorithmSelectionIndex == 1)
		{
			ui->tableWidget_input->item(0, 0)->setText("被减图像");
			ui->tableWidget_input->item(1, 0)->setText("待减图像");
			//ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
			//ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");
			//ui->tableWidget_input->item(1, 1)->setBackground(Qt::red);
			//ui->tableWidget_input->item(1, 1)->setText("某个检测器的输出");
		}
	}
}

//初始化图片来源菜单
void CMvAdditionAndSubtraction::initMenuByTest()
{
	m_pMakeImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pMakeImageMenuData);
	m_pPendingImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pPendingImageMenuData);
}

void CMvAdditionAndSubtraction::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pMakeImageMenu->move(cursor().pos());
		m_pMakeImageMenu->show();
	}
	if (col == 1 && row == 1)
	{
		m_pPendingImageMenu->move(cursor().pos());
		m_pPendingImageMenu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvAdditionAndSubtraction::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";

	if (m_iCol == 1 && m_iRow == 0)
	{
		allMenuData = m_pMakeImageMenuData;
		ui->tableWidget_input->item(m_iRow, m_iCol)->setBackground(Qt::transparent);
	}
	if (m_iCol == 1 && m_iRow == 1)
	{
		allMenuData = m_pPendingImageMenuData;
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
void CMvAdditionAndSubtraction::slotGetDetectorNameValue()
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
void CMvAdditionAndSubtraction::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvAdditionAndSubtraction::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvAdditionAndSubtraction::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvAdditionAndSubtraction::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvAdditionAndSubtraction::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvAdditionAndSubtraction::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvAdditionAndSubtraction::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvAdditionAndSubtraction::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvAdditionAndSubtraction::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}

