#include "CMvRingDefect.h"
#include "ui_CMvRingDefect.h"
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

CMvRingDefect * CMvRingDefect::s_pCMvRingDefect = nullptr;

CMvRingDefect::CMvRingDefect(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvRingDefect)
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
	initCMvRingDefect();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据彩色图像菜单动作选择，设置单元格显示内容
	connect(m_pColorImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));


	//选择二值化类型
	connect(ui->comboBox_binaryDetection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeBinaryDetection(int)));

	//灰度阈值
	connect(ui->spinBox_grayLevel, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelValue(int)));

	//获取面积上限
	connect(ui->spinBox_areaMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetAreaMaxValue(int)));

	//获取面积下限
	connect(ui->spinBox_areaMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetAreaMinValue(int)));

	//点击显示面积信息
	connect(ui->pushButton_areaInformation, SIGNAL(clicked()), this, SLOT(slotGetAreaInformationIsClicked()));

	//获取曲率上限
	connect(ui->spinBox_curvatureMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetCurvatureMaxValue(int)));

	//获取曲率下限
	connect(ui->spinBox_curvatureMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetCurvatureMinValue(int)));

	//获取尺度上限
	connect(ui->spinBox_dimensionMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetDimensionMaxValue(int)));


	//获取尺度下限
	connect(ui->spinBox_dimensionMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetDimensionMinValue(int)));

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

CMvRingDefect::~CMvRingDefect()
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
CMvRingDefect * CMvRingDefect::Instance()
{
	if (s_pCMvRingDefect == nullptr)
	{
		s_pCMvRingDefect = new CMvRingDefect;
	}
	return s_pCMvRingDefect;

}

//释放内存
void CMvRingDefect::destroy()
{
	if (s_pCMvRingDefect)
	{
		delete s_pCMvRingDefect;
		s_pCMvRingDefect = nullptr;
	}
}

//初始化数据
void CMvRingDefect::initCMvRingDefect()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//选择二值化类型
	ui->comboBox_binaryDetection->setCurrentIndex(2);

	if (ui->comboBox_binaryDetection->currentIndex() < 2) {
		ui->label_grayLevel->setEnabled(true);
		ui->spinBox_grayLevel->setEnabled(true);
	}
	else {
		ui->label_grayLevel->setEnabled(false);
		ui->spinBox_grayLevel->setEnabled(false);
	}

	//灰度阈值
	ui->spinBox_grayLevel->setValue(5);

	//获取面积上限
	ui->spinBox_areaMax->setValue(5);

	//获取面积下限
	ui->spinBox_areaMin->setValue(5);

	//获取曲率上限
	ui->spinBox_curvatureMax->setValue(5);
	
	//获取曲率下限
	ui->spinBox_curvatureMin->setValue(5);
	
	//获取尺度上限
	ui->spinBox_dimensionMax->setValue(5);

	//获取尺度下限
	ui->spinBox_dimensionMin->setValue(5);
	
	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;

}

//选择二值化类型
void CMvRingDefect::slotChangeBinaryDetection(int index)
{
	if (m_signalEnable) {
		qDebug() << "选择二值化类型" << ui->comboBox_binaryDetection->itemText(index) << " " << index;
		if (index < 2) {
			ui->label_grayLevel->setEnabled(true);
			ui->spinBox_grayLevel->setEnabled(true);
		}
		else{
			ui->label_grayLevel->setEnabled(false);
			ui->spinBox_grayLevel->setEnabled(false);
		}
	}
}

//获取灰度阈值
void CMvRingDefect::slotGetGrayLevelValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度阈值" << value;
	}
}

//获取面积上限
void CMvRingDefect::slotGetAreaMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积上限" << ui->spinBox_areaMax->value() << value;
	}
}

//获取面积下限
void CMvRingDefect::slotGetAreaMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积下限" << ui->spinBox_areaMin->value() << value;
	}
}

//点击显示面积信息
void CMvRingDefect::slotGetAreaInformationIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击显示面积信息";
	}
}

//获取曲率上限
void CMvRingDefect::slotGetCurvatureMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取曲率上限" << ui->spinBox_curvatureMax->value() << value;
	}
}

//获取曲率下限
void CMvRingDefect::slotGetCurvatureMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取曲率下限" << ui->spinBox_curvatureMin->value() << value;
	}
}

//获取尺度上限
void CMvRingDefect::slotGetDimensionMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取尺度上限" << ui->spinBox_dimensionMax->value() << value;
	}
}

//获取尺度下限
void CMvRingDefect::slotGetDimensionMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取尺度下限" << ui->spinBox_dimensionMin->value() << value;
	}
}



void CMvRingDefect::initMenuByTest()
{
	//初始化图片来源菜单
	m_pColorImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pColorImageMenuData);
}

void CMvRingDefect::slotClickPushButton(int row, int col)
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
void CMvRingDefect::soltMenuTriggered(QAction* action)
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
void CMvRingDefect::slotGetDetectorNameValue()
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
void CMvRingDefect::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvRingDefect::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvRingDefect::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvRingDefect::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvRingDefect::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvRingDefect::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvRingDefect::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvRingDefect::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvRingDefect::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}

