#include "CMvColorSelection.h"
#include "ui_CMvColorSelection.h"
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

CMvColorSelection* CMvColorSelection::s_pColorSelection = nullptr;

CMvColorSelection::CMvColorSelection(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvColorSelection)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("某个检测器的输出");
	/*===============================================================================================*\
	**====================================输入设置相关函数及信号与槽的链接===========================**
	**=================================二级菜单相关函数及信号与槽的链接==============================**
	\*===============================================================================================*/

	//初始化数据
	initCMvColorSelection();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据图片来源菜单动作选择，设置单元格显示内容
	connect(m_pImageSourceMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));


	/*===============================================================================================*\
	**====================================参数设置信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取颜色空间
	connect(ui->comboBox_colorSpace, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetColorSpaceValue(int)));

	//点击显示颜色直方图
	connect(ui->pushButton_colorHistogram, SIGNAL(clicked()), this, SLOT(slotGetUnqualifiedPiontIsClick()));

	//获取启用杂点剔除选中信息
	connect(ui->checkBox_miscellaneousElimination, SIGNAL(clicked(bool)), this, SLOT(slotGetMiscellaneousEliminationIsChecked(bool)));

	//获取面积上限 数值
	connect(ui->doubleSpinBox_maxArea, SIGNAL(valueChanged(double)), this, SLOT(slotGetMaxAreaValue(double)));

	//获取面积下限 数值
	connect(ui->doubleSpinBox_minArea, SIGNAL(valueChanged(double)), this, SLOT(slotGetMinAreaValue(double)));

	//获取背景图像类型 数值
	connect(ui->comboBox_backgroundType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetBackgroundTypeValue(int)));

	/*===============================================================================================*\
	**====================================结果绘制信号与槽的链接=====================================**
	\*===============================================================================================*/
	//获取启动绘制选中信息
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

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
CMvColorSelection::~CMvColorSelection()
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

	if (m_allImageSourceMenuData.size() != 0)
	{
		for (int index = 0; index < m_allImageSourceMenuData.size(); index++)
		{
			delete m_allImageSourceMenuData[index]->pAction;
			delete m_allImageSourceMenuData[index];
		}
		m_allImageSourceMenuData.clear();
	}

	delete ui;
}


//单例化
CMvColorSelection* CMvColorSelection::Instance()
{
	if (s_pColorSelection == nullptr) {
		s_pColorSelection = new CMvColorSelection;
	}
	return s_pColorSelection;
}


//释放内存
void CMvColorSelection::destroy()
{
	if (s_pColorSelection)
	{
		delete s_pColorSelection;
		s_pColorSelection = nullptr;
	}//if (s_pColorSelection)
}

//初始化数据
void CMvColorSelection::initCMvColorSelection()
{
	m_signalEnable = false;

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//设置颜色空间
	ui->comboBox_colorSpace->setCurrentIndex(0);

	//设置启用杂点剔除
	ui->checkBox_miscellaneousElimination->setChecked(false);
	ui->widget_miscellaneousElimination->setEnabled(ui->checkBox_miscellaneousElimination->isChecked());

	//设置面积上限
	ui->doubleSpinBox_maxArea->setValue(5);

	//设置面积下限
	ui->doubleSpinBox_minArea->setValue(5);

	//设置背景图像类型
	ui->comboBox_backgroundType->setCurrentIndex(0);

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;
}


/*===============================================================================================*\
**====================================输入设置页面槽函数=========================================**
\*===============================================================================================*/
//获取检测器名称
void CMvColorSelection::slotGetDetectorNameValue()
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
void CMvColorSelection::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**======================================二级菜单槽函数===========================================**
\*===============================================================================================*/
////初始化二级菜单
void CMvColorSelection::initMenu()
{

}

void CMvColorSelection::initMenuByTest()
{
	//初始化图片来源菜单
	m_pImageSourceMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_allImageSourceMenuData);
}

//根据点击位置选择弹框
void CMvColorSelection::slotClickPushButton(int row, int col)
{
	qDebug() << "位置确定";
	//根据在tabelWidget点击的位置判断该弹出的菜单
	if (col == 1 && row == 0)
	{
		m_pImageSourceMenu->move(cursor().pos());
		m_pImageSourceMenu->show();
	}

	//记录点击的行列数据
	m_iRow = row;
	m_iCol = col;
}

//菜单动作点击
void CMvColorSelection::soltMenuTriggered(QAction* action)
{
	//设置点击栏的显示内容
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "弹出";
	if (m_iRow == 0)
	{
		allMenuData = m_allImageSourceMenuData;
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
//获取颜色空间
void CMvColorSelection::slotGetColorSpaceValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取颜色空间" << ui->comboBox_colorSpace->itemText(index);
	}
}

//点击显示颜色直方图
void CMvColorSelection::slotGetUnqualifiedPiontIsClick()
{
	qDebug() << "点击显示颜色直方图";
}


//获取启用杂点剔除选中信息
void CMvColorSelection::slotGetMiscellaneousEliminationIsChecked(bool State)
{
	qDebug() << "获取开启凹凸性检测选中信息" << State << " " << ui->checkBox_miscellaneousElimination->isChecked();

	ui->widget_miscellaneousElimination->setEnabled(State);
}


//获取面积上限 数值
void CMvColorSelection::slotGetMaxAreaValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积上限" << ui->doubleSpinBox_maxArea->value() << "  " << Value;
	}
}

//获取面积下限 数值
void CMvColorSelection::slotGetMinAreaValue(double Value)
{
	if (m_signalEnable) {
		qDebug() << "获取面积下限" << ui->doubleSpinBox_minArea->value() << "  " << Value;
	}
}

//获取背景图像类型 数值
void CMvColorSelection::slotGetBackgroundTypeValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "获取背景图像类型" << ui->comboBox_backgroundType->itemText(index);
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/

//获取启动绘制选中信息
void CMvColorSelection::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvColorSelection::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvColorSelection::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvColorSelection::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvColorSelection::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvColorSelection::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvColorSelection::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvColorSelection::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}
