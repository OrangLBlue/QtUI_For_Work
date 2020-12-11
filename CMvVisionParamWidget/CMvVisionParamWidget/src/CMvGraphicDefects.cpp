#include "CMvGraphicDefects.h"
#include "ui_CMvGraphicDefects.h"
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

CMvGraphicDefects* CMvGraphicDefects::s_pCMvGraphicDefects = nullptr;

CMvGraphicDefects::CMvGraphicDefects(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvGraphicDefects)
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
	initCMvGraphicDefects();

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
	//点击编辑图像模板
	connect(ui->pushButton_editImageTemplate, SIGNAL(clicked()), this, SLOT(slotGetEditImageTemplateIsClick()));

	//获取二值化高阈值
	connect(ui->spinBox_binaryThresholdMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetBinaryThresholdMaxValue(int)));

	//获取二值化低阈值
	connect(ui->spinBox_binaryThresholdMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetBinaryThresholdMinValue(int)));

	//获取缺陷最小灰度差
	connect(ui->spinBox_minimumGrayscale, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumGrayscaleValue(int)));

	//获取缺陷最小面积
	connect(ui->spinBox_minimumArea, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumAreaValue(int)));

	//获取单个图形面积上限
	connect(ui->spinBox_areaMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetAreaMaxValue(int)));

	//获取单个图形面积下限
	connect(ui->spinBox_areaMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetAreaMinValue(int)));

	//点击显示图形面积信息
	connect(ui->pushButton_figureArea, SIGNAL(clicked()), this, SLOT(slotGetFigureAreaIsClick()));

	//开启图形个数限定
	connect(ui->checkBox_number, SIGNAL(clicked(bool)), this, SLOT(slotGetNumberIsChecked(bool)));

	//获取图形个数上限
	connect(ui->spinBox_numberMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMaxValue(int)));

	//获取图形个数下限
	connect(ui->spinBox_numberMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMinValue(int)));


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
CMvGraphicDefects::~CMvGraphicDefects()
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
CMvGraphicDefects* CMvGraphicDefects::Instance()
{
	if (s_pCMvGraphicDefects == nullptr) {
		s_pCMvGraphicDefects = new CMvGraphicDefects;
	}
	return s_pCMvGraphicDefects;
}


//释放内存
void CMvGraphicDefects::destroy()
{
	if (s_pCMvGraphicDefects)
	{
		delete s_pCMvGraphicDefects;
		s_pCMvGraphicDefects = nullptr;
	}//if (s_pCMvGraphicDefects)
}

//初始化数据
void CMvGraphicDefects::initCMvGraphicDefects()
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

	//设置二值化高阈值
	ui->spinBox_binaryThresholdMax->setValue(0);

	//设置二值化低阈值
	ui->spinBox_binaryThresholdMin->setValue(0);

	//设置缺陷最小灰度差
	ui->spinBox_minimumGrayscale->setValue(0);

	//设置缺陷最小面积
	ui->spinBox_minimumArea->setValue(0);

	//设置单个图形面积上限
	ui->spinBox_areaMax->setValue(0);

	//设置单个图形面积下限
	ui->spinBox_areaMin->setValue(0);

	//设置图形个数上限
	ui->spinBox_numberMax->setValue(0);

	//设置图形个数下限
	ui->spinBox_numberMin->setValue(0);

	//设置图形个数限定选中
	ui->checkBox_number->setChecked(false);
	ui->groupBox_number->setEnabled(ui->checkBox_number->isChecked());

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
void CMvGraphicDefects::slotGetDetectorNameValue()
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
void CMvGraphicDefects::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvGraphicDefects::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMvGraphicDefects::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvGraphicDefects::initMenu()
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

void CMvGraphicDefects::initMenuByTest()
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
void CMvGraphicDefects::slotClickPushButton(int row, int col)
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
void CMvGraphicDefects::soltMenuTriggered(QAction* action)
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

//点击编辑图像模板
void CMvGraphicDefects::slotGetEditImageTemplateIsClick()
{
	qDebug() << "点击编辑图像模板";
}

//获取二值化高阈值
void CMvGraphicDefects::slotGetBinaryThresholdMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取二值化高阈值" << value;
	}
}

//获取二值化低阈值
void CMvGraphicDefects::slotGetBinaryThresholdMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取二值化低阈值" << value;
	}
}

//获取缺陷最小灰度差
void CMvGraphicDefects::slotGetMinimumGrayscaleValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形宽度上限" << value;
	}
}

//获取缺陷最小面积
void CMvGraphicDefects::slotGetMinimumAreaValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小矩形宽度下限" << value;
	}
}

//获取单个图形面积上限
void CMvGraphicDefects::slotGetAreaMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取单个图形面积上限" << value;
	}
}

//获取单个图形面积下限
void CMvGraphicDefects::slotGetAreaMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取单个图形面积下限" << value;
	}
}

//点击显示图形面积信息
void CMvGraphicDefects::slotGetFigureAreaIsClick()
{
	qDebug() << "点击显示图形面积信息";
}

//开启图形个数限定
void CMvGraphicDefects::slotGetNumberIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启图形个数限定" << state;
		ui->groupBox_number->setEnabled(state);
	}
}

//获取图形个数上限
void CMvGraphicDefects::slotGetNumberMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取图形个数上限" << value;
	}
}

//获取图形个数下限
void CMvGraphicDefects::slotGetNumberMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取图形个数下限" << value;
	}
}

/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值
void CMvGraphicDefects::slotMaskOfDetectionAreaValue(int Index)
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
void CMvGraphicDefects::slotEditModeValue(int Index)
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
void CMvGraphicDefects::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvGraphicDefects::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvGraphicDefects::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvGraphicDefects::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvGraphicDefects::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvGraphicDefects::slotGetStartUpDrawingValue(bool State)
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
void CMvGraphicDefects::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}


/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvGraphicDefects::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvGraphicDefects::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvGraphicDefects::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvGraphicDefects::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvGraphicDefects::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvGraphicDefects::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvGraphicDefects::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
