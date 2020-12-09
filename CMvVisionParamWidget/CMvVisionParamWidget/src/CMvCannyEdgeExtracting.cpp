#include "CMvCannyEdgeExtracting.h"
#include "ui_CMvCannyEdgeExtracting.h"
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

CMvCannyEdgeExtracting* CMvCannyEdgeExtracting::s_pCMvCannyEdgeExtracting = nullptr;

CMvCannyEdgeExtracting::CMvCannyEdgeExtracting(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvCannyEdgeExtracting)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	//设置单元格 等宽
	//ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");
	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/

	//初始化数据
	initCMvCannyEdgeExtracting();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据图片来源菜单动作选择，设置单元格显示内容
	connect(m_pImageSourceMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));


	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取面积上限 数值
	connect(ui->doubleSpinBox_maxThreshold, SIGNAL(valueChanged(double)), this, SLOT(slotGetMaxThresholdValue(double)));

	//获取面积下限 数值
	connect(ui->doubleSpinBox_minThreshold, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinThresholdValue(double)));
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
CMvCannyEdgeExtracting::~CMvCannyEdgeExtracting()
{
	qDebug() << "析构函数";

	if (m_pImageSourceMenu)
	{
		for (int index = 0; index < m_pImageSourceMenu->actions().size(); index++)
		{
			delete m_pImageSourceMenu->actions()[0]->menu();
		}
		delete m_pImageSourceMenu;
		m_pImageSourceMenu = nullptr;
	}

	if (m_allImageSourceMenuData.size() != 0)
	{
		for (int index = 0; index < m_allImageSourceMenuData.size(); index++)
		{
			delete m_allImageSourceMenuData[index]->pAction;
			delete m_allImageSourceMenuData[index];
		}
		m_allImageSourceMenuData.clear();
	}

	delete ui;
}


//单例化
CMvCannyEdgeExtracting* CMvCannyEdgeExtracting::Instance()
{
	if (s_pCMvCannyEdgeExtracting == nullptr) {
		s_pCMvCannyEdgeExtracting = new CMvCannyEdgeExtracting;
	}
	return s_pCMvCannyEdgeExtracting;
}


//释放内存
void CMvCannyEdgeExtracting::destroy()
{
	if (s_pCMvCannyEdgeExtracting)
	{
		delete s_pCMvCannyEdgeExtracting;
		s_pCMvCannyEdgeExtracting = nullptr;
	}//if (s_pCMvCannyEdgeExtracting)
}

//初始化数据
void CMvCannyEdgeExtracting::initCMvCannyEdgeExtracting()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//设置高阈值
	ui->doubleSpinBox_maxThreshold->setValue(5);

	//设置面积下限
	ui->doubleSpinBox_minThreshold->setValue(5);

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;
}

/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvCannyEdgeExtracting::slotGetDetectorNameValue()
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
void CMvCannyEdgeExtracting::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvCannyEdgeExtracting::initMenu()
{

}

void CMvCannyEdgeExtracting::initMenuByTest()
{
	//初始化图片来源菜单
	m_pImageSourceMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allImageSourceMenuData);
}

//根据点击位置选择弹框
void CMvCannyEdgeExtracting::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pImageSourceMenu->move(cursor().pos());
		m_pImageSourceMenu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvCannyEdgeExtracting::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";
	if (m_iRow == 0)
	{
		allMenuData = m_allImageSourceMenuData;
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
//获取高阈值 数值
void CMvCannyEdgeExtracting::slotGetMaxThresholdValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取高阈值" << ui->doubleSpinBox_maxThreshold->value() << "  " << Value;
	}
}

//获取低阈值 数值
void CMvCannyEdgeExtracting::slotGetMinThresholdValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取低阈值" << ui->doubleSpinBox_minThreshold->value() << "  " << Value;
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/

//获取启动绘制选中信息
void CMvCannyEdgeExtracting::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvCannyEdgeExtracting::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvCannyEdgeExtracting::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvCannyEdgeExtracting::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvCannyEdgeExtracting::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvCannyEdgeExtracting::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvCannyEdgeExtracting::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvCannyEdgeExtracting::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
