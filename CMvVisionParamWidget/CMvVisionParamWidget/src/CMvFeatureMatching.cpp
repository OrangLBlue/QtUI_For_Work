#include "CMvFeatureMatching.h"
#include "ui_CMvFeatureMatching.h"
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

CMvFeatureMatching* CMvFeatureMatching::s_pCMvFeatureMatching = nullptr;

CMvFeatureMatching::CMvFeatureMatching(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvFeatureMatching)
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
	initCMvFeatureMatching();

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
	//点击编辑轮廓
	connect(ui->pushButton_editingContours, SIGNAL(clicked()), this, SLOT(slotGetEditingContoursIsClick()));

	//点击锁
	connect(ui->pushButton_lock, SIGNAL(clicked()), this, SLOT(slotGetLockIsClick()));

	//获取检测模式 数值
	connect(ui->comboBox_detectionMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetDetectionModeValue(int)));

	//获取边缘阈值
	connect(ui->comboBox_thresholdType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetEdgeThresholdtValue(int)));

	//获取边缘梯度阈值 数值
	connect(ui->spinBox_threshold, SIGNAL(valueChanged(int)), this, SLOT(slotGetEdgeGradientThresholdtValue(int)));

	//获取边缘极性检测方式 数值
	connect(ui->comboBox_edgePolarity, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetEdgePolarityValue(int)));

	//获取检测尺度 数值
	connect(ui->doubleSpinBox_detectionScale, SIGNAL(valueChanged(double)), this, SLOT(slotGetDetectionScaleValue(double)));

	//获取定位尺度
	connect(ui->comboBox_positioningScales, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetPositioningScalesValue(int)));

	//获取尺度参数 数值
	connect(ui->doubleSpinBox_scaleParameter, SIGNAL(valueChanged(double)), this, SLOT(slotGetScaleParameterValue(double)));

	//获取滤波尺寸 数值
	connect(ui->comboBox_filterSize, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetFilterSizeValue(int)));

	//获取相邻目标最小距离 数值
	connect(ui->spinBox_minimumRange, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumRangeValue(int)));

	//获取最小匹配度 数值
	connect(ui->doubleSpinBox_minimumMatching, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinimumMatchingValue(double)));

	//获取最小角度 数值
	connect(ui->doubleSpinBox_minimumAngle, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinimumAngleValue(double)));

	//获取最大角度 数值
	connect(ui->doubleSpinBox_maximumAngle, SIGNAL(valueChanged(double)), this, SLOT(slotGetMaximumAngleValue(double)));

	//获取比例下限 数值
	connect(ui->doubleSpinBox_maxScale, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinScaleValue(double)));

	//获取比例上限 数值
	connect(ui->doubleSpinBox_minScale, SIGNAL(valueChanged(double)), this, SLOT(slotGetMaxScaleValue(double)));

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
CMvFeatureMatching::~CMvFeatureMatching()
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
CMvFeatureMatching* CMvFeatureMatching::Instance()
{
	if (s_pCMvFeatureMatching == nullptr) {
		s_pCMvFeatureMatching = new CMvFeatureMatching;
	}
	return s_pCMvFeatureMatching;
}


//释放内存
void CMvFeatureMatching::destroy()
{
	if (s_pCMvFeatureMatching)
	{
		delete s_pCMvFeatureMatching;
		s_pCMvFeatureMatching = nullptr;
	}//if (s_pCMvFeatureMatching)
}

//初始化数据
void CMvFeatureMatching::initCMvFeatureMatching()
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

	//设置检测模式
	ui->comboBox_detectionMode->setCurrentIndex(0);

	//设置阈值方式
	ui->comboBox_thresholdType->setCurrentIndex(0);

	//设置边缘点提取阈值
	ui->spinBox_threshold->setValue(5);
	if (ui->comboBox_thresholdType->currentIndex() == 0){
		ui->label_threshold->setEnabled(false);
		ui->spinBox_threshold->setEnabled(false);
	}else {
		ui->label_threshold->setEnabled(true);
		ui->spinBox_threshold->setEnabled(true);
	}

	//检测尺度
	ui->doubleSpinBox_detectionScale->setValue(5);

	//设置定位尺度
	ui->comboBox_positioningScales->setCurrentIndex(0);

	//设置尺度参数
	ui->doubleSpinBox_scaleParameter->setValue(5);
	if (ui->comboBox_positioningScales->currentIndex() == 0) {
		ui->label_scaleParameter->setEnabled(false);
		ui->doubleSpinBox_scaleParameter->setEnabled(false);
	}
	else {
		ui->label_scaleParameter->setEnabled(true);
		ui->doubleSpinBox_scaleParameter->setEnabled(true);
	}
	
	//获取边缘极性检测方式 数值
	ui->comboBox_edgePolarity->setCurrentIndex(0);

	//获取滤波尺寸 数值
	ui->comboBox_filterSize->setCurrentIndex(0);

	//获取相邻目标最小距离 数值
	ui->spinBox_minimumRange->setValue(5);

	//获取最小匹配度 数值
	ui->doubleSpinBox_minimumMatching->setValue(0.1);

	//获取最小角度 数值
	ui->doubleSpinBox_minimumAngle->setValue(5);

	//获取最大角度 数值
	ui->doubleSpinBox_maximumAngle->setValue(5);

	//获取比例下限 数值
	ui->doubleSpinBox_minScale->setValue(1);

	//获取比例上限 数值
	ui->doubleSpinBox_maxScale->setValue(1);


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
void CMvFeatureMatching::slotGetDetectorNameValue()
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
void CMvFeatureMatching::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvFeatureMatching::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMvFeatureMatching::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvFeatureMatching::initMenu()
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

void CMvFeatureMatching::initMenuByTest()
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
void CMvFeatureMatching::slotClickPushButton(int row, int col)
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
void CMvFeatureMatching::soltMenuTriggered(QAction* action)
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
//点击编辑轮廓
void CMvFeatureMatching::slotGetEditingContoursIsClick()
{
	qDebug() << "点击编辑轮廓";
}

//点击锁
void CMvFeatureMatching::slotGetLockIsClick()
{
	qDebug() << "点击锁";
}


//获取检测模式数值
void CMvFeatureMatching::slotGetDetectionModeValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取检测模式数值" << ui->comboBox_detectionMode->itemText(index);
	}
}

//获取边缘阈值
void CMvFeatureMatching::slotGetEdgeThresholdtValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘阈值" << ui->comboBox_thresholdType->itemText(index);

		if (index == 1) {
			ui->label_threshold->setEnabled(true);
			ui->spinBox_threshold->setEnabled(true);
		}
		else if (index == 0) {
			ui->label_threshold->setEnabled(false);
			ui->spinBox_threshold->setEnabled(false);//如果是手动阈值，则显示边缘梯度阈值-数值
		}
	}
}

//获取边缘梯度阈值 数值
void CMvFeatureMatching::slotGetEdgeGradientThresholdtValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘梯度阈值" << ui->spinBox_threshold->value() << "  " << Value;
	}
}

//获取检测尺度 数值
void CMvFeatureMatching::slotGetDetectionScaleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取检测尺度" << ui->doubleSpinBox_detectionScale->value() << "  " << Value;
	}
}


//获取定位尺度
void CMvFeatureMatching::slotGetPositioningScalesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取定位尺度" << ui->comboBox_positioningScales->itemText(index);

		if (index == 1) {
			ui->label_scaleParameter->setEnabled(true);
			ui->doubleSpinBox_scaleParameter->setEnabled(true);
		}
		else if (index == 0) {
			ui->label_scaleParameter->setEnabled(false);
			ui->doubleSpinBox_scaleParameter->setEnabled(false);//如果是手动阈值，则显示边缘梯度阈值-数值
		}
	}
}

//获取尺度参数 数值
void CMvFeatureMatching::slotGetScaleParameterValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取尺度参数" << ui->doubleSpinBox_scaleParameter->value() << "  " << Value;
	}
}


//获取边缘极性检测方式 数值
void CMvFeatureMatching::slotGetEdgePolarityValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘极性检测方式" << ui->comboBox_edgePolarity->itemText(index);
	}
}

//获取滤波尺寸 数值
void CMvFeatureMatching::slotGetFilterSizeValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取滤波尺寸" << ui->comboBox_filterSize->itemText(index);
	}
}

//获取相邻目标最小距离 数值
void CMvFeatureMatching::slotGetMinimumRangeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取相邻目标最小距离" << ui->spinBox_minimumRange->value() << "  " << Value;
	}
}

//获取最小匹配度 数值
void CMvFeatureMatching::slotGetMinimumMatchingValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小匹配度" << ui->doubleSpinBox_minimumMatching->value() << "  " << Value;
	}
}

//获取最小角度 数值
void CMvFeatureMatching::slotGetMinimumAngleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小角度" << ui->doubleSpinBox_minimumAngle->value() << " " << Value;
	}
}

//获取最大角度 数值
void CMvFeatureMatching::slotGetMaximumAngleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取最大角度" << ui->doubleSpinBox_maximumAngle->value() << " " << Value;
	}
}

//获取比例下限 数值
void CMvFeatureMatching::slotGetMinScaleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取比例下限" << ui->doubleSpinBox_minScale->value() << " " << Value;
	}
}

//获取比例上限 数值
void CMvFeatureMatching::slotGetMaxScaleValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取比例上限" << ui->doubleSpinBox_maxScale->value() << " " << Value;
	}
}


/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值
void CMvFeatureMatching::slotMaskOfDetectionAreaValue(int Index)
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
void CMvFeatureMatching::slotEditModeValue(int Index)
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
void CMvFeatureMatching::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvFeatureMatching::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvFeatureMatching::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvFeatureMatching::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvFeatureMatching::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvFeatureMatching::slotGetStartUpDrawingValue(bool State)
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
void CMvFeatureMatching::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}


/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvFeatureMatching::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvFeatureMatching::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvFeatureMatching::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvFeatureMatching::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvFeatureMatching::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvFeatureMatching::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvFeatureMatching::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
