#include "CMvChipDefect.h"
#include "ui_CMvChipDefect.h"
#include <QStringList>
#include <QTableWidgetItem>
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

CMvChipDefect * CMvChipDefect::s_pCMvChipDefect = nullptr;

CMvChipDefect::CMvChipDefect(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvChipDefect)
{ 
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	//ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置单元格 等宽

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");

	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	m_signalEnable = true;

	//初始化数据
	initCMvChipDefect();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据彩色图像菜单动作选择，设置单元格显示内容
	connect(m_pColorImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	
	//选择二值化类型
	connect(ui->comboBox_binaryDetection, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeBinaryDetection(int)));

	//获取晶片灰度阈值
	connect(ui->spinBox_grayLevel, SIGNAL(valueChanged(int)), this, SLOT(slotGetGrayLevelValue(int)));

	//获取晶片宽度上限
	connect(ui->spinBox_rectangleMaxWidth, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMaxWidthValue(int)));

	//获取晶片宽度下限
	connect(ui->spinBox_rectangleMinWidth, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMinWidthValue(int)));

	//获取晶片高度上限
	connect(ui->spinBox_rectangleMaxHight, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMaxHightValue(int)));

	//获取晶片高度下限
	connect(ui->spinBox_rectangleMinHight, SIGNAL(valueChanged(int)), this, SLOT(slotGetRectangleMinHightValue(int)));

	//开启检测外凸缺陷
	connect(ui->checkBox_evagination, SIGNAL(clicked(bool)), this, SLOT(slotGetEvaginationIsChecked(bool)));

	//开启检测内陷缺陷
	connect(ui->checkBox_invagination, SIGNAL(clicked(bool)), this, SLOT(slotGetInvaginationIsChecked(bool)));

	//开启检测切角缺陷
	connect(ui->checkBox_cornerCut, SIGNAL(clicked(bool)), this, SLOT(slotGetCornerCutIsChecked(bool)));

	//获取外凸最小长度
	connect(ui->spinBox_minimumLengthConvex, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinimumLengthConvexValue(double)));

	//获取外凸边缘不平整度
	connect(ui->spinBox_edgeUnevenEvagination, SIGNAL(valueChanged(double)), this, SLOT(slotGetEdgeUnevenEvaginationValue(double)));

	//获取内陷最小深度
	connect(ui->spinBox_minimumDepthSubsidence, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinimumDepthSubsidenceValue(double)));

	//获取内陷边缘不平整度
	connect(ui->spinBox_edgeUnevenInvagination, SIGNAL(valueChanged(double)), this, SLOT(slotGetEdgeUnevenInvaginationValue(double)));

	//获取与顶点最小距离
	connect(ui->spinBox_minimumRange, SIGNAL(valueChanged(int)), this, SLOT(slotGetMinimumRangeValue(int)));

	//获取与顶点最大距离
	connect(ui->spinBox_maximumRange, SIGNAL(valueChanged(int)), this, SLOT(slotGetMaximumRangeValue(int)));	

	//开启检测空洞缺陷
	connect(ui->checkBox_cavity, SIGNAL(clicked(bool)), this, SLOT(slotGetCavityIsChecked(bool)));
	
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

	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//设置关闭时释放内存
	//setAttribute(Qt::WA_DeleteOnClose);
}

CMvChipDefect::~CMvChipDefect()
{
	qDebug() << "析构函数";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	//if (m_pColorImageMenu)
	//{
	//	for (int index = 0; index < m_pColorImageMenu->actions().size(); index++)
	//	{
	//		delete m_pColorImageMenu->actions()[0]->menu();
	//	}
	//	delete m_pColorImageMenu;
	//	m_pColorImageMenu = nullptr;
	//}

	if (m_pColorImageMenuData.size() != 0)
	{
		for (int index = 0; index < m_pColorImageMenuData.size(); index++)
		{
			delete m_pColorImageMenuData[index]->pAction;
			delete m_pColorImageMenuData[index];
		}
		m_pColorImageMenuData.clear();
	}

	delete ui;
}

//单例
CMvChipDefect * CMvChipDefect::Instance()
{
	if (s_pCMvChipDefect == nullptr)
	{
		s_pCMvChipDefect = new CMvChipDefect;
	}
	return s_pCMvChipDefect;

}

//释放内存
void CMvChipDefect::destroy()
{
	if (s_pCMvChipDefect)
	{
		delete s_pCMvChipDefect;
		s_pCMvChipDefect = nullptr;
	}
}

//初始化数据
void CMvChipDefect::initCMvChipDefect()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

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

	//获取晶片灰度阈值
	ui->spinBox_grayLevel->setValue(5);

	//获取晶片宽度上限
	ui->spinBox_rectangleMaxWidth->setValue(5);

	//获取晶片宽度下限
	ui->spinBox_rectangleMinWidth->setValue(5);

	//获取晶片高度上限
	ui->spinBox_rectangleMaxHight->setValue(5);

	//获取晶片高度下限
	ui->spinBox_rectangleMinHight->setValue(5);

	//开启检测外凸缺陷
	ui->checkBox_evagination->setChecked(false);
	ui->groupBox_evagination->setEnabled(ui->checkBox_evagination->isChecked());

	//开启检测内陷缺陷
	ui->checkBox_invagination->setChecked(false);
	ui->groupBox_invagination->setEnabled(ui->checkBox_invagination->isChecked());

	//开启检测切角缺陷
	ui->checkBox_cornerCut->setChecked(false);
	ui->groupBox_cornerCut->setEnabled(ui->checkBox_cornerCut->isChecked());

	//获取外凸最小长度
	ui->spinBox_minimumLengthConvex->setValue(5);

	//获取外凸边缘不平整度
	ui->spinBox_edgeUnevenEvagination->setValue(5);

	//获取内陷最小深度
	ui->spinBox_minimumDepthSubsidence->setValue(5);

	//获取内陷边缘不平整度
	ui->spinBox_edgeUnevenInvagination->setValue(5);

	//获取与顶点最小距离
	ui->spinBox_minimumRange->setValue(5);

	//获取与顶点最大距离
	ui->spinBox_maximumRange->setValue(5);

	//开启检测空洞缺陷
	ui->checkBox_cavity->setChecked(false);

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;

}

//选择二值化类型
void CMvChipDefect::slotChangeBinaryDetection(int index)
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

//获取晶片灰度阈值
void CMvChipDefect::slotGetGrayLevelValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取晶片灰度阈值" << value;
	}
}

//获取晶片宽度上限
void CMvChipDefect::slotGetRectangleMaxWidthValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取晶片宽度上限" << value;
	}
}

//获取晶片宽度下限
void CMvChipDefect::slotGetRectangleMinWidthValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取晶片宽度下限" << value;
	}
}

//获取晶片高度上限
void CMvChipDefect::slotGetRectangleMaxHightValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取晶片高度上限" << value;
	}
}

//获取晶片高度下限
void CMvChipDefect::slotGetRectangleMinHightValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取晶片高度下限" << value;
	}
}

//开启检测外凸缺陷
void CMvChipDefect::slotGetEvaginationIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启检测外凸缺陷" << state;
		ui->groupBox_evagination->setEnabled(state);
	}
}

//开启检测内陷缺陷
void CMvChipDefect::slotGetInvaginationIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启检测内陷缺陷" << state;
		ui->groupBox_invagination->setEnabled(state);
	}
}

//开启检测切角缺陷
void CMvChipDefect::slotGetCornerCutIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启检测切角缺陷" << state;
		ui->groupBox_cornerCut->setEnabled(state);
	}
}

//获取外凸最小长度
void CMvChipDefect::slotGetMinimumLengthConvexValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取外凸最小长度" << ui->spinBox_minimumLengthConvex->value() << value;
	}
}

//获取外凸边缘不平整度
void CMvChipDefect::slotGetEdgeUnevenEvaginationValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取外凸边缘不平整度" << ui->spinBox_edgeUnevenEvagination->value() << value;
	}
}

//获取内陷最小深度
void CMvChipDefect::slotGetMinimumDepthSubsidenceValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取内陷最小深度" << ui->spinBox_minimumDepthSubsidence->value() << value;
	}
}

//获取内陷边缘不平整度
void CMvChipDefect::slotGetEdgeUnevenInvaginationValue(double value)
{
	if (m_signalEnable) {
		qDebug() << "获取内陷边缘不平整度" << ui->spinBox_edgeUnevenInvagination->value() << value;
	}
}

//获取与顶点最小距离
void CMvChipDefect::slotGetMinimumRangeValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取与顶点最小距离" << ui->spinBox_minimumRange->value() << value;
	}
}

//获取与顶点最大距离
void CMvChipDefect::slotGetMaximumRangeValue(int value)
{
	if (m_signalEnable) {
		qDebug() << "获取与顶点最大距离" << ui->spinBox_maximumRange->value() << value;
	}
}

//开启检测空洞缺陷
void CMvChipDefect::slotGetCavityIsChecked(bool state)
{
	if (m_signalEnable) {
		qDebug() << "开启检测空洞缺陷" << state;
	}
}



void CMvChipDefect::initMenuByTest()
{
	//初始化图片来源菜单
	m_pColorImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pColorImageMenuData);
}

void CMvChipDefect::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pColorImageMenu->move(cursor().pos());
		m_pColorImageMenu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvChipDefect::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";

	if (m_iCol == 1 && m_iRow == 0)
	{
		allMenuData = m_pColorImageMenuData ;
		ui->tableWidget_input->item(m_iRow, m_iCol)->setBackground(Qt::yellow);
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
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvChipDefect::slotGetDetectorNameValue()
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
void CMvChipDefect::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvChipDefect::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvChipDefect::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvChipDefect::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvChipDefect::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvChipDefect::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvChipDefect::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvChipDefect::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvChipDefect::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}

