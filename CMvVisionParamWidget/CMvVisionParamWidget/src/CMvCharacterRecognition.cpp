#include "CMvCharacterRecognition.h"
#include "ui_CMvCharacterRecognition.h"
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
//

CMvCharacterRecognition* CMvCharacterRecognition::s_pCMvCharacterRecognition = nullptr;

CMvCharacterRecognition::CMvCharacterRecognition(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvCharacterRecognition)
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
	//启用字符训练
	connect(ui->checkBox_characterTraining, SIGNAL(clicked(bool)), this, SLOT(slotGetSharacterTrainingIsChecked(bool)));

	//获取分割字符
	connect(ui->plainTextEdit_splitCharacter, SIGNAL(textChanged()), this, SLOT(slotGetSplitCharacter()));

	//点击裁剪
	connect(ui->pushButton_cutOut, SIGNAL(clicked()), this, SLOT(slotCutOutIsClick()));

	//点击打开训练界面
	connect(ui->pushButton_trainingCharacter, SIGNAL(clicked()), this, SLOT(slottRainingCharacterClick()));

	//获取二值化类型
	connect(ui->comboBox_binaryzation, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetBinaryzation(int)));

	//获取灰度阈值
	connect(ui->spinBox_grayLevel, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelValue(int)));

	//开启二值图像
	connect(ui->checkBox_binaryzationShow, SIGNAL(clicked(bool)), this, SLOT(slotGetBinaryzationShowIsChecked(bool)));

	//获取字符颜色
	connect(ui->comboBox_color, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetColor(int)));

	//获取最小相似度
	connect(ui->doubleSpinBox_similarityMinimum, SIGNAL(valueChanged(double)), this, SLOT(slotGetSimilarityMinimumValue(double)));

	//获取绘制字符大小
	connect(ui->spinBox_size, SIGNAL(valueChanged(int)), this, SLOT(slotGetSizeValue(int)));

	//获取宽度上限
	connect(ui->spinBox_maxWidth, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMaxWidthValue(int)));

	//获取宽度下限
	connect(ui->spinBox_minWidth, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMinWidthValue(int)));

	//获取高度上限
	connect(ui->spinBox_maxHight, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMaxHightValue(int)));

	//获取高度下限
	connect(ui->spinBox_minHight, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMinHightValue(int)));

	//获取投影最小宽度
	connect(ui->spinBox_minimumWidith, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumWidithValue(int)));

	//获取投影最小高度
	connect(ui->spinBox_minimumHeight, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumHeightValue(int)));

	//获取个数上限
	connect(ui->spinBox_numberMax, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMaxValue(int)));

	//获取个数下限
	connect(ui->spinBox_numberMin, SIGNAL(valueChanged(int)), this, SLOT(slotGetNumberMinValue(int)));

	//获取字符最小点数
	connect(ui->spinBox_minimumNumberCharacters, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumNumberCharactersValue(int)));

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
CMvCharacterRecognition::~CMvCharacterRecognition()
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
CMvCharacterRecognition* CMvCharacterRecognition::Instance()
{
	if (s_pCMvCharacterRecognition == nullptr) {
		s_pCMvCharacterRecognition = new CMvCharacterRecognition;
	}
	return s_pCMvCharacterRecognition;
}


//释放内存
void CMvCharacterRecognition::destroy()
{
	if (s_pCMvCharacterRecognition)
	{
		delete s_pCMvCharacterRecognition;
		s_pCMvCharacterRecognition = nullptr;
	}//if (c_pUniqueShowMessage)
}

//初始化界面
void CMvCharacterRecognition::initBlobRapidDetection()
{
	m_signalEnable = false;

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");

	//设置ROI来源
	ui->comboBox_imageSource->setCurrentIndex(0);

	//启用字符训练
	ui->checkBox_characterTraining->setChecked(false);
	ui->groupBox_characterTraining->setEnabled(ui->checkBox_characterTraining->isChecked());
	
	//获取分割字符
	ui->plainTextEdit_splitCharacter->setPlainText("");

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

	//开启二值图像
	ui->checkBox_binaryzationShow->setChecked(false);

	//获取字符颜色
	ui->comboBox_color->setCurrentIndex(0);

	//获取最小相似度
	ui->doubleSpinBox_similarityMinimum->setValue(0);
	
	//获取绘制字符大小
	ui->spinBox_size->setValue(0);
	
	//获取宽度上限
	ui->spinBox_maxWidth->setValue(0);

	//获取宽度下限
	ui->spinBox_minWidth->setValue(0);
	
	//获取高度上限
	ui->spinBox_maxHight->setValue(0);

	//获取高度下限
	ui->spinBox_minHight->setValue(0);
	
	//获取投影最小宽度
	ui->spinBox_minimumWidith->setValue(0);
	
	//获取投影最小高度
	ui->spinBox_minimumHeight->setValue(0);

	//获取个数上限
	ui->spinBox_numberMin->setValue(0);

	//获取个数下限
	ui->spinBox_numberMax->setValue(0);
	
	//获取字符最小点数
	ui->spinBox_minimumNumberCharacters->setValue(0);
	


	

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
void CMvCharacterRecognition::slotGetDetectorNameValue()
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
void CMvCharacterRecognition::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvCharacterRecognition::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMvCharacterRecognition::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}


/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvCharacterRecognition::initMenu()
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

void CMvCharacterRecognition::initMenuByTest()
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
void CMvCharacterRecognition::slotClickPushButton(int row, int col)
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
void CMvCharacterRecognition::soltMenuTriggered(QAction* action)
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
//启用字符训练
void CMvCharacterRecognition::slotGetSharacterTrainingIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "启用字符训练" << state; 
		ui->groupBox_characterTraining->setEnabled(state);
	}
}

//获取分割字符
void CMvCharacterRecognition::slotGetSplitCharacter()
{
	if (m_signalEnable) {
		QString strText = ui->plainTextEdit_splitCharacter->toPlainText();
		int nLength = strText.length();
		for (int index = 0; index < nLength; index++)
		{
			if (strText[index] == '\n') {
				ui->plainTextEdit_splitCharacter->blockSignals(true);
				strText.remove("\n");
				qDebug() << "获取分割字符" << strText;
				ui->plainTextEdit_splitCharacter->setPlainText(strText);
				ui->plainTextEdit_splitCharacter->blockSignals(false);
			}
		}
	}
}

//点击裁剪
void CMvCharacterRecognition::slotCutOutIsClick()
{
	if (m_signalEnable) {
		qDebug() << "点击裁剪";
	}
}

//点击打开训练界面
void CMvCharacterRecognition::slottRainingCharacterClick()
{
	if (m_signalEnable) {
		qDebug() << "点击打开训练界面";
	}
}

//获取二值化类型
void CMvCharacterRecognition::slotGetBinaryzation(int index)
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
void CMvCharacterRecognition::slotGetGrayLevelValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取灰度阈值" << value;
	}
}

//开启二值图像
void CMvCharacterRecognition::slotGetBinaryzationShowIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启二值图像" << state;
	}
}

//获取字符颜色
void CMvCharacterRecognition::slotGetColor(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取字符颜色" << ui->comboBox_color->itemText(index);
	}
}

//获取最小相似度
void CMvCharacterRecognition::slotGetSimilarityMinimumValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取最小相似度" << value;
	}
}

//获取绘制字符大小
void CMvCharacterRecognition::slotGetSizeValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取绘制字符大小" << value;
	}
}

//获取宽度上限
void CMvCharacterRecognition::slotGetRectangleMaxWidthValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取宽度上限" << value;
	}
}

//获取宽度下限
void CMvCharacterRecognition::slotGetRectangleMinWidthValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取宽度下限" << value;
	}
}


//获取高度上限
void CMvCharacterRecognition::slotGetRectangleMaxHightValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取高度上限" << value;
	}
}

//获取高度下限
void CMvCharacterRecognition::slotGetRectangleMinHightValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取高度下限" << value;
	}
}

//获取投影最小宽度
void CMvCharacterRecognition::slotGetMinimumWidithValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取投影最小宽度" << value;
	}
}

//获取投影最小高度
void CMvCharacterRecognition::slotGetMinimumHeightValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取投影最小高度" << value;
	}
}


//获取个数上限
void CMvCharacterRecognition::slotGetNumberMaxValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取个数上限" << value;
	}
}

//获取个数下限
void CMvCharacterRecognition::slotGetNumberMinValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取个数下限" << value;
	}
}

//获取字符最小点数
void CMvCharacterRecognition::slotGetMinimumNumberCharactersValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取字符最小点数" << value;
	}
}

/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值

void CMvCharacterRecognition::slotMaskOfDetectionAreaValue(int Index)
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
void CMvCharacterRecognition::slotEditModeValue(int Index)
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
void CMvCharacterRecognition::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvCharacterRecognition::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvCharacterRecognition::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvCharacterRecognition::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取线条宽度 数值
void CMvCharacterRecognition::slotGetLineWidthValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取线条宽度" << ui->spinBox_lineWidth->value() << " " << Value;
	}
}

//获取启动绘制选中信息
void CMvCharacterRecognition::slotGetStartUpDrawingValue(bool State)
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
void CMvCharacterRecognition::slotGetLineColourValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "获取线条颜色" << ui->comboBox_lineColour->itemText(Index);
	}
}


/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvCharacterRecognition::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvCharacterRecognition::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvCharacterRecognition::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvCharacterRecognition::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvCharacterRecognition::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvCharacterRecognition::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvCharacterRecognition::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
