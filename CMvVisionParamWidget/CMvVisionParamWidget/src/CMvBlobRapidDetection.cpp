#include "CMvFindRoundParamWidget.h"
#include "ui_CMvFindRoundParamWidget.h"
#include <QCheckBox>
#include <QDebug>
#include <QList>
#include <time.h>
#include <QTableWidgetItem>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvFindRoundParamWidget* CMvFindRoundParamWidget::s_pFindRoundParamWidget = nullptr;

CMvFindRoundParamWidget::CMvFindRoundParamWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvFindRoundParamWidget)
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
	connect(ui->plainTextEdit_funcName_2, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc_2 , SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	//点击ROI来源选择获取选项信息
	connect(ui->comboBox_imageSource_3, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetROISourcesValue(int)));

	//获取自己创建选中信息
	connect(ui->checkBox_roiCreat_2, SIGNAL(clicked(bool)), this, SLOT(slotGetCreateYourselfValue(bool)));


	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取边缘阈值
	connect(ui->comboBox_thresholdType_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetEdgeThresholdtValue(int)));

	//获取边缘梯度阈值 数值
	connect(ui->spinBox_threshold_2, SIGNAL(valueChanged(int)), this, SLOT(slotGetEdgeGradientThresholdtValue(int)));

	//获取扫描点数 数值
	connect(ui->spinBox_scanPointSum_2, SIGNAL(valueChanged(int)), this, SLOT(slotGetScanPointsValue(int)));

	//获取抽样点数 数值
	connect(ui->spinBox_samplingPointSum_2, SIGNAL(valueChanged(int)), this, SLOT(slotGetSamplingPointsValue(int)));

	//获取扫描方向
	connect(ui->comboBox_scanDirection_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetDirectionOfDetectionValue(int)));

	//获取边缘极性检测方式
	connect(ui->comboBox_edgeCheckType_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetCoordinateInputValue(int)));

	//获取拟合范围 数值
	connect(ui->spinBox_fitRange_2, SIGNAL(valueChanged(int)), this, SLOT(slotGetScopeOfFitValue(int)));


	/*===============================================================================================*\
	**====================================结果判断信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取拟合误差限制 数值
	connect(ui->spinBox_fitBias_2, SIGNAL(valueChanged(int)), this, SLOT(slotGetFittingErrorlimitsValue(int)));

	//获取半径下限 数值
	connect(ui->spinBox_minRoundRadius, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinRoundRadiusValue(int)));

	//获取半径上限 数值
	connect(ui->spinBox_maxRoundRadius, SIGNAL(valueChanged(int)), this, SLOT(slotGetMaxRoundRadiusValue(int)));

	//获取开启凹凸性检测选中信息
	connect(ui->checkBox_concaveConvex, SIGNAL(clicked(bool)), this, SLOT(slotGetConcaveConvexIsChecked(bool)));

	//获取最小深度 数值
	connect(ui->doubleSpinBox_minimumDepth, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinimumDepthValue(double)));

	//获取最小抽样点数 数值
	connect(ui->doubleSpinBox_minimumSamplingPoints, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinimumSamplingPointsValue(double)));

	//点击显示凹凸点信息
	connect(ui->pushButton_unqualifiedPiont, SIGNAL(clicked()), this, SLOT(slotGetUnqualifiedPiontIsClick()));


	/*===============================================================================================*\
	**====================================掩膜设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取检测区域的掩膜
	connect(ui->comboBox_dEtectionMask, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMaskOfDetectionAreaValue(int)));

	//获取编辑方式
	connect(ui->comboBox_lightOutputIo_7, SIGNAL(activated(int)), this, SLOT(slotEditModeValue(int)));

	//获取画笔尺寸 
	connect(ui->spinBox_lightTime_3, SIGNAL(valueChanged(int)), this, SLOT(slotBrushSizeValue(int)));

	//点击清空掩膜
	connect(ui->pushButton_maskNull_2, SIGNAL(clicked()), this, SLOT(slotEmptyMaskIsClick()));

	//点击掩盖所有
	connect(ui->pushButton_maskAll_2, SIGNAL(clicked()), this, SLOT(slotCoverUpEverythingClick()));

	//点击保存修改
	connect(ui->pushButton_saveMask_2, SIGNAL(clicked()), this, SLOT(slotSaveChangesClick()));


	/*===============================================================================================*\
	**====================================结果绘制信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取线条宽度 数值
	connect(ui->spinBox_lightTime_5, SIGNAL(valueChanged(int)), this, SLOT(slotGetLineWidthValue(int)));

	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig_4, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//获取线条颜色
	connect(ui->comboBox_lightOutputIo_11, SIGNAL(activated(int)), this, SLOT(slotGetLineColourValue(int)));


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
	setAttribute(Qt::WA_DeleteOnClose);
}


//析构函数
CMvFindRoundParamWidget::~CMvFindRoundParamWidget()
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
CMvFindRoundParamWidget* CMvFindRoundParamWidget::Instance()
{
	if (s_pFindRoundParamWidget == nullptr) {
		s_pFindRoundParamWidget = new CMvFindRoundParamWidget;
	}
	return s_pFindRoundParamWidget;
}


//释放内存
void CMvFindRoundParamWidget::destroy()
{
	if (s_pFindRoundParamWidget)
	{
		delete s_pFindRoundParamWidget;
		s_pFindRoundParamWidget = nullptr;
	}//if (c_pUniqueShowMessage)
}


/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvFindRoundParamWidget::slotGetDetectorNameValue()
{
	if (m_signalEnable) {
		QString strText = ui->plainTextEdit_funcName_2->toPlainText();
		int nLength = strText.length();
		for (int index = 0; index < nLength; index++)
		{
			if (strText[index] == '\n') {
				ui->plainTextEdit_funcName_2->blockSignals(true);
				strText.remove("\n");
				qDebug() << "获取检测器名称" << strText;
				ui->plainTextEdit_funcName_2->setPlainText(strText);
				ui->plainTextEdit_funcName_2->blockSignals(false);
			}
		}
	}
}

//获取启用检测器选中信息
void CMvFindRoundParamWidget::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc_2->isChecked();
	}
}

//获取ROI来源
void CMvFindRoundParamWidget::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource_3->itemText(index);
	}
}

//获取自己创建选中信息
void CMvFindRoundParamWidget::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat_2->isChecked();
	}
}


/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvFindRoundParamWidget::initMenu()
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

void CMvFindRoundParamWidget::initMenuByTest()
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
void CMvFindRoundParamWidget::slotClickPushButton(int row, int col)
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
void CMvFindRoundParamWidget::soltMenuTriggered(QAction* action)
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
void CMvFindRoundParamWidget::slotGetEdgeThresholdtValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘阈值" << ui->comboBox_thresholdType_2->itemText(index);

		if (index == 1) {
			ui->label_threshold_2->setEnabled(true);
			ui->spinBox_threshold_2->setEnabled(true);
		}
		else if (index == 0) {
			ui->label_threshold_2->setEnabled(false);
			ui->spinBox_threshold_2->setEnabled(false);//如果是手动阈值，则显示边缘梯度阈值-数值
		}
	}
}

//获取边缘梯度阈值 数值
void CMvFindRoundParamWidget::slotGetEdgeGradientThresholdtValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘梯度阈值" << ui->spinBox_threshold_2->value() << "  " << Value;
	}
}

//获取边缘极性检测方式 数值
void CMvFindRoundParamWidget::slotGetCoordinateInputValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取边缘极性检测方式" << ui->comboBox_edgeCheckType_2->itemText(index);
	}
}

//获取扫描点数 数值
void CMvFindRoundParamWidget::slotGetScanPointsValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取扫描点数" << ui->spinBox_scanPointSum_2->value() << "  " << Value;
	}
}

//获取抽样点数 数值
void CMvFindRoundParamWidget::slotGetSamplingPointsValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取抽样点数" << ui->spinBox_samplingPointSum_2->value() << "  " << Value;
	}
}

//获取扫描方向 数值
void CMvFindRoundParamWidget::slotGetDirectionOfDetectionValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取扫描方向" << ui->comboBox_scanDirection_2->itemText(index);
	}
}

//获取拟合范围 数值
void CMvFindRoundParamWidget::slotGetScopeOfFitValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取拟合范围" << ui->spinBox_fitRange_2->value() << " " << Value;
		//ui->label_10->setText(QStringLiteral("拟合范围: ") + ui->doubleSpinBox->text().sprintf("%g", ui->doubleSpinBox->text().toFloat()));
	}
}


/*===============================================================================================*\
**=======================================结果判断槽函数==========================================**
\*===============================================================================================*/
//获取拟合误差限制 数值
void CMvFindRoundParamWidget::slotGetFittingErrorlimitsValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取拟合最少点数" << ui->spinBox_fitBias_2->text() << ui->spinBox_fitBias_2->value() << " " << Value;
	}
}

//获取半径下限 数值
void CMvFindRoundParamWidget::slotGetMinRoundRadiusValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取半径下限" << ui->spinBox_minRoundRadius->text() << ui->spinBox_minRoundRadius->value() << " " << Value;
	}
}

//获取半径上限 数值
void CMvFindRoundParamWidget::slotGetMaxRoundRadiusValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取半径上限" << ui->spinBox_maxRoundRadius->text() << ui->spinBox_maxRoundRadius->value() << " " << Value;
	}
}

//获取开启凹凸性检测选中信息
void CMvFindRoundParamWidget::slotGetConcaveConvexIsChecked(bool State)
{
	qDebug() << "获取开启凹凸性检测选中信息" << State << " " << ui->checkBox_concaveConvex->isChecked();
	
	ui->widget_concaveConvex->setEnabled(State);
}

//获取最小深度 数值
void CMvFindRoundParamWidget::slotGetMinimumDepthValue(double Value)
{
	qDebug() << "获取最小深度" << Value << " " << ui->doubleSpinBox_minimumDepth->value();
}

//获取最小抽样点数 数值
void CMvFindRoundParamWidget::slotGetMinimumSamplingPointsValue(double Value)
{
	qDebug() << "获取最小抽样点数" << Value << " " << ui->doubleSpinBox_minimumSamplingPoints->value();
}

//点击显示凹凸点信息
void CMvFindRoundParamWidget::slotGetUnqualifiedPiontIsClick()
{
	qDebug() << "点击显示凹凸点信息" ;
}


/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值
void CMvFindRoundParamWidget::slotMaskOfDetectionAreaValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取检测区域的掩膜" << ui->comboBox_dEtectionMask->itemText(Index) << " " << Index;

		if (Index == 0) {
			ui->widget_3->setEnabled(false);
		}
		else {
			ui->widget_3->setEnabled(true);
		}
	}
}

//获取编辑方式 数值
void CMvFindRoundParamWidget::slotEditModeValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取编辑方式" << ui->comboBox_lightOutputIo_7->itemText(Index) << " " << Index;

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
			ui->pushButton_maskNull_2->setEnabled(false);
		}
		else {
			ui->pushButton_maskNull_2->setEnabled(true);
		}
	}
}

//获取画笔尺寸 数值
void CMvFindRoundParamWidget::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime_3->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvFindRoundParamWidget::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull_2->setEnabled(false);
	}
}

//点击掩盖所有
void CMvFindRoundParamWidget::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvFindRoundParamWidget::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvFindRoundParamWidget::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lightTime_5->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvFindRoundParamWidget::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig_4->isChecked();

		ui->spinBox_lightTime_5->setEnabled(State);
		ui->label_lightOutputIo_20->setEnabled(State);
		ui->label_lightOutputIo_19->setEnabled(State);
		ui->comboBox_lightOutputIo_11->setEnabled(State);
	}
}

//获取线条颜色 数值
void CMvFindRoundParamWidget::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lightOutputIo_11->itemText(Index);
	}
}


/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvFindRoundParamWidget::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvFindRoundParamWidget::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvFindRoundParamWidget::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvFindRoundParamWidget::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvFindRoundParamWidget::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvFindRoundParamWidget::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvFindRoundParamWidget::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
