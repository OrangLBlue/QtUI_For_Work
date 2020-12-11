#include "CMvContactAttitudeDefect.h"
#include "ui_CMvContactAttitudeDefect.h"
#include <QCheckBox>
#include <QDebug>
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


CMvContactAttitudeDefect* CMvContactAttitudeDefect::s_pCMvContactAttitudeDefect = nullptr;

CMvContactAttitudeDefect::CMvContactAttitudeDefect(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvContactAttitudeDefect)
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
	initCMvContactAttitudeDefect();

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
	//选择二值化类型
	connect(ui->comboBox_binaryDetection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeBinaryDetection(int)));

	//获取灰度阈值
	connect(ui->spinBox_grayLevel, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelValue(int)));

	//开启开启灰尘检测
	connect(ui->checkBox_dust, SIGNAL(clicked(bool)), this, SLOT(slotGetDustIsChecked(bool)));

	//获取载片灰度上限
	connect(ui->spinBox_grayLevelMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelMaxValue(int)));

	//获取载片灰度下限
	connect(ui->spinBox_grayLevelMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelMinValue(int)));

	//获取灰尘梯度上限
	connect(ui->spinBox_dustMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetDustMaxValue(int)));

	//获取灰尘梯度下限
	connect(ui->spinBox_dustMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetDustMinValue(int)));

	//获取查找范围
	connect(ui->spinBox_seekScope, SIGNAL(valueChanged(int)), this, SLOT(slotGetSeekScopeValue(int)));

	//获取灰尘最少点数
	connect(ui->spinBox_MinimumPointsNumber, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumPointsNumberValue(int)));

	//开启杂点剔除参数
	connect(ui->checkBox_miscellaneous, SIGNAL(clicked(bool)), this, SLOT(slotGetMiscellaneousIsChecked(bool)));

	//获取杂点面积上限
	connect(ui->doubleSpinBox_areaMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetAreaMaxValue(double)));

	//获取杂点面积下限
	connect(ui->doubleSpinBox_areaMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetAreaMinValue(double)));

	//点击显示杂点信息
	connect(ui->pushButton_miscellaneousInformation, SIGNAL(clicked()), this, SLOT(slotGetMiscellaneousInformationIsClicked()));

	//开启触点面积限定
	connect(ui->checkBox_contactArea, SIGNAL(clicked(bool)), this, SLOT(slotGetContactAreaIsChecked(bool)));

	//获取触点面积上限
	connect(ui->doubleSpinBox_contactAreaMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetContactAreaMaxValue(double)));

	//获取触点面积下限
	connect(ui->doubleSpinBox_contactAreaMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetContactAreaMinValue(double)));

	//获取触点宽度上限
	connect(ui->doubleSpinBox_widthMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetWidthMaxValue(double)));

	//获取触点宽度下限
	connect(ui->doubleSpinBox_widthMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetWidthMinValue(double)));

	//获取触点高度上限
	connect(ui->doubleSpinBox_hightMax, SIGNAL(valueChanged(double)), this, SLOT(slotGetHightMaxValue(double)));

	//获取触点高度下限
	connect(ui->doubleSpinBox_hightMin, SIGNAL(valueChanged(double)), this, SLOT(slotGetHightMinValue(double)));

	//点击显示面积信息
	connect(ui->pushButton_areaInformation, SIGNAL(clicked()), this, SLOT(slotGetAreaInformationIsClicked()));

	//获取偏移距离阈值
	connect(ui->doubleSpinBox_offsetDistance, SIGNAL(valueChanged(double)), this, SLOT(slotGetOffsetDistanceValue(double)));

	//获取缺失距离阈值
	connect(ui->doubleSpinBox_missingDistance, SIGNAL(valueChanged(double)), this, SLOT(slotGetMissingDistanceValue(double)));

	//获取偏移角度阈值
	connect(ui->doubleSpinBox_offsetAngle, SIGNAL(valueChanged(double)), this, SLOT(slotGetOffsetAngleValue(double)));

	//获取特征范围
	connect(ui->doubleSpinBox_characteristic, SIGNAL(valueChanged(double)), this, SLOT(slotGetCharacteristicValue(double)));

	//点击学习一次
	connect(ui->pushButton_study, SIGNAL(clicked()), this, SLOT(slotGetStudyIsClicked()));

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

	//绘制边缘轮廓
	connect(ui->checkBox_drawEdges, SIGNAL(clicked(bool)), this, SLOT(slotGetDrawEdgesValue(bool)));
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
CMvContactAttitudeDefect::~CMvContactAttitudeDefect()
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
CMvContactAttitudeDefect* CMvContactAttitudeDefect::Instance()
{
	if (s_pCMvContactAttitudeDefect == nullptr) {
		s_pCMvContactAttitudeDefect = new CMvContactAttitudeDefect;
	}
	return s_pCMvContactAttitudeDefect;
}


//释放内存
void CMvContactAttitudeDefect::destroy()
{
	if (s_pCMvContactAttitudeDefect)
	{
		delete s_pCMvContactAttitudeDefect;
		s_pCMvContactAttitudeDefect = nullptr;
	}//if (s_pCMvContactAttitudeDefect)
}

//初始化界面
void CMvContactAttitudeDefect::initCMvContactAttitudeDefect()
{
	m_signalEnable = false;
	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");

	//设置ROI来源
	ui->comboBox_imageSource->setCurrentIndex(0);

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

	//获取灰度阈值
	ui->spinBox_grayLevel->setValue(5);


	//开启开启灰尘检测
	ui->checkBox_dust->setChecked(false);
	ui->groupBox_dust->setEnabled(ui->checkBox_dust->isChecked());

	//获取载片灰度上限
	ui->spinBox_grayLevelMax->setValue(0);

	//获取载片灰度下限
	ui->spinBox_grayLevelMin->setValue(0);

	//获取灰尘梯度上限
	ui->spinBox_dustMax->setValue(0);

	//获取灰尘梯度下限
	ui->spinBox_dustMin->setValue(0);

	//获取查找范围
	ui->spinBox_seekScope->setValue(0);

	//获取灰尘最少点数
	ui->spinBox_MinimumPointsNumber->setValue(0);

	//开启杂点剔除参数
	ui->checkBox_miscellaneous->setChecked(false);
	ui->groupBox_miscellaneous->setEnabled(ui->checkBox_miscellaneous->isChecked());

	//获取杂点面积上限
	ui->doubleSpinBox_areaMax->setValue(0);

	//获取杂点面积下限
	ui->doubleSpinBox_areaMin->setValue(0);

	//开启触点面积限定
	ui->checkBox_contactArea->setChecked(false);
	ui->groupBox_contactArea->setEnabled(ui->checkBox_contactArea->isChecked());

	//获取触点面积上限
	ui->doubleSpinBox_contactAreaMax->setValue(0);

	//获取触点面积下限
	ui->doubleSpinBox_contactAreaMin->setValue(0);

	//获取触点宽度上限
	ui->doubleSpinBox_widthMax->setValue(0);

	//获取触点宽度下限
	ui->doubleSpinBox_widthMin->setValue(0);

	//获取触点高度上限
	ui->doubleSpinBox_hightMax->setValue(0);

	//获取触点高度下限
	ui->doubleSpinBox_hightMin->setValue(0);

	//获取偏移距离阈值
	ui->doubleSpinBox_offsetDistance->setValue(0);
	
	//获取缺失距离阈值
	ui->doubleSpinBox_missingDistance->setValue(0);

	//获取偏移角度阈值
	ui->doubleSpinBox_offsetAngle->setValue(0);

	//获取特征范围
	ui->doubleSpinBox_characteristic->setValue(0);


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

	ui->checkBox_drawEdges->setChecked(false);
	m_signalEnable = true;	
}

/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvContactAttitudeDefect::slotGetDetectorNameValue()
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
void CMvContactAttitudeDefect::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvContactAttitudeDefect::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMvContactAttitudeDefect::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}


/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvContactAttitudeDefect::initMenu()
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

void CMvContactAttitudeDefect::initMenuByTest()
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
void CMvContactAttitudeDefect::slotClickPushButton(int row, int col)
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
void CMvContactAttitudeDefect::soltMenuTriggered(QAction* action)
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
//选择二值化类型
void CMvContactAttitudeDefect::slotChangeBinaryDetection(int index)
{
	if (m_signalEnable) {
		qDebug() << "选择二值化类型" << ui->comboBox_binaryDetection->itemText(index) << " " << index;
		if (index < 2) {
			ui->label_grayLevel->setEnabled(true);
			ui->spinBox_grayLevel->setEnabled(true);
		}
		else {
			ui->label_grayLevel->setEnabled(false);
			ui->spinBox_grayLevel->setEnabled(false);
		}
	}
}

//获取灰度阈值
void CMvContactAttitudeDefect::slotGetGrayLevelValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度阈值" << value;
	}
}

//开启开启灰尘检测
void CMvContactAttitudeDefect::slotGetDustIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启开启灰尘检测" << state;
		ui->groupBox_dust->setEnabled(state);
	}
}

//获取载片灰度上限
void CMvContactAttitudeDefect::slotGetGrayLevelMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取载片灰度上限" << value;
	}
}

//获取载片灰度下限
void CMvContactAttitudeDefect::slotGetGrayLevelMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取载片灰度下限" << value;
	}
}

//获取灰尘梯度上限
void CMvContactAttitudeDefect::slotGetDustMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰尘梯度上限" << value;
	}
}

//获取灰尘梯度下限
void CMvContactAttitudeDefect::slotGetDustMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰尘梯度下限" << value;
	}
}

//获取查找范围
void CMvContactAttitudeDefect::slotGetSeekScopeValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取查找范围" << value; 
	}
}

//获取灰尘最少点数
void CMvContactAttitudeDefect::slotGetMinimumPointsNumberValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰尘最少点数" << value;
	}
}


//开启杂点剔除参数
void CMvContactAttitudeDefect::slotGetMiscellaneousIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启杂点剔除参数" << state;
		ui->groupBox_miscellaneous->setEnabled(state);
	}
}

//获取杂点面积上限
void CMvContactAttitudeDefect::slotGetAreaMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取杂点面积上限" << value;
	}
}

//获取杂点面积下限
void CMvContactAttitudeDefect::slotGetAreaMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取杂点面积下限" << value;
	}
}

//点击显示杂点信息
void CMvContactAttitudeDefect::slotGetMiscellaneousInformationIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击显示杂点信息";
	}
}

//开启触点面积限定
void CMvContactAttitudeDefect::slotGetContactAreaIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启触点面积限定" << state;
		ui->groupBox_contactArea->setEnabled(state);
	}
}

//获取触点面积上限
void CMvContactAttitudeDefect::slotGetContactAreaMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取触点面积上限" << value;
	}
}

//获取触点面积下限
void CMvContactAttitudeDefect::slotGetContactAreaMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取触点面积下限" << value;
	}
}

//获取触点宽度上限
void CMvContactAttitudeDefect::slotGetWidthMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取触点宽度上限" << value;
	}
}

//获取触点宽度下限
void CMvContactAttitudeDefect::slotGetWidthMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取触点宽度下限" << value;
	}
}

//获取触点高度上限
void CMvContactAttitudeDefect::slotGetHightMaxValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取触点高度上限" << value;
	}
}

//获取触点高度下限
void CMvContactAttitudeDefect::slotGetHightMinValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取触点高度下限" << value;
	}
}

//点击显示面积信息
void CMvContactAttitudeDefect::slotGetAreaInformationIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击显示面积信息";
	}
}

//获取偏移距离阈值
void CMvContactAttitudeDefect::slotGetOffsetDistanceValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取偏移距离阈值" << value;
	}
}

//获取缺失距离阈值
void CMvContactAttitudeDefect::slotGetMissingDistanceValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取缺失距离阈值" << value;
	}
}

//获取偏移角度阈值
void CMvContactAttitudeDefect::slotGetOffsetAngleValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取偏移角度阈值" << value;
	}
}

//获取特征范围
void CMvContactAttitudeDefect::slotGetCharacteristicValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取特征范围" << value;
	}
}

//点击学习一次
void CMvContactAttitudeDefect::slotGetStudyIsClicked()
{
	if (m_signalEnable) {
		qDebug() << "点击学习一次";
	}
}



/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值

void CMvContactAttitudeDefect::slotMaskOfDetectionAreaValue(int Index)
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
void CMvContactAttitudeDefect::slotEditModeValue(int Index)
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
void CMvContactAttitudeDefect::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvContactAttitudeDefect::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvContactAttitudeDefect::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvContactAttitudeDefect::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvContactAttitudeDefect::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvContactAttitudeDefect::slotGetStartUpDrawingValue(bool State)
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
void CMvContactAttitudeDefect::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}

//绘制边缘轮廓
void CMvContactAttitudeDefect::slotGetDrawEdgesValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "绘制边缘轮廓" << ui->checkBox_drawEdges->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvContactAttitudeDefect::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvContactAttitudeDefect::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvContactAttitudeDefect::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvContactAttitudeDefect::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvContactAttitudeDefect::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvContactAttitudeDefect::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvContactAttitudeDefect::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
