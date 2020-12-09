﻿#include "CMvImageDefect.h"
#include "ui_CMvImageDefect.h"
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

CMvImageDefect* CMvImageDefect::s_pCMvImageDefect = nullptr;

CMvImageDefect::CMvImageDefect(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvImageDefect)
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

	//初始化数据
	initCMvImageDefect();

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
	//点击编辑模板
	connect(ui->pushButton_editTemplate, SIGNAL(clicked()), this, SLOT(slotGetEditTemplateIsClick()));

	//点击显示差异图像
	connect(ui->pushButton_ImageDifferences, SIGNAL(clicked()), this, SLOT(slotGetImageDifferencesIsClick()));

	//点击显示缺陷信息
	connect(ui->pushButton_defectiveInformation, SIGNAL(clicked()), this, SLOT(slotGetDefectiveInformationIsClick()));

	//获取缺陷类型 数值
	connect(ui->comboBox_defectType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetDefectTypeValue(int)));

	//获取灰度上限
	connect(ui->spinBox_grayLevelMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelMaxValue(int)));

	//获取灰度下限
	connect(ui->spinBox_grayLevelMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelMinValue(int)));

	//获取面积上限
	connect(ui->doubleSpinBox_areaMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetAreaMaxValue(double)));

	//获取面积下限
	connect(ui->doubleSpinBox_areaMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetAreaMinValue(double)));

	//获取最小矩形宽度上限
	connect(ui->doubleSpinBox_rectangleMaxWidth, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMaxWidthValue(double)));

	//获取最小矩形宽度下限
	connect(ui->doubleSpinBox_rectangleMinWidth, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMinWidthValue(double)));

	//获取最小矩形高度上限
	connect(ui->doubleSpinBox_rectangleMaxHight, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMaxHightValue(double)));

	//获取最小矩形高度下限
	connect(ui->doubleSpinBox_rectangleMinHight, SIGNAL(valueChanged(double)), this, SLOT(slotGetRectangleMinHightValue(double)));

	//开启面积筛选
	connect(ui->checkBox_area, SIGNAL(clicked(bool)), this, SLOT(slotGetAreaMinIsChecked(bool)));

	//开启矩形宽度筛选
	connect(ui->checkBox_rectangleWidth, SIGNAL(clicked(bool)), this, SLOT(slotGetRectangleMaxWidthIsChecked(bool)));

	//开启矩形高度筛选
	connect(ui->checkBox_rectangleHight, SIGNAL(clicked(bool)), this, SLOT(slotGetRectangleMaxHightIsChecked(bool)));
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
	//setAttribute(Qt::WA_DeleteOnClose);
}

//析构函数
CMvImageDefect::~CMvImageDefect()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_pImageSourceMenu)
	{
		for (int index = 0; index < m_pImageSourceMenu->actions().size(); index++)
		{
			delete m_pImageSourceMenu->actions()[0]->menu();
		}
		delete m_pImageSourceMenu;
		m_pImageSourceMenu = nullptr;
	}

	if (m_pROISourceMenu)
	{
		int roiMenuSize = m_pROISourceMenu->actions().size();
		for (int index = 0; index < roiMenuSize; ++index)
		{
			qDebug()<< m_pROISourceMenu->actions()[0]->menu()->title();
			delete m_pROISourceMenu->actions()[0]->menu();
		}
		delete m_pROISourceMenu;
		m_pROISourceMenu = nullptr;
	}

	if (m_pROIPositionUpdatingMenu)
	{
		for (int index = 0; index < m_pROIPositionUpdatingMenu->actions().size(); index++)
		{
			delete m_pROIPositionUpdatingMenu->actions()[0]->menu();
		}
		delete m_pROIPositionUpdatingMenu;
		m_pROIPositionUpdatingMenu = nullptr;
	}

	if (m_pMaskSourceMenu)
	{
		for (int index = 0; index < m_pMaskSourceMenu->actions().size(); index++)
		{
			delete m_pMaskSourceMenu->actions()[0]->menu();
		}
		delete m_pMaskSourceMenu;
		m_pMaskSourceMenu = nullptr;
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
CMvImageDefect* CMvImageDefect::Instance()
{
	if (s_pCMvImageDefect == nullptr) {
		s_pCMvImageDefect = new CMvImageDefect;
	}
	return s_pCMvImageDefect;
}


//释放内存
void CMvImageDefect::destroy()
{
	if (s_pCMvImageDefect)
	{
		delete s_pCMvImageDefect;
		s_pCMvImageDefect = nullptr;
	}//if (s_pCMvImageDefect)
}

//初始化数据
void CMvImageDefect::initCMvImageDefect()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//设置ROI来源
	ui->comboBox_imageSource->setCurrentIndex(0);
	ui->checkBox_roiCreat->setChecked(true);

	//设置缺陷类型
	ui->comboBox_defectType->setCurrentIndex(0);

	//设置灰度上限
	ui->spinBox_grayLevelMax->setValue(0);

	//设置灰度下限
	ui->spinBox_grayLevelMin->setValue(0);

	//设置面积上限
	ui->doubleSpinBox_areaMax->setValue(0);

	//设置面积下限
	ui->doubleSpinBox_areaMin->setValue(0);

	//设置最小矩形宽度上限
	ui->doubleSpinBox_rectangleMaxWidth->setValue(0);

	//设置最小矩形宽度下限
	ui->doubleSpinBox_rectangleMinWidth->setValue(0);

	//设置最小矩形高度上限
	ui->doubleSpinBox_rectangleMaxHight->setValue(0);

	//设置最小矩形高度下限
	ui->doubleSpinBox_rectangleMinHight->setValue(0);

	//设置面积筛选中
	ui->checkBox_area->setChecked(false);
	ui->groupBox_area->setEnabled(false);

	//设置斜矩形宽度筛选选中
	ui->checkBox_rectangleWidth->setChecked(false);
	ui->groupBox_rectangleWidth->setEnabled(false);

	//设置斜矩形高度筛选选中
	ui->checkBox_rectangleHight->setChecked(false);
	ui->groupBox_rectangleHight->setEnabled(false);

	//设置掩膜
	ui->comboBox_dEtectionMask->setCurrentIndex(0);
	ui->comboBox_editMode->setCurrentIndex(0);
	ui->spinBox_lightTime->setValue(5);

	if (ui->comboBox_dEtectionMask->currentIndex() == 0){
		ui->widget_Mask->setEnabled(false);
	}else{
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
void CMvImageDefect::slotGetDetectorNameValue()
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
void CMvImageDefect::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvImageDefect::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMvImageDefect::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvImageDefect::initMenu()
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

void CMvImageDefect::initMenuByTest()
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
void CMvImageDefect::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1)
	{
		switch (row)
		{
		case 0:
			m_pImageSourceMenu->move(cursor().pos());
			m_pImageSourceMenu->show();

			qDebug() << "image source menu " << m_pImageSourceMenu->isEmpty();

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
void CMvImageDefect::soltMenuTriggered(QAction* action)
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
//点击编辑模板
void CMvImageDefect::slotGetEditTemplateIsClick()
{
	qDebug() << "点击编辑模板";
}

//点击显示差异图像
void CMvImageDefect::slotGetImageDifferencesIsClick()
{
	qDebug() << "点击显示差异图像";
}

//点击显示缺陷信息
void CMvImageDefect::slotGetDefectiveInformationIsClick()
{
	qDebug() << "点击显示缺陷信息";
}

//获取缺陷类型 数值
void CMvImageDefect::slotGetDefectTypeValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取缺陷类型" << ui->comboBox_defectType->itemText(index);
	}
}

//获取灰度上限
void CMvImageDefect::slotGetGrayLevelMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度上限" << value;
	}
}

//获取灰度下限
void CMvImageDefect::slotGetGrayLevelMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度下限" << value;
	}
}

//获取面积上限
void CMvImageDefect::slotGetAreaMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积上限" << value;
	}
}

//获取面积下限
void CMvImageDefect::slotGetAreaMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积下限" << value;
	}
}

//获取最小矩形宽度上限
void CMvImageDefect::slotGetRectangleMaxWidthValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形宽度上限" << value;
	}
}

//获取最小矩形宽度下限
void CMvImageDefect::slotGetRectangleMinWidthValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形宽度下限" << value;
	}
}

//获取最小矩形高度上限
void CMvImageDefect::slotGetRectangleMaxHightValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形高度上限" << value;
	}
}

//获取最小矩形高度下限
void CMvImageDefect::slotGetRectangleMinHightValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形高度下限" << value;
	}
}

//开启面积筛选
void CMvImageDefect::slotGetAreaMinIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启面积筛选" << state;
		ui->groupBox_area->setEnabled(state);
	}
}


//开启矩形宽度筛选
void CMvImageDefect::slotGetRectangleMaxWidthIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启矩形宽度筛选" << state;
		ui->groupBox_rectangleWidth->setEnabled(state);
	}
}

//开启矩形高度筛选
void CMvImageDefect::slotGetRectangleMaxHightIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启矩形高度筛选" << state;
		ui->groupBox_rectangleHight->setEnabled(state);
	}
}

/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值
void CMvImageDefect::slotMaskOfDetectionAreaValue(int Index)
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
void CMvImageDefect::slotEditModeValue(int Index)
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
void CMvImageDefect::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvImageDefect::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvImageDefect::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvImageDefect::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvImageDefect::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvImageDefect::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();

		ui->label_lineWidth->setEnabled(State);
		ui->spinBox_lineWidth->setEnabled(State);
		ui->comboBox_lineColour->setEnabled(State);
		ui->label_lineColour->setEnabled(State);
	}
}

//获取线条颜色 数值
void CMvImageDefect::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}


/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvImageDefect::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvImageDefect::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvImageDefect::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvImageDefect::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvImageDefect::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvImageDefect::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvImageDefect::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
