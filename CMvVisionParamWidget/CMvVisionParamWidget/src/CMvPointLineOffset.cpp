#include "CMvPointLineOffset.h"
#include "ui_CMvPointLineOffset.h"
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

CMvPointLineOffset* CMvPointLineOffset::s_pCMvPointLineOffset = nullptr;

CMvPointLineOffset::CMvPointLineOffset(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvPointLineOffset)
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
	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/

	//初始化数据
	initCMvPointLineOffset();

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
	//获取初始点X偏移 数值
	connect(ui->doubleSpinBox_initialOffsetX, SIGNAL(valueChanged(double)), this, SLOT(slotGetInitialOffsetXValue(double)));
	
	//获取初始点Y偏移 数值
	connect(ui->doubleSpinBox_initialOffsetY, SIGNAL(valueChanged(double)), this, SLOT(slotGetInitialOffsetYValue(double)));

	//点击初始点位置
	connect(ui->pushButton_study, SIGNAL(clicked()), this, SLOT(slotGetStudyIsClicked()));

	//开启初始点位置
	connect(ui->checkBox_initialPoint, SIGNAL(clicked(bool)), this, SLOT(slotGetInitialPointIsChecked(bool)));

	//获取初始点X 数值
	connect(ui->doubleSpinBox_initialPointX, SIGNAL(valueChanged(double)), this, SLOT(slotGetinitialPointXValue(double)));

	//获取初始点Y 数值
	connect(ui->doubleSpinBox_initialPointY, SIGNAL(valueChanged(double)), this, SLOT(slotGetInitialPointYValue(double)));

	//点击初始点位置应用手动设置
	connect(ui->pushButton_initialPoint, SIGNAL(clicked()), this, SLOT(slotGetInitialPointIsClicked()));

	//开启初始直线位置
	connect(ui->checkBox_initialStraightLine, SIGNAL(clicked(bool)), this, SLOT(slotGetInitialStraightLineIsChecked(bool)));

	//获取直线起点X 数值
	connect(ui->doubleSpinBox_initialStraightLineX, SIGNAL(valueChanged(double)), this, SLOT(slotGetInitialStraightLineXValue(double)));

	//获取直线起点Y： 数值
	connect(ui->doubleSpinBox_initialStraightLineY, SIGNAL(valueChanged(double)), this, SLOT(slotGetInitialStraightLineYValue(double)));

	//获取直线终点X 数值
	connect(ui->doubleSpinBox_straightLineEndPointX, SIGNAL(valueChanged(double)), this, SLOT(slotGetStraightLineEndPointXValue(double)));

	//获取直线终点Y 数值
	connect(ui->doubleSpinBox_straightLineEndPointY, SIGNAL(valueChanged(double)), this, SLOT(slotGetStraightLineEndPointYValue(double)));

	//点击直线初始位置应用手动设置
	connect(ui->pushButton_initialStraightLine, SIGNAL(clicked()), this, SLOT(slotGetInitialStraightLineIsClicked()));
	
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
CMvPointLineOffset::~CMvPointLineOffset()
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
CMvPointLineOffset* CMvPointLineOffset::Instance()
{
	if (s_pCMvPointLineOffset == nullptr) {
		s_pCMvPointLineOffset = new CMvPointLineOffset;
	}
	return s_pCMvPointLineOffset;
}


//释放内存
void CMvPointLineOffset::destroy()
{
	if (s_pCMvPointLineOffset)
	{
		delete s_pCMvPointLineOffset;
		s_pCMvPointLineOffset = nullptr;
	}//if (s_pCMvPointLineOffset)
}

//初始化数据
void CMvPointLineOffset::initCMvPointLineOffset()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//获取初始点X偏移 数值
	ui->doubleSpinBox_initialOffsetX->setValue(0);

	//获取初始点Y偏移 数值
	ui->doubleSpinBox_initialOffsetY->setValue(0);

	//开启初始点位置
	ui->checkBox_initialPoint->setChecked(false);

	ui->groupBox_initialPoint->setEnabled(ui->checkBox_initialPoint->isChecked());
	

	//获取初始点X 数值
	ui->doubleSpinBox_initialPointX->setValue(0);

	//获取初始点Y 数值
	ui->doubleSpinBox_initialPointY->setValue(0);


	//开启初始直线位置
	ui->checkBox_initialStraightLine->setChecked(false);

	ui->groupBox_initialStraightLine->setEnabled(ui->checkBox_initialStraightLine->isChecked());


	//获取直线起点X 数值
	ui->doubleSpinBox_initialStraightLineX->setValue(0);

	//获取直线起点Y： 数值
	ui->doubleSpinBox_initialStraightLineY->setValue(0);

	//获取直线终点X 数值
	ui->doubleSpinBox_straightLineEndPointX->setValue(0);

	//获取直线终点Y 数值
	ui->doubleSpinBox_straightLineEndPointY->setValue(0);


	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;
}


/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvPointLineOffset::slotGetDetectorNameValue()
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
void CMvPointLineOffset::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvPointLineOffset::initMenu()
{

}

void CMvPointLineOffset::initMenuByTest()
{
	m_pInput1Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pInput1MenuData);
	m_pInput2Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pInput2MenuData);
}

//根据点击位置选择弹框
void CMvPointLineOffset::slotClickPushButton(int row, int col)
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
void CMvPointLineOffset::soltMenuTriggered(QAction* action)
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
//获取初始点X偏移 数值
void CMvPointLineOffset::slotGetInitialOffsetXValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取初始点X偏移" << ui->doubleSpinBox_initialOffsetX->value() << "  " << Value;
	}
}

//获取初始点Y偏移 数值
void CMvPointLineOffset::slotGetInitialOffsetYValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取初始点Y偏移" << ui->doubleSpinBox_initialOffsetY->value() << "  " << Value;
	}
}

//点击初始点位置
void CMvPointLineOffset::slotGetStudyIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击初始点位置" ;
	}
}

//开启初始点位置
void CMvPointLineOffset::slotGetInitialPointIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启初始点位置" << state;
		ui->groupBox_initialPoint->setEnabled(state);
	}
}

//获取初始点X 数值
void CMvPointLineOffset::slotGetinitialPointXValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取初始点X" << ui->doubleSpinBox_initialPointX->value() << "  " << Value;
	}
}

//获取初始点Y 数值
void CMvPointLineOffset::slotGetInitialPointYValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取初始点Y" << ui->doubleSpinBox_initialPointY->value() << "  " << Value;
	}
}

//点击初始点位置应用手动设置
void CMvPointLineOffset::slotGetInitialPointIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击初始点位置应用手动设置";
	}
}

//开启初始直线位置
void CMvPointLineOffset::slotGetInitialStraightLineIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启初始直线位置" << state;
		ui->groupBox_initialStraightLine->setEnabled(state);
	}
}

//获取直线起点X 数值
void CMvPointLineOffset::slotGetInitialStraightLineXValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线起点X" << ui->doubleSpinBox_initialStraightLineX->value() << "  " << Value;
	}
}

//获取直线起点Y： 数值
void CMvPointLineOffset::slotGetInitialStraightLineYValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线起点Y" << ui->doubleSpinBox_initialStraightLineY->value() << "  " << Value;
	}
}

//获取直线终点X 数值
void CMvPointLineOffset::slotGetStraightLineEndPointXValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线终点X" << ui->doubleSpinBox_straightLineEndPointX->value() << "  " << Value;
	}
}

//获取直线终点Y 数值
void CMvPointLineOffset::slotGetStraightLineEndPointYValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线终点Y" << ui->doubleSpinBox_straightLineEndPointY->value() << "  " << Value;
	}
}

//点击直线初始位置应用手动设置
void CMvPointLineOffset::slotGetInitialStraightLineIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击直线初始位置应用手动设置";
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/

//获取启动绘制选中信息
void CMvPointLineOffset::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvPointLineOffset::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvPointLineOffset::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvPointLineOffset::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvPointLineOffset::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvPointLineOffset::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvPointLineOffset::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvPointLineOffset::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
