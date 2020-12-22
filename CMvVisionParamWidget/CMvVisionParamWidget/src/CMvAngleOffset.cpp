#include "CMvAngleOffset.h"
#include "ui_CMvAngleOffset.h"
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

CMvAngleOffset* CMvAngleOffset::s_pCMvAngleOffset = nullptr;

CMvAngleOffset::CMvAngleOffset(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvAngleOffset)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/
	//初始化数据
	initCMvAngleOffset();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据图片来源菜单动作选择，设置单元格显示内容
	connect(m_pInput1Menu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//点击学习直线初始位置
	connect(ui->pushButton_study, SIGNAL(clicked()), this, SLOT(slotGetStudyIsClicked()));

	//开启初始直线位置
	connect(ui->checkBox_initialStraightLine, SIGNAL(clicked(bool)), this, SLOT(slotGetInitialStraightLineIsChecked(bool)));

	//获取直线起点X 数值
	connect(ui->doubleSpinBox_initialStraightLineX, SIGNAL(valueChanged(double)), this, SLOT(slotGetInitialStraightLineXValue(double)));

	//获取直线起点Y 数值
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
CMvAngleOffset::~CMvAngleOffset()
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

	delete ui;
}

//单例化
CMvAngleOffset* CMvAngleOffset::Instance()
{
	if (s_pCMvAngleOffset == nullptr) {
		s_pCMvAngleOffset = new CMvAngleOffset;
	}
	return s_pCMvAngleOffset;
}

//释放内存
void CMvAngleOffset::destroy()
{
	if (s_pCMvAngleOffset)
	{
		delete s_pCMvAngleOffset;
		s_pCMvAngleOffset = nullptr;
	}//if (s_pCMvAngleOffset)
}

//初始化数据
void CMvAngleOffset::initCMvAngleOffset()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

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
void CMvAngleOffset::slotGetDetectorNameValue()
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
void CMvAngleOffset::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvAngleOffset::initMenu()
{

}

void CMvAngleOffset::initMenuByTest()
{
	m_pInput1Menu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pInput1MenuData);
}

//根据点击位置选择弹框
void CMvAngleOffset::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";

	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pInput1Menu->move(cursor().pos());
		m_pInput1Menu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvAngleOffset::soltMenuTriggered(QAction* action)
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
//点击学习直线初始位置
void CMvAngleOffset::slotGetStudyIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击学习直线初始位置" ;
	}
}

//开启初始直线位置
void CMvAngleOffset::slotGetInitialStraightLineIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启初始直线位置" << state;
		ui->groupBox_initialStraightLine->setEnabled(state);
	}
}

//获取直线起点X 数值
void CMvAngleOffset::slotGetInitialStraightLineXValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线起点X" << ui->doubleSpinBox_initialStraightLineX->value() << "  " << Value;
	}
}

//获取直线起点Y： 数值
void CMvAngleOffset::slotGetInitialStraightLineYValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线起点Y" << ui->doubleSpinBox_initialStraightLineY->value() << "  " << Value;
	}
}

//获取直线终点X 数值
void CMvAngleOffset::slotGetStraightLineEndPointXValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线终点X" << ui->doubleSpinBox_straightLineEndPointX->value() << "  " << Value;
	}
}

//获取直线终点Y 数值
void CMvAngleOffset::slotGetStraightLineEndPointYValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取直线终点Y" << ui->doubleSpinBox_straightLineEndPointY->value() << "  " << Value;
	}
}

//点击直线初始位置应用手动设置
void CMvAngleOffset::slotGetInitialStraightLineIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击直线初始位置应用手动设置";
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/

//获取启动绘制选中信息
void CMvAngleOffset::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvAngleOffset::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvAngleOffset::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvAngleOffset::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvAngleOffset::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvAngleOffset::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvAngleOffset::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvAngleOffset::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
