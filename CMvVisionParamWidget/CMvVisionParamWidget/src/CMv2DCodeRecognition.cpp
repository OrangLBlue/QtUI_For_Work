#include "CMv2DCodeRecognition.h"
#include "ui_CMv2DCodeRecognition.h"
#include <QCheckBox>
#include <QDebug>
#include <QList>
#include <time.h>
#include <QTableWidgetItem>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER
//
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

CMv2DCodeRecognition* CMv2DCodeRecognition::s_pCMv2DCodeRecognition = nullptr;

CMv2DCodeRecognition::CMv2DCodeRecognition(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMv2DCodeRecognition)
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
	initCMv2DCodeRecognition();

	//初始化所有二级菜单
	initMenuByTest();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据图片来源菜单动作选择，设置单元格显示内容
	connect(m_pImageSourceMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//根据ROI来源菜单动作选择，设置单元格显示内容
	connect(m_pROISourceMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//根据ROI位置修正菜单动作选择，设置单元格显示内容
	connect(m_pROIPositionUpdatingMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//根据掩膜来源菜单动作选择，设置单元格显示内容
	connect(m_pMaskSourceMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	//点击ROI来源选择获取选项信息
	connect(ui->comboBox_imageSource, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetROISourcesValue(int)));

	//获取自己创建选中信息
	connect(ui->checkBox_roiCreat, SIGNAL(clicked(bool)), this, SLOT(slotGetCreateYourselfValue(bool)));


	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取绘制字符大小
	connect(ui->spinBox_size, SIGNAL(valueChanged(int)), this, SLOT(slotGetSizeValue(int)));

	//获取读码类型
	connect(ui->comboBox_readType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetReadTypeValue(int)));

	//获取二值化类型
	connect(ui->comboBox_binaryzation, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetBinaryzation(int)));

	//获取灰度阈值
	connect(ui->spinBox_grayLevel, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelValue(int)));

	//获取中心x上限
	connect(ui->spinBox_centerXMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetCenterXMaxValue(int)));

	//获取中心x下限
	connect(ui->spinBox_centerXMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetCenterXMinValue(int)));

	//获取中心y上限
	connect(ui->spinBox_centerYMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetCenterYMaxValue(int)));

	//获取中心y下限
	connect(ui->spinBox_centerYMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetCenterYMinValue(int)));
	
	//点击显示中心信息
	connect(ui->pushButton_showInformation, SIGNAL(clicked()), this, SLOT(slotShowInformationIsClick()));

	//获取个数上限
	connect(ui->spinBox_numberMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMaxValue(int)));

	//获取个数下限
	connect(ui->spinBox_numberMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMinValue(int)));

	//开启中心x筛选
	connect(ui->checkBox_centerX, SIGNAL(clicked(bool)), this, SLOT(slotGetCenterXMaxIsChecked(bool)));
	
	//开启中心y筛选
	connect(ui->checkBox_centerY, SIGNAL(clicked(bool)), this, SLOT(slotGetCenterYMaxIsChecked(bool)));
	

	/*===============================================================================================*\
	**====================================掩膜设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取检测区域的掩膜
	connect(ui->comboBox_dEtectionMask, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMaskOfDetectionAreaValue(int)));

	//获取编辑方式
	connect(ui->comboBox_editMode, SIGNAL(activated(int)), this, SLOT(slotEditModeValue(int)));

	//获取画笔尺寸 
	connect(ui->spinBox_lightTime, SIGNAL(valueChanged(int)), this, SLOT(slotBrushSizeValue(int)));

	//点击清空掩膜
	connect(ui->pushButton_maskNull, SIGNAL(clicked()), this, SLOT(slotEmptyMaskIsClick()));

	//点击掩盖所有
	connect(ui->pushButton_maskAll, SIGNAL(clicked()), this, SLOT(slotCoverUpEverythingClick()));

	//点击保存修改
	connect(ui->pushButton_saveMask, SIGNAL(clicked()), this, SLOT(slotSaveChangesClick()));


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
CMv2DCodeRecognition::~CMv2DCodeRecognition()
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
	
	if (m_allROISourceMenuData.size() != 0)
	{
		for (int index = 0; index < m_allROISourceMenuData.size(); index++)
		{
			delete m_allROISourceMenuData[index]->pAction;
			delete m_allROISourceMenuData[index];
		}
		m_allROISourceMenuData.clear();
	}

	if (m_allROIPositionUpdatingMenuData.size() != 0)
	{
		for (int index = 0; index < m_allROIPositionUpdatingMenuData.size(); index++)
		{
			delete m_allROIPositionUpdatingMenuData[index]->pAction;
			delete m_allROIPositionUpdatingMenuData[index];
		}
		m_allROIPositionUpdatingMenuData.clear();
	}

	if (m_allMaskSourceMenuData.size() != 0)
	{
		for (int index = 0; index < m_allMaskSourceMenuData.size(); index++)
		{
			delete m_allMaskSourceMenuData[index]->pAction;
			delete m_allMaskSourceMenuData[index];
		}
		m_allMaskSourceMenuData.clear();
	}

	delete ui;
}


//单例化
CMv2DCodeRecognition* CMv2DCodeRecognition::Instance()
{
	if (s_pCMv2DCodeRecognition == nullptr) {
		s_pCMv2DCodeRecognition = new CMv2DCodeRecognition;
	}
	return s_pCMv2DCodeRecognition;
}


//释放内存
void CMv2DCodeRecognition::destroy()
{
	if (s_pCMv2DCodeRecognition)
	{
		delete s_pCMv2DCodeRecognition;
		s_pCMv2DCodeRecognition = nullptr;
	}//if (c_pUniqueShowMessage)
}

//初始化界面
void CMv2DCodeRecognition::initCMv2DCodeRecognition()
{
	m_signalEnable = false;

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");

	//设置ROI来源
	ui->comboBox_imageSource->setCurrentIndex(0);
	
	
	//获取绘制字符大小
	ui->spinBox_size->setValue(0);
	
	//获取读码类型
	ui->comboBox_readType->setCurrentIndex(0);

	//获取二值化类型
	ui->comboBox_binaryzation->setCurrentIndex(0);
	if (ui->comboBox_binaryzation->currentIndex() == 0)
	{
		ui->spinBox_grayLevel->setEnabled(false);
		ui->label_grayLevel->setEnabled(false);
	}
	else
	{
		ui->spinBox_grayLevel->setEnabled(true);
		ui->label_grayLevel->setEnabled(true);
	}

	//获取灰度阈值
	ui->spinBox_grayLevel->setValue(0);

	//设置中心x上限
	ui->spinBox_centerXMax->setValue(0);

	//设置中心x下限
	ui->spinBox_centerXMin->setValue(0);

	//设置中心y上限
	ui->spinBox_centerYMax->setValue(0);

	//设置中心y下限
	ui->spinBox_centerYMin->setValue(0);

	//设置个数上限
	ui->spinBox_numberMax->setValue(0);

	//设置个数下限
	ui->spinBox_numberMin->setValue(0);

	//设置中心x选中
	ui->checkBox_centerX->setChecked(false);
	ui->groupBox_centerX->setEnabled(ui->checkBox_centerX->isChecked());

	//设置中心y选中
	ui->checkBox_centerY->setChecked(false);
	ui->groupBox_centerY->setEnabled(ui->checkBox_centerY->isChecked());


	//设置掩膜
	ui->comboBox_dEtectionMask->setCurrentIndex(0);
	ui->comboBox_editMode->setCurrentIndex(0);
	ui->spinBox_lightTime->setValue(5);

	if (ui->comboBox_dEtectionMask->currentIndex() == 0) {
		ui->widget_Mask->setEnabled(false);
	}
	else {
		ui->widget_Mask->setEnabled(false);
	}

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
void CMv2DCodeRecognition::slotGetDetectorNameValue()
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
void CMv2DCodeRecognition::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMv2DCodeRecognition::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMv2DCodeRecognition::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}


/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMv2DCodeRecognition::initMenu()
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

void CMv2DCodeRecognition::initMenuByTest()
{
	//初始化图片来源菜单
	m_pImageSourceMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allImageSourceMenuData);

	//初始化ROI来源菜单
	m_pROISourceMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allROISourceMenuData);

	//初始化ROI位置修正菜单
	m_pROIPositionUpdatingMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allROIPositionUpdatingMenuData);

	//初始化掩膜来源菜单
	m_pMaskSourceMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allMaskSourceMenuData);
}

//根据点击位置选择弹框
void CMv2DCodeRecognition::slotClickPushButton(int row, int col)
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
		case 1:
			m_pROISourceMenu->move(cursor().pos());
			m_pROISourceMenu->show();
			break;
		case 2:
			m_pROIPositionUpdatingMenu->move(cursor().pos());
			m_pROIPositionUpdatingMenu->show();
			break;
		case 3:
			m_pMaskSourceMenu->move(cursor().pos());
			m_pMaskSourceMenu->show();
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
void CMv2DCodeRecognition::soltMenuTriggered(QAction* action)
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

	case 1:
		allMenuData = m_allROISourceMenuData;
		break;

	case 2:
		allMenuData = m_allROIPositionUpdatingMenuData;
		break;

	case 3:
		allMenuData = m_allMaskSourceMenuData;
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

//获取喷码类型
void CMv2DCodeRecognition::slotGetReadTypeValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取喷码类型" << ui->comboBox_readType->itemText(index);
		if (index == 1)
		{
			ui->widget_binaryzation->setEnabled(false);
			
		}
		else
		{
			ui->widget_binaryzation->setEnabled(true);
			
		}
	}
}

//获取绘制字符大小
void CMv2DCodeRecognition::slotGetSizeValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取绘制字符大小" << value;
	}
}

//获取二值化类型
void CMv2DCodeRecognition::slotGetBinaryzation(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取二值化类型" << ui->comboBox_binaryzation->itemText(index);
		if (index == 0)
		{
			ui->spinBox_grayLevel->setEnabled(false);
			ui->label_grayLevel->setEnabled(false);
		}
		else
		{
			ui->spinBox_grayLevel->setEnabled(true);
			ui->label_grayLevel->setEnabled(true);
		}
	}
}

//获取灰度阈值
void CMv2DCodeRecognition::slotGetGrayLevelValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度阈值" << value;
	}
}



//开启条码中心X筛选
void CMv2DCodeRecognition::slotGetCenterXMaxIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启条码中心X筛选" << state;
		ui->groupBox_centerX->setEnabled(state);
	}
}

//获取中心x上限
void CMv2DCodeRecognition::slotGetCenterXMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心x上限" << value;
	}
}

//获取中心x下限
void CMv2DCodeRecognition::slotGetCenterXMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心x下限" << value;
	}
}

//开启开启条码中心y筛选
void CMv2DCodeRecognition::slotGetCenterYMaxIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启开启条码中心y筛选" << state;
		ui->groupBox_centerY->setEnabled(state);
	}
}

//获取中心y上限
void CMv2DCodeRecognition::slotGetCenterYMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心y上限" << value;
	}
}

//获取中心y下限
void CMv2DCodeRecognition::slotGetCenterYMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取中心y下限" << value;
	}
}

//点击显示中心信息
void CMv2DCodeRecognition::slotShowInformationIsClick()
{
	if (m_signalEnable) {
		qDebug() << "点击显示中心信息";
	}
}

//获取个数上限
void CMv2DCodeRecognition::slotGetNumberMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取个数上限" << value;
	}
}

//获取个数下限
void CMv2DCodeRecognition::slotGetNumberMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取个数下限" << value;
	}
}

/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值

void CMv2DCodeRecognition::slotMaskOfDetectionAreaValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取检测区域的掩膜" << ui->comboBox_dEtectionMask->itemText(Index) << " " << Index;

		if (Index == 0) {
			ui->widget_Mask->setEnabled(false);
		}
		else {
			ui->widget_Mask->setEnabled(true);
		}
	}
}

//获取编辑方式 数值
void CMv2DCodeRecognition::slotEditModeValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取编辑方式" << ui->comboBox_editMode->itemText(Index) << " " << Index;

		if (Index == 0) {//增加掩膜数量
			m_maskCount++;
			qDebug() << "已选择增加掩膜,当前掩膜数量为:" << m_maskCount;

		}
		else if (Index == 1) {//减少掩膜数量
			m_maskCount--;
			if (m_maskCount < 0) {
				m_maskCount = 0;
			}
			qDebug() << "已选择删除掩膜,当前掩膜数量为:" << m_maskCount;
		}

		if (m_maskCount == 0) {
			ui->pushButton_maskNull->setEnabled(false);
		}
		else {
			ui->pushButton_maskNull->setEnabled(true);
		}
	}
}

//获取画笔尺寸 数值
void CMv2DCodeRecognition::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMv2DCodeRecognition::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMv2DCodeRecognition::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMv2DCodeRecognition::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMv2DCodeRecognition::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMv2DCodeRecognition::slotGetStartUpDrawingValue(bool State)
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
void CMv2DCodeRecognition::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}


/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMv2DCodeRecognition::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMv2DCodeRecognition::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMv2DCodeRecognition::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMv2DCodeRecognition::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMv2DCodeRecognition::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMv2DCodeRecognition::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMv2DCodeRecognition::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
