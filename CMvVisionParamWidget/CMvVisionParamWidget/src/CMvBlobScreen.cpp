#include "CMvBlobScreen.h"
#include "ui_CMvBlobScreen.h"
#include <QCheckBox>
#include <QDebug>
#include <QList>
#include <time.h>
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

CMvBlobScreen* CMvBlobScreen::s_pCMvBlobScreen = nullptr;

CMvBlobScreen::CMvBlobScreen(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvBlobScreen)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_maskCount = 0;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");
	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/
	
	//初始化参数
	initBlobRapidDetection();

	//初始化所有二级菜单
	initMenuByTest();

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
	
	//获取面积上限
	connect(ui->doubleSpinBox_areaMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetAreaMaxValue(double)));

	//获取面积下限
	connect(ui->doubleSpinBox_areaMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetAreaMinValue(double)));

	//获取中心x上限
	connect(ui->doubleSpinBox_centerXMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetCenterXMaxValue(double)));

	//获取中心x下限
	connect(ui->doubleSpinBox_centerXMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetCenterXMinValue(double)));

	//获取中心y上限
	connect(ui->doubleSpinBox_centerYMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetCenterYMaxValue(double)));

	//获取中心y下限
	connect(ui->doubleSpinBox_centerYMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetCenterYMinValue(double)));

	//获取最小矩形宽度上限
	connect(ui->doubleSpinBox_rectangleMaxWidth, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMaxWidthValue(double)));

	//获取最小矩形宽度下限
	connect(ui->doubleSpinBox_rectangleMinWidth, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMinWidthValue(double)));

	//获取最小矩形高度上限
	connect(ui->doubleSpinBox_rectangleMaxHight, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMaxHightValue(double)));

	//获取最小矩形高度下限
	connect(ui->doubleSpinBox_rectangleMinHight, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMinHightValue(double)));


	//开启斜矩形长宽比筛选
	connect(ui->checkBox_lengthWidthRatio, SIGNAL(clicked(bool)), this, SLOT(slotGetLengthWidthRatioIsChecked(bool)));

	//获取最小矩形长宽比上限
	connect(ui->doubleSpinBox_maxLengthWidthRatio, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMinHightValue(double)));

	//获取最小矩形长宽比下限
	connect(ui->doubleSpinBox_minLengthWidthRatio, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinLengthWidthRatioValue(double)));

	//获取个数上限
	connect(ui->spinBox_numberMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMaxValue(int)));

	//获取个数下限
	connect(ui->spinBox_numberMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMinValue(int)));

	//开启面积筛选
	connect(ui->checkBox_area, SIGNAL(clicked(bool)), this, SLOT(slotGetAreaMinIsChecked(bool)));

	//开启中心x筛选
	connect(ui->checkBox_centerX, SIGNAL(clicked(bool)), this, SLOT(slotGetCenterXMaxIsChecked(bool)));
	
	//开启中心y筛选
	connect(ui->checkBox_centerY, SIGNAL(clicked(bool)), this, SLOT(slotGetCenterYMaxIsChecked(bool)));

	//开启矩形宽度筛选
	connect(ui->checkBox_rectangleWidth, SIGNAL(clicked(bool)), this, SLOT(slotGetRectangleMaxWidthIsChecked(bool)));	

	//开启矩形高度筛选
	connect(ui->checkBox_rectangleHight, SIGNAL(clicked(bool)), this, SLOT(slotGetRectangleMaxHightIsChecked(bool)));

	//点击显示Blob信息
	connect(ui->pushButton_show, SIGNAL(clicked()), this, SLOT(slotShowIsClick()));



	/*===============================================================================================*\
	**====================================结果绘制信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取线条宽度 数值
	connect(ui->spinBox_lineWidth, SIGNAL(valueChanged(int)), this, SLOT(slotGetLineWidthValue(int)));

	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//获取线条颜色
	connect(ui->comboBox_lineColour, SIGNAL(activated(int)), this, SLOT(slotGetLineColourValue(int)));


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
	//setAttribute(Qt::WA_QuitOnClose);
	//setAttribute(Qt::WA_DeleteOnClose);
}


//析构函数
CMvBlobScreen::~CMvBlobScreen()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
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
CMvBlobScreen* CMvBlobScreen::Instance()
{
	if (s_pCMvBlobScreen == nullptr) {
		s_pCMvBlobScreen = new CMvBlobScreen;
	}
	return s_pCMvBlobScreen;
}


//释放内存
void CMvBlobScreen::destroy()
{
	if (s_pCMvBlobScreen)
	{
		delete s_pCMvBlobScreen;
		s_pCMvBlobScreen = nullptr;
	}//if (c_pUniqueShowMessage)
}

//初始化界面
void CMvBlobScreen::initBlobRapidDetection()
{
	m_signalEnable = false;
	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");

	//设置面积上限
	ui-> doubleSpinBox_areaMax->setValue(0);

	//设置面积下限
	ui->doubleSpinBox_areaMin->setValue(0);

	//设置中心x上限
	ui->doubleSpinBox_centerXMax->setValue(0);

	//设置中心x下限
	ui->doubleSpinBox_centerXMin->setValue(0);

	//设置中心y上限
	ui->doubleSpinBox_centerYMax->setValue(0);

	//设置中心y下限
	ui->doubleSpinBox_centerYMin->setValue(0);

	//设置最小矩形宽度上限
	ui->doubleSpinBox_rectangleMaxWidth->setValue(0);

	//设置最小矩形宽度下限
	ui->doubleSpinBox_rectangleMinWidth->setValue(0);

	//设置最小矩形高度上限
	ui->doubleSpinBox_rectangleMaxHight->setValue(0);

	//设置最小矩形高度下限
	ui->doubleSpinBox_rectangleMinHight->setValue(0);

	//设置个数上限
	ui->spinBox_numberMax->setValue(0);

	//设置个数下限
	ui->spinBox_numberMin->setValue(0);

	//设置面积筛选中
	ui->checkBox_area->setChecked(false);
	ui->groupBox_area->setEnabled(ui->checkBox_area->isChecked());

	//设置中心x选中
	ui->checkBox_centerX->setChecked(false);
	ui->groupBox_centerX->setEnabled(ui->checkBox_centerX->isChecked());

	//设置中心y选中
	ui->checkBox_centerY->setChecked(false);
	ui->groupBox_centerY->setEnabled(ui->checkBox_centerY->isChecked());

	//设置斜矩形宽度筛选选中
	ui->checkBox_rectangleWidth->setChecked(false);
	ui->groupBox_rectangleWidth->setEnabled(ui->checkBox_rectangleWidth->isChecked());

	//设置斜矩形高度筛选选中
	ui->checkBox_rectangleHight->setChecked(false);
	ui->groupBox_rectangleHight->setEnabled(ui->checkBox_rectangleHight->isChecked());

	//开启斜矩形长宽比筛选
	ui->checkBox_lengthWidthRatio->setChecked(false);
	ui->groupBox_lengthWidthRatio->setEnabled(ui->checkBox_lengthWidthRatio->isChecked());

	//获取最小矩形长宽比上限
	ui->doubleSpinBox_maxLengthWidthRatio->setValue(0);

	//获取最小矩形长宽比下限
	ui->doubleSpinBox_minLengthWidthRatio->setValue(0);
	

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);
	ui->comboBox_lineColour->setEnabled(ui->checkBox_valuTrig->isChecked());
	ui->spinBox_lineWidth->setEnabled(ui->checkBox_valuTrig->isChecked());
	ui->label_lineWidth->setEnabled(ui->checkBox_valuTrig->isChecked());
	ui->label_lineColour->setEnabled(ui->checkBox_valuTrig->isChecked());

	m_signalEnable = true;	
}

/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvBlobScreen::slotGetDetectorNameValue()
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
void CMvBlobScreen::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}


/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvBlobScreen::initMenu()
{
//	//初始化图片来源菜单
//	m_ImageSourceMenu = SecondLevelMenu->initSecondLevelMenu(m_AllImageSourceMenuData, ui->tableWidget_input);
//
//	//初始化ROI来源菜单
//	m_ROISourceMenu = SecondLevelMenu->initSecondLevelMenu(m_AllROISourceMenuData, ui->tableWidget_input);
//
//	//初始化ROI位置修正菜单
//	m_ROIPositionUpdatingMenu = SecondLevelMenu->initSecondLevelMenu(m_AllROIPositionUpdatingMenuData, ui->tableWidget_input);
//
//	//初始化掩膜来源菜单
//	m_MaskSourceMenu = SecondLevelMenu->initSecondLevelMenu(m_AllMaskSourceMenuData, ui->tableWidget_input);
}

void CMvBlobScreen::initMenuByTest()
{
	//初始化图片来源菜单
	m_pImageSourceMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allImageSourceMenuData);

}

//根据点击位置选择弹框
void CMvBlobScreen::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1)
	{
		switch(row)
		{
		case 0:
			m_pImageSourceMenu->move(cursor().pos());
			m_pImageSourceMenu->show();

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
void CMvBlobScreen::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";
	switch (m_iRow)
	{
	case 0:
		allMenuData = m_allImageSourceMenuData;
		break;

	default:
		break;
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
//开启面积筛选
void CMvBlobScreen::slotGetAreaMinIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启面积筛选" << state;
		ui->groupBox_area->setEnabled(state);
	}
}

//获取面积上限
void CMvBlobScreen::slotGetAreaMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积上限" << value;
	}
}

//获取面积下限
void CMvBlobScreen::slotGetAreaMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积下限" << value;
	}
}

//开启中心x筛选
void CMvBlobScreen::slotGetCenterXMaxIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启中心x筛选" << state;
		ui->groupBox_centerX->setEnabled(state);
	}
}

//获取中心x上限
void CMvBlobScreen::slotGetCenterXMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心x上限" << value;
	}
}

//获取中心x下限
void CMvBlobScreen::slotGetCenterXMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心x下限" << value;
	}
}

//开启中心y筛选
void CMvBlobScreen::slotGetCenterYMaxIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启中心y筛选" << state;
		ui->groupBox_centerY->setEnabled(state);
	}
}

//获取中心y上限
void CMvBlobScreen::slotGetCenterYMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心y上限" << value;
	}
}

//获取中心y下限
void CMvBlobScreen::slotGetCenterYMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心y下限" << value;
	}
}

//开启矩形宽度筛选
void CMvBlobScreen::slotGetRectangleMaxWidthIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启矩形宽度筛选" << state;
		ui->groupBox_rectangleWidth->setEnabled(state);
	}
}

//获取最小矩形宽度上限
void CMvBlobScreen::slotGetRectangleMaxWidthValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形宽度上限" << value;
	}
}

//获取最小矩形宽度下限
void CMvBlobScreen::slotGetRectangleMinWidthValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形宽度下限" << value;
	}
}

//开启矩形高度筛选
void CMvBlobScreen::slotGetRectangleMaxHightIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启矩形高度筛选" << state;
		ui->groupBox_rectangleHight->setEnabled(state);
	}
}

//获取最小矩形高度上限
void CMvBlobScreen::slotGetRectangleMaxHightValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形高度上限" << value;
	}
}

//获取最小矩形高度下限
void CMvBlobScreen::slotGetRectangleMinHightValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形高度下限" << value;
	}
}

//开启斜矩形长宽比筛选
void CMvBlobScreen::slotGetLengthWidthRatioIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启矩形高度筛选" << state;
		ui->groupBox_lengthWidthRatio->setEnabled(state);
	}
}

//获取最小矩形长宽比上限
void CMvBlobScreen::slotGetMaxLengthWidthRatioValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形长宽比上限" << value;
	}
}

//获取最小矩形长宽比下限
void CMvBlobScreen::slotGetMinLengthWidthRatioValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形长宽比下限" << value;
	}
}

//获取个数上限
void CMvBlobScreen::slotGetNumberMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取个数上限" << value;
	}
}

//获取个数下限
void CMvBlobScreen::slotGetNumberMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取个数下限" << value;
	}
}
//点击显示Blob信息
void CMvBlobScreen::slotShowIsClick()
{
	if (m_signalEnable) {
		qDebug() << "点击显示Blob信息";
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvBlobScreen::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvBlobScreen::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();

		ui->comboBox_lineColour->setEnabled(State);
		ui->spinBox_lineWidth->setEnabled(State);
		ui->label_lineWidth->setEnabled(State);
		ui->label_lineColour->setEnabled(State);
	}
}

//获取线条颜色 数值
void CMvBlobScreen::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvBlobScreen::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvBlobScreen::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvBlobScreen::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvBlobScreen::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvBlobScreen::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvBlobScreen::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvBlobScreen::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
