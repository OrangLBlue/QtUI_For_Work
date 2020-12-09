#include "CMvManualBinary.h"
#include "ui_CMvManualBinary.h"
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

CMvManualBinary * CMvManualBinary::s_pCMvManualBinary = nullptr;

CMvManualBinary::CMvManualBinary(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvManualBinary)
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
	initCMvManualBinary();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据彩色图像菜单动作选择，设置单元格显示内容
	connect(m_pColorImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//选择二值化类型
	connect(ui->comboBox_binaryDetection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeBinaryDetection(int)));

	//获取灰度上限
	connect(ui->spinBox_grayLevelMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelMaxValue(int)));

	//获取灰度下限
	connect(ui->spinBox_grayLevelMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelMinValue(int)));

	//选择选定颜色
	connect(ui->comboBox_selectedColor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeSelectedColor(int)));

	//获取平均范围
	connect(ui->spinBox_averageRange, SIGNAL(valueChanged(int)), this, SLOT(slotGetAverageRangeValue(int)));

	//获取严格程度
	connect(ui->doubleSpinBox_strict, SIGNAL(valueChanged(double)), this, SLOT(slotGetStrictValue(double)));

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

CMvManualBinary::~CMvManualBinary()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	//if (m_pColorImageMenu)
	//{
	//	for (int index = 0; index < m_pColorImageMenu->actions().size(); index++)
	//	{
	//		delete m_pColorImageMenu->actions()[0]->menu();
	//	}
	//	delete m_pColorImageMenu;
	//	m_pColorImageMenu = nullptr;
	//}

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
CMvManualBinary * CMvManualBinary::Instance()
{
	if (s_pCMvManualBinary == nullptr)
	{
		s_pCMvManualBinary = new CMvManualBinary;
	}
	return s_pCMvManualBinary;

}

//释放内存
void CMvManualBinary::destroy()
{
	if (s_pCMvManualBinary)
	{
		delete s_pCMvManualBinary;
		s_pCMvManualBinary = nullptr;
	}
}

//初始化数据
void CMvManualBinary::initCMvManualBinary()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//选择二值化类型
	ui->comboBox_binaryDetection->setCurrentIndex(0);

	if (ui->comboBox_binaryDetection->currentIndex() == 1) {
		ui->widget_screen->setEnabled(true);
	}
	else if (ui->comboBox_binaryDetection->currentIndex() == 0) {
		ui->widget_screen->setEnabled(false);
	}

	//获取灰度上限
	ui->spinBox_grayLevelMax->setValue(5);

	//获取灰度下限
	ui->spinBox_grayLevelMin->setValue(5);

	//选择选定颜色
	ui->comboBox_selectedColor->setCurrentIndex(0);

	//获取平均范围
	ui->spinBox_averageRange->setValue(5);

	//获取严格程度
	ui->doubleSpinBox_strict->setValue(5);

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;

}

//选择二值化类型
void CMvManualBinary::slotChangeBinaryDetection(int index)
{
	if (m_signalEnable) {
		qDebug() << "选择二值化类型" << ui->comboBox_binaryDetection->itemText(index) << " " << index;
		if (index == 1) {
			ui->widget_screen->setEnabled(true);
		}
		else if (index == 0) {
			ui->widget_screen->setEnabled(false);
		}
	}
}

//获取灰度上限
void CMvManualBinary::slotGetGrayLevelMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度上限" << value;
	}
}

//获取灰度下限
void CMvManualBinary::slotGetGrayLevelMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度下限" << value;
	}
}

//选择选定颜色
void CMvManualBinary::slotChangeSelectedColor(int index)
{
	if (m_signalEnable) {
		qDebug() << "选择选定颜色" << ui->comboBox_selectedColor->itemText(index) << " " << index;
	}
}

//获取平均范围
void CMvManualBinary::slotGetAverageRangeValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取平均范围" << ui->spinBox_averageRange->value() << value;
	}
}

//获取严格程度
void CMvManualBinary::slotGetStrictValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取严格程度" << ui->doubleSpinBox_strict->value() << value;
	}
}

void CMvManualBinary::initMenuByTest()
{
	//初始化图片来源菜单
	m_pColorImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pColorImageMenuData);
}

void CMvManualBinary::slotClickPushButton(int row, int col)
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
void CMvManualBinary::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";

	if (m_iCol == 1 && m_iRow == 0)
	{
		allMenuData = m_pColorImageMenuData ;
		ui->tableWidget_input->item(m_iRow, m_iCol)->setBackground(Qt::yellow);
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
void CMvManualBinary::slotGetDetectorNameValue()
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
void CMvManualBinary::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvManualBinary::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvManualBinary::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvManualBinary::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvManualBinary::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvManualBinary::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvManualBinary::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvManualBinary::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvManualBinary::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}

