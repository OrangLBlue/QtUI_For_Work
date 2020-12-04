#include "CMvImagesCut.h"
#include "ui_CMvImagesCut.h"
#include <QTableWidgetItem>
#include "CMvSecondLevelMenu.h"
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

CMvImagesCut * CMvImagesCut::s_pimagesCut = nullptr;

CMvImagesCut::CMvImagesCut(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvImagesCut)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_iRow = -1;
	m_iCol = -1;
	//设置单元格 等宽
	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");
	
	m_maskCount = 0;

	m_pSecondLevelMenu = new CMvSecondLevelMenu;
	//初始化数据
	initCMvImagesCut();

	////初始显示裁剪图片按钮
	//initPushButton();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据彩色图片菜单动作选择，设置单元格显示内容
	connect(m_pColorImagesMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//根据坐标输入菜单动作选择，设置单元格显示内容
	connect(m_pCoordinateInputMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	//点击ROI来源选择获取选项信息
	connect(ui->comboBox_imageSource, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetROISourcesValue(int)));

	//获取自己创建选中信息
	connect(ui->checkBox_roiCreat, SIGNAL(clicked(bool)), this, SLOT(slotGetCreateYourselfValue(bool)));

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


	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//设置关闭窗体时释放资源
	//setAttribute(Qt::WA_DeleteOnClose);
}

//析构函数
CMvImagesCut::~CMvImagesCut()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_ColorImagesMenuData.size() != 0)
	{
		for (int index = 0; index < m_ColorImagesMenuData.size(); index++)
		{
			delete m_ColorImagesMenuData[index]->pAction;
			delete m_ColorImagesMenuData[index];
		}
		m_ColorImagesMenuData.clear();
	}

	if (m_pCoordinateInputMenuData.size() != 0)
	{
		for (int index = 0; index < m_pCoordinateInputMenuData.size(); index++)
		{
			delete m_pCoordinateInputMenuData[index]->pAction;
			delete m_pCoordinateInputMenuData[index];
		}
		m_pCoordinateInputMenuData.clear();
	}

	delete ui;
}

//单实例
CMvImagesCut * CMvImagesCut::Instance()
{
	if (s_pimagesCut == nullptr)
	{
		s_pimagesCut = new CMvImagesCut;
	}
	return s_pimagesCut;
}

//释放内存
void CMvImagesCut::destroy()
{
	if (s_pimagesCut)
	{
		delete s_pimagesCut;
		s_pimagesCut = nullptr;
	}
}


//初始化数据
void CMvImagesCut::initCMvImagesCut()
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

	m_signalEnable = true;
}


////初始化按钮
//void CMvImagesCut::initPushButton()
//{
//	m_pPushbutton_cuttingPicture = new QPushButton(this);
//	m_pPushbutton_cuttingPicture->setText(tr("显示裁剪图像"));
//
//	ui->tableWidget_input->setCellWidget(0, 2, m_pPushbutton_cuttingPicture);
//
//}

//初始化二级菜单
void CMvImagesCut::initMenuByTest()
{
	//初始化图片来源菜单
	m_pColorImagesMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_ColorImagesMenuData);

	//初始化ROI来源菜单
	m_pCoordinateInputMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pCoordinateInputMenuData);
}

//根据点击位置选择弹框
void CMvImagesCut::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1)
	{
		switch (row)
		{
		case 0:
			m_pColorImagesMenu->move(cursor().pos());
			m_pColorImagesMenu->show();
			qDebug() << "m_pColorImagesMenu " << m_pColorImagesMenu->isEmpty();

			break;

		case 1:
			m_pCoordinateInputMenu->move(cursor().pos());
			m_pCoordinateInputMenu->show();
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
void CMvImagesCut::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";
	switch (m_iRow)
	{
	case 0:
		allMenuData = m_ColorImagesMenuData;
		break;

	case 1:
		allMenuData = m_pCoordinateInputMenuData;
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
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvImagesCut::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
	//pushButton_zoomIn
}

//点击 缩小
void CMvImagesCut::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
	//pushButton_zoomOut
}

//点击 最好尺寸
void CMvImagesCut::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
	//pushButton_zoomBest
}

//点击 锁定ROI
void CMvImagesCut::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
	//pushButton_lockRoiMove
}

//点击 单次
void CMvImagesCut::slotOnceIsClick()
{
	qDebug() << "单次被点了";
	//pushButton_ones
}

//点击 确定
void CMvImagesCut::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
	//pushButton_ensure
}

//点击 取消
void CMvImagesCut::slotCancelIsClick()
{
	qDebug() << "取消被点了";
	//pbPrev_cancel
}

/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvImagesCut::slotGetDetectorNameValue()
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
void CMvImagesCut::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

//获取ROI来源
void CMvImagesCut::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取ROI来源选项" << ui->comboBox_imageSource->itemText(index);
	}
}

//获取自己创建选中信息
void CMvImagesCut::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取自己创建选中信息" << ui->checkBox_roiCreat->isChecked();
	}
}

/*===============================================================================================*\
**=======================================掩膜设置槽函数==========================================**
\*===============================================================================================*/
//获取检测区域的掩膜 数值
void CMvImagesCut::slotMaskOfDetectionAreaValue(int Index)
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
void CMvImagesCut::slotEditModeValue(int Index)
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
void CMvImagesCut::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "获取画笔尺寸" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//点击清空掩膜
void CMvImagesCut::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "清空掩膜被点了,当前掩膜数量为:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//点击掩盖所有
void CMvImagesCut::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "掩盖所有被点了";
	}
}

//点击保存修改
void CMvImagesCut::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "保存修改被点了";
	}
}


/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvImagesCut::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();

	}
}