#include "CMvColorConversionBlackAndWhite.h"
#include "ui_CMvColorConversionBlackAndWhite.h"
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

CMvColorConversionBlackAndWhite * CMvColorConversionBlackAndWhite::s_pColorConversionBlackAndWhite = nullptr;

CMvColorConversionBlackAndWhite::CMvColorConversionBlackAndWhite(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvColorConversionBlackAndWhite)
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
	initCMvColorConversionBlackAndWhite();

	//算法选择触发
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//根据彩色图像菜单动作选择，设置单元格显示内容
	connect(m_pColorImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//选择颜色空间
	connect(ui->comboBox_colorSpace, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeColorSpace(int)));

	//选择颜色通道
	connect(ui->comboBox_colorChannel, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeColorChannel(int)));

	//获取检测器名称
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//获取启用检测器选中信息
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

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

CMvColorConversionBlackAndWhite::~CMvColorConversionBlackAndWhite()
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
CMvColorConversionBlackAndWhite * CMvColorConversionBlackAndWhite::Instance()
{
	if (s_pColorConversionBlackAndWhite == nullptr)
	{
		s_pColorConversionBlackAndWhite = new CMvColorConversionBlackAndWhite;
	}
	return s_pColorConversionBlackAndWhite;

}

//释放内存
void CMvColorConversionBlackAndWhite::destroy()
{
	if (s_pColorConversionBlackAndWhite)
	{
		delete s_pColorConversionBlackAndWhite;
		s_pColorConversionBlackAndWhite = nullptr;
	}
}

//初始化数据
void CMvColorConversionBlackAndWhite::initCMvColorConversionBlackAndWhite()
{
	m_signalEnable = false;

	//初始化颜色空间
	initComboBoxOfColorSpace();

	//初始化颜色通道
	initComboBoxOfColorChannel();

	//初始化所有二级菜单
	initMenuByTest();

	//设置检测器名称
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//设置颜色空间
	ui->comboBox_colorSpace->setCurrentIndex(0);

	//设置颜色通道
	ui->comboBox_colorChannel->setCurrentIndex(0);

	//设置绘图
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;

}


//初始化颜色空间
void CMvColorConversionBlackAndWhite::initComboBoxOfColorSpace()
{
	//ui->comboBox_colorSpace = new QComboBox(this);
	ui->comboBox_colorSpace->setObjectName(QStringLiteral("颜色空间"));

	ui->comboBox_colorSpace->clear();
	QStringList fonts;
	fonts << "RGB" << "HSV" << "LAB";
	ui->comboBox_colorSpace->addItems(fonts);

	//ui->tableWidget_input->setCellWidget(0, 1, ui->comboBox_colorSpace);
}

//初始化颜色通道
void CMvColorConversionBlackAndWhite::initComboBoxOfColorChannel()
{
	//ui->comboBox_colorChannel = new QComboBox(this);
	ui->comboBox_colorChannel->setObjectName(QStringLiteral("颜色通道"));

	ui->comboBox_colorChannel->clear();
	QStringList fonts;
	if (ui->comboBox_colorSpace == nullptr)
	{
		initComboBoxOfColorSpace();
	}
	switch (ui->comboBox_colorSpace->currentIndex())
	{
	case 0:
		fonts << tr("灰度") << tr("红色") << tr("绿色") << tr("蓝色") << tr("黄色") << tr("青色") << tr("品红");
		break;

	case 1:
		fonts << tr("色调") << tr("饱和度") << tr("亮度");
		break;

	case 2:
		fonts << tr("亮度") << "A" << "B";
		break;

	default:
		break;
	}
	
	ui->comboBox_colorChannel->addItems(fonts);

	//ui->tableWidget_input->setCellWidget(0, 2, ui->comboBox_colorChannel);
}

//选择颜色空间
void CMvColorConversionBlackAndWhite::slotChangeColorSpace(int index)
{
	if (m_signalEnable) {
		qDebug() << "选择颜色空间" << ui->comboBox_colorSpace->itemText(index) << " " << index;

		ui->comboBox_colorChannel->blockSignals(true);
		ui->comboBox_colorChannel->clear();
		ui->comboBox_colorChannel->blockSignals(false);
		QStringList fonts;
		switch (index)
		{
		case 0:
			fonts << tr("灰度") << tr("红色") << tr("绿色") << tr("蓝色") << tr("黄色") << tr("青色") << tr("品红");
			break;

		case 1:
			fonts << tr("色调") << tr("饱和度") << tr("亮度");
			break;

		case 2:
			fonts << tr("亮度") << "A" << "B";
			break;

		default:
			break;
		}
		ui->comboBox_colorChannel->addItems(fonts);
	}
}

//选择颜色通道
void CMvColorConversionBlackAndWhite::slotChangeColorChannel(int index)
{
	if (m_signalEnable) {
		qDebug() << "选择颜色通道" << ui->comboBox_colorChannel->itemText(index) << " " << index;
	}
}

void CMvColorConversionBlackAndWhite::initMenuByTest()
{
	//初始化图片来源菜单
	m_pColorImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pColorImageMenuData);
}

void CMvColorConversionBlackAndWhite::slotClickPushButton(int row, int col)
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
void CMvColorConversionBlackAndWhite::soltMenuTriggered(QAction* action)
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
void CMvColorConversionBlackAndWhite::slotGetDetectorNameValue()
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
void CMvColorConversionBlackAndWhite::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "获取启用检测器选中信息" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**=======================================结果绘制页面槽函数======================================**
\*===============================================================================================*/
//获取启动绘制选中信息
void CMvColorConversionBlackAndWhite::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "获取启动绘制选中信息" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================功能栏槽函数=============================================**
\*===============================================================================================*/
//点击 放大
void CMvColorConversionBlackAndWhite::slotAmplifyThePictureIsClick()
{
	qDebug() << "放大被点了";
}

//点击 缩小
void CMvColorConversionBlackAndWhite::slotShrinkThePictureIsClick()
{
	qDebug() << "缩小被点了";
}

//点击 最好尺寸
void CMvColorConversionBlackAndWhite::slotBestSizeOfPictureIsClick()
{
	qDebug() << "最好尺寸被点了";
}

//点击 锁定ROI
void CMvColorConversionBlackAndWhite::slotLockROIIsClick()
{
	qDebug() << "锁定ROI被点了";
}

//点击 单次
void CMvColorConversionBlackAndWhite::slotOnceIsClick()
{
	qDebug() << "单次被点了";
}

//点击 确定
void CMvColorConversionBlackAndWhite::slotMakeSureIsClick()
{
	qDebug() << "确定被点了";
}

//点击 取消
void CMvColorConversionBlackAndWhite::slotCancelIsClick()
{
	qDebug() << "取消被点了";
}

