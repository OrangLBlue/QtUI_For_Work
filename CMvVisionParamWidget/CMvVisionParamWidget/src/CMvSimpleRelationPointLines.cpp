#include "CMvSimpleRelationPointLines.h"
#include "ui_CMvSimpleRelationPointLines.h"
#include <QCheckBox>
#include <QDebug>
#include <QTableWidgetItem>

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
//

CMvSimpleRelationPointLines* CMvSimpleRelationPointLines::s_pCMvSimpleRelationPointLines = nullptr;

CMvSimpleRelationPointLines::CMvSimpleRelationPointLines(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvSimpleRelationPointLines)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	ui->tableWidget_input->setItem(1, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(1, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(1, 1)->setText("某个检测器的输出");

	ui->groupBox_range->setGeometry(QRect(10, 30, 251, 80));
	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/
	m_AlgorithmSelectionIndex = ui->comboBox_surveyTools->currentIndex();//记录当前选择的算法

	//初始化数据
	initCMvSimpleRelationPointLines();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据图片来源菜单动作选择，设置单元格显示内容
	connect(m_pInput1Menu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//根据图片来源菜单动作选择，设置单元格显示内容
	connect(m_pInput2Menu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));


	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取选择测量工具
	connect(ui->comboBox_surveyTools, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetSurveyToolsValue(int)));

	//获取角度下限 数值
	connect(ui->doubleSpinBox_minAngle, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinAngleValue(double)));

	//获取角度上限 数值
	connect(ui->doubleSpinBox_maxAngle, SIGNAL(valueChanged(double)), this, SLOT(slotGetMaxAngleValue(double)));

	//获取距离下限 数值
	connect(ui->doubleSpinBox_minRange, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinRangeValue(double)));

	//获取距离上限 数值
	connect(ui->doubleSpinBox_maxRange, SIGNAL(valueChanged(double)), this, SLOT(slotGetMaxRangeValue(double)));
	
	/*===============================================================================================*\
	**====================================结果绘制信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

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

	//设置关闭窗体时释放资源
	//setAttribute(Qt::WA_DeleteOnClose);
}

//析构函数
CMvSimpleRelationPointLines::~CMvSimpleRelationPointLines()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_pInput1MenuData.size() != 0)
	{
		for (int index = 0; index < m_pInput1MenuData.size(); index++)
		{
			delete m_pInput1MenuData[index]->pAction;
			delete m_pInput1MenuData[index];
		}
		m_pInput1MenuData.clear();
	}

	if (m_pInput2MenuData.size() != 0)
	{
		for (int index = 0; index < m_pInput2MenuData.size(); index++)
		{
			delete m_pInput2MenuData[index]->pAction;
			delete m_pInput2MenuData[index];
		}
		m_pInput2MenuData.clear();
	}


	delete ui;
}


//单例化
CMvSimpleRelationPointLines* CMvSimpleRelationPointLines::Instance()
{
	if (s_pCMvSimpleRelationPointLines == nullptr) {
		s_pCMvSimpleRelationPointLines = new CMvSimpleRelationPointLines;
	}
	return s_pCMvSimpleRelationPointLines;
}


//释放内存
void CMvSimpleRelationPointLines::destroy()
{
	if (s_pCMvSimpleRelationPointLines)
	{
		delete s_pCMvSimpleRelationPointLines;
		s_pCMvSimpleRelationPointLines = nullptr;
	}//if (s_pCMvSimpleRelationPointLines)
}

//初始化数据
void CMvSimpleRelationPointLines::initCMvSimpleRelationPointLines()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//获取选择测量工具
	ui->comboBox_surveyTools->setCurrentIndex(0);

	m_AlgorithmSelectionIndex = ui->comboBox_surveyTools->currentIndex();//记录当前选择的算法

	//设置算法选择
	if (m_AlgorithmSelectionIndex == 0)
	{
		ui->groupBox_angle->setHidden(false);
		ui->groupBox_range->setHidden(true);
	}
	else
	{
		ui->groupBox_angle->setHidden(true);
		ui->groupBox_range->setHidden(false);
	}

	switch (m_AlgorithmSelectionIndex)
	{
	case 0: 		
		ui->tableWidget_input->item(0, 0)->setText("直线一输入");
		ui->tableWidget_input->item(1, 0)->setText("直线二输入");
		break;
	case 1:
		ui->tableWidget_input->item(0, 0)->setText("直线一输入");
		ui->tableWidget_input->item(1, 0)->setText("直线二输入");
		break;
	case 2:
		ui->tableWidget_input->item(0, 0)->setText("输入点");
		ui->tableWidget_input->item(1, 0)->setText("输入直线");
		break;
	case 3:
		ui->tableWidget_input->item(0, 0)->setText("输入点一");
		ui->tableWidget_input->item(1, 0)->setText("输入点二");
		break;
	default:
		break;
	}
	
	//获取角度下限 数值
	ui->doubleSpinBox_minAngle->setValue(0);
	
	//获取角度上限 数值
	ui->doubleSpinBox_maxAngle->setValue(180);
	
	//获取距离下限 数值
	ui->doubleSpinBox_minRange->setValue(0);
	
	//获取距离上限 数值
	ui->doubleSpinBox_maxRange->setValue(10000);
	

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;
}


/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvSimpleRelationPointLines::slotGetDetectorNameValue()
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
void CMvSimpleRelationPointLines::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvSimpleRelationPointLines::initMenu()
{

}

void CMvSimpleRelationPointLines::initMenuByTest()
{
	m_pInput1Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pInput1MenuData);
	m_pInput2Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pInput2MenuData);
}

//根据点击位置选择弹框
void CMvSimpleRelationPointLines::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pInput1Menu->move(cursor().pos());
		m_pInput1Menu->show();
	}
	if (col == 1 && row == 1)
	{
		m_pInput2Menu->move(cursor().pos());
		m_pInput2Menu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvSimpleRelationPointLines::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";
	if (m_iRow == 0)
	{
		allMenuData = m_pInput1MenuData;
	}

	if (m_iRow == 1)
	{
		allMenuData = m_pInput2MenuData;
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
**======================================参数设置页面槽函数=======================================**
\*===============================================================================================*/
//获取选择测量工具
void CMvSimpleRelationPointLines::slotGetSurveyToolsValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取选择测量工具" << ui->comboBox_surveyTools->itemText(index);
	}
	m_AlgorithmSelectionIndex = ui->comboBox_surveyTools->currentIndex();//记录当前选择的算法

	//设置算法选择
	if (m_AlgorithmSelectionIndex == 0)
	{
		ui->groupBox_angle->setHidden(false);
		ui->groupBox_range->setHidden(true);
	}
	else
	{
		ui->groupBox_angle->setHidden(true);
		ui->groupBox_range->setHidden(false);
	}

	switch (m_AlgorithmSelectionIndex)
	{
	case 0:
		ui->tableWidget_input->item(0, 0)->setText("直线一输入");
		ui->tableWidget_input->item(1, 0)->setText("直线二输入");
		break;
	case 1:
		ui->tableWidget_input->item(0, 0)->setText("直线一输入");
		ui->tableWidget_input->item(1, 0)->setText("直线二输入");
		break;
	case 2:
		ui->tableWidget_input->item(0, 0)->setText("输入点");
		ui->tableWidget_input->item(1, 0)->setText("输入直线");
		break;
	case 3:
		ui->tableWidget_input->item(0, 0)->setText("输入点一");
		ui->tableWidget_input->item(1, 0)->setText("输入点二");
		break;
	default:
		break;
	}
}

//获取角度下限 数值
void CMvSimpleRelationPointLines::slotGetMinAngleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取角度下限" << ui->doubleSpinBox_minAngle->value() << "  " << Value;
	}
}

//获取角度上限 数值
void CMvSimpleRelationPointLines::slotGetMaxAngleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取角度上限" << ui->doubleSpinBox_maxAngle->value() << "  " << Value;
	}
}

//获取距离下限 数值
void CMvSimpleRelationPointLines::slotGetMinRangeValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取距离下限" << ui->doubleSpinBox_minRange->value() << "  " << Value;
	}
}

//获取距离上限 数值
void CMvSimpleRelationPointLines::slotGetMaxRangeValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取距离上限" << ui->doubleSpinBox_maxRange->value() << "  " << Value;
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/

//获取启动绘制选中信息
void CMvSimpleRelationPointLines::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvSimpleRelationPointLines::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvSimpleRelationPointLines::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvSimpleRelationPointLines::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvSimpleRelationPointLines::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvSimpleRelationPointLines::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvSimpleRelationPointLines::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvSimpleRelationPointLines::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
