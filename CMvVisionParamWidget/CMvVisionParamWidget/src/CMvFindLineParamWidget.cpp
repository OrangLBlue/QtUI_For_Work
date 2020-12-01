#include <QDebug>
#include "CMvFindLineParamWidget.h"
#include "ui_CMvFindLineParamWidget.h"
#include <QTableWidgetItem>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvFindLineParamWidget * CMvFindLineParamWidget::s_pFindLineParamWidget = nullptr;

CMvFindLineParamWidget::CMvFindLineParamWidget(QWidget *parent)
	: QWidget(parent),
      ui(new Ui::CMvFindLineParamWidget)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_maskCount = 0;
	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/
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
	connect(ui->comboBox_imageSource_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetROISourcesValue(int)));

	//获取自己创建选中信息
	connect(ui->checkBox_roiCreat, SIGNAL(clicked(bool)), this, SLOT(slotGetCreateYourselfValue(bool)));


	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取边缘阈值
	connect(ui->comboBox_thresholdType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetEdgeThresholdtValue(int)));

	//获取边缘梯度阈值 数值
	connect(ui->spinBox_threshold, SIGNAL(valueChanged(int)), this, SLOT(slotGetEdgeGradientThresholdtValue(int)));

	//获取扫描点数 数值
	connect(ui->spinBox_scanPointSum, SIGNAL(valueChanged(int)), this, SLOT(slotGetScanPointsValue(int)));

	//获取抽样点数 数值
	connect(ui->spinBox_samplingPointSum, SIGNAL(valueChanged(int)), this, SLOT(slotGetSamplingPointsValue(int)));

	//获取扫描方向
	connect(ui->comboBox_scanDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetDirectionOfDetectionValue(int)));

	//获取边缘极性检测方式
	connect(ui->comboBox_edgeCheckType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetCoordinateInputValue(int)));

	//获取拟合范围 数值
	connect(ui->spinBox_fitRange, SIGNAL(valueChanged(int)), this, SLOT(slotGetScopeOfFitValue(int)));


	/*===============================================================================================*\
	**====================================结果判断信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取拟合误差限制 数值
	connect(ui->spinBox_fitBias, SIGNAL(valueChanged(int)), this, SLOT(slotGetFittingErrorlimitsValue(int)));

	//获取最小直线长度 数值
	connect(ui->spinBox_minLineLong, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumLineLengthValue(int)));

	//获取最大直线长度 数值
	connect(ui->spinBox_maxLineLong, SIGNAL(valueChanged(int)), this, SLOT(slotGetMaximumLineLengthValue(int)));


	/*===============================================================================================*\
	**====================================掩膜设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取检测区域的掩膜
	connect(ui->comboBox_lightOutputIo_5, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMaskOfDetectionAreaValue(int)));
	
	//获取编辑方式
	connect(ui->comboBox_lightOutputIo_6, SIGNAL(activated(int)), this, SLOT(slotEditModeValue(int)));

	//获取画笔尺寸 
	connect(ui->spinBox_lightTime_2, SIGNAL(valueChanged(int)), this, SLOT(slotBrushSizeValue(int)));

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
	connect(ui->spinBox_lightTime_3, SIGNAL(valueChanged(int)), this, SLOT(slotGetLineWidthValue(int)));

	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig_3, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//获取线条颜色
	connect(ui->comboBox_lightOutputIo_10, SIGNAL(activated(int)), this, SLOT(slotGetLineColourValue(int)));


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
	connect(ui->pushButton_ensure, SIGNAL(clicked()), this, SLOT(slotMakeSureIsClick()));

	//点击 取消
	connect(ui->pbPrev_cancel, SIGNAL(clicked()), this, SLOT(slotCancelIsClick()));

	//设置关闭窗体时释放资源
	setAttribute(Qt::WA_DeleteOnClose);
}

CMvFindLineParamWidget::~CMvFindLineParamWidget()
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
			qDebug() << m_pROISourceMenu->actions()[0]->menu()->title();
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

//单实例化
CMvFindLineParamWidget* CMvFindLineParamWidget::Instance()
{
	if (s_pFindLineParamWidget == nullptr)
	{
		s_pFindLineParamWidget = new CMvFindLineParamWidget;
	}
	return s_pFindLineParamWidget;
}

//释放内存
void CMvFindLineParamWidget::destroy()
{
	if (s_pFindLineParamWidget)
	{
		delete s_pFindLineParamWidget;
		s_pFindLineParamWidget = nullptr;
	}//if (c_pUniqueShowMessage)
}


void CMvFindLineParamWidget::testInit()
{
	m_signalEnable = false;
	ui->comboBox_imageSource_2->setCurrentIndex(2);
	m_signalEnable = true;
}


/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvFindLineParamWidget::slotGetDetectorNameValue()
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
void CMvFindLineParamWidget::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvFindLineParamWidget::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource_2->itemText(index);
	}
}

//获取自己创建选中信息
void CMvFindLineParamWidget::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}


/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
//初始化二级菜单
void CMvFindLineParamWidget::initMenu()
{
	//初始化图片来源菜单
	//m_pImageSourceMenu = m_pSecondLevelMenu->initMenu(m_allImageSourceMenuData, ui->tableWidget_input);

	//初始化ROI来源菜单
	//m_pROISourceMenu = m_pSecondLevelMenu->initSecondLevelMenu(m_allROISourceMenuData, ui->tableWidget_input);
	
	//初始化ROI位置修正菜单
	//m_pROIPositionUpdatingMenu = m_pSecondLevelMenu->initSecondLevelMenu(m_allROIPositionUpdatingMenuData, ui->tableWidget_input);
	
	//初始化掩膜来源菜单
	//m_pMaskSourceMenu = m_pSecondLevelMenu->initSecondLevelMenu(m_allMaskSourceMenuData, ui->tableWidget_input);
}

void CMvFindLineParamWidget::initMenuByTest()
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
void CMvFindLineParamWidget::slotClickPushButton(int row, int col)
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
void CMvFindLineParamWidget::soltMenuTriggered(QAction* action)
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
//获取边缘阈值
void CMvFindLineParamWidget::slotGetEdgeThresholdtValue(int index)
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
void CMvFindLineParamWidget::slotGetEdgeGradientThresholdtValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘梯度阈值" << ui->spinBox_threshold->value() << "  " << Value;
	}
}

//获取边缘极性检测方式 数值
void CMvFindLineParamWidget::slotGetCoordinateInputValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘极性检测方式" << ui->comboBox_edgeCheckType->itemText(index);
	}
}

//获取扫描点数 数值
void CMvFindLineParamWidget::slotGetScanPointsValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取扫描点数" << ui->spinBox_scanPointSum->value() << "  " << Value;
	}
}

//获取抽样点数 数值
void CMvFindLineParamWidget::slotGetSamplingPointsValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取抽样点数" << ui->spinBox_samplingPointSum->value() << "  " << Value;
	}
}

//获取扫描方向 数值
void CMvFindLineParamWidget::slotGetDirectionOfDetectionValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取扫描方向" << ui->comboBox_scanDirection->itemText(index);
	}
}

//获取拟合范围 数值
void CMvFindLineParamWidget::slotGetScopeOfFitValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取拟合范围" << ui->spinBox_fitRange->value() << " " << Value;
		//ui->label_10->setText(QStringLiteral("拟合范围: ") + ui->doubleSpinBox->text().sprintf("%g", ui->doubleSpinBox->text().toFloat()));
	}
}


/*===============================================================================================*\
**=======================================结果判断槽函数==========================================**
\*===============================================================================================*/
//获取拟合误差限制 数值
void CMvFindLineParamWidget::slotGetFittingErrorlimitsValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取拟合最少点数" << ui->spinBox_fitBias->text() << ui->spinBox_fitBias->value() << " " << Value;
	}
}

//获取最小直线长度 数值
void CMvFindLineParamWidget::slotGetMinimumLineLengthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小直线长度" << ui->spinBox_minLineLong->text() << ui->spinBox_minLineLong->value() << " " << Value;
	}
}

//获取最大直线长度 数值
void CMvFindLineParamWidget::slotGetMaximumLineLengthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取最大直线长度" << ui->spinBox_maxLineLong->text() << ui->spinBox_maxLineLong->value() << " " << Value;
	}
}


/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值
void CMvFindLineParamWidget::slotMaskOfDetectionAreaValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取检测区域的掩膜" << ui->comboBox_lightOutputIo_5->itemText(Index) << " " << Index;

		if (Index == 0) {
			ui->widget_3->setEnabled(false);
		}
		else {
			ui->widget_3->setEnabled(true);
		}
	}
}

//获取编辑方式 数值
void CMvFindLineParamWidget::slotEditModeValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取编辑方式" << ui->comboBox_lightOutputIo_6->itemText(Index) << " " << Index;

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
void CMvFindLineParamWidget::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime_2->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvFindLineParamWidget::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvFindLineParamWidget::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvFindLineParamWidget::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvFindLineParamWidget::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lightTime_3->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvFindLineParamWidget::slotGetStartUpDrawingValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig_3->isChecked();
		if (state) {
			ui->spinBox_lightTime_3->setEnabled(true);
			ui->comboBox_lightOutputIo_10->setEnabled(true);
			ui->label_lightOutputIo_17->setEnabled(true);
			ui->label_lightOutputIo_18->setEnabled(true);
		}
		else {
			ui->spinBox_lightTime_3->setEnabled(false);
			ui->comboBox_lightOutputIo_10->setEnabled(false);
			ui->label_lightOutputIo_17->setEnabled(false);
			ui->label_lightOutputIo_18->setEnabled(false);
		}
	}
}

//获取线条颜色 数值
void CMvFindLineParamWidget::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lightOutputIo_10->itemText(Index);
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvFindLineParamWidget::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
	//pushButton_zoomIn
}

//点击 缩小
void CMvFindLineParamWidget::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
	//pushButton_zoomOut
}

//点击 最好尺寸
void CMvFindLineParamWidget::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
	//pushButton_zoomBest
}

//点击 锁定ROI
void CMvFindLineParamWidget::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
	//pushButton_lockRoiMove
}

//点击 单次
void CMvFindLineParamWidget::slotOnceIsClick()
{
	qDebug() << "单次被点了";
	//pushButton_ones
}

//点击 确定
void CMvFindLineParamWidget::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
	//pushButton_ensure
}

//点击 取消
void CMvFindLineParamWidget::slotCancelIsClick()
{
	qDebug() << "取消被点了";
	//pbPrev_cancel
	testInit();
}
