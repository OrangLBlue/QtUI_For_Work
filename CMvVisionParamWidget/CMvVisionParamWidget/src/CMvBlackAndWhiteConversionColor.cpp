#include "CMvBlackAndWhiteConversionColor.h"
#include "ui_CMvBlackAndWhiteConversionColor.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QDebug>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvBlackAndWhiteConversionColor * CMvBlackAndWhiteConversionColor::s_pBlackAndWhiteConversionColor = nullptr;

CMvBlackAndWhiteConversionColor::CMvBlackAndWhiteConversionColor(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvBlackAndWhiteConversionColor)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_signalEnable = true;
	m_pSecondLevelMenu = new CMvSecondLevelMenu;
	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//���õ�Ԫ�� �ȿ�

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("ĳ������������");

	//��ʼ�����ж����˵�
	initMenuByTest();

	//�㷨ѡ�񴥷�
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//���ݺڰ�ͼ�񵥶���ѡ�����õ�Ԫ����ʾ����
	connect(m_pBlackAndWhiteImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//��ȡ���������
	connect(ui->plainTextEdit_funcName_2, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//��ȡ���ü����ѡ����Ϣ
	connect(ui->checkBox_enableFunc_2, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	/*===============================================================================================*\
	**====================================�������ź���۵�����=======================================**
	\*===============================================================================================*/
	//��� �Ŵ�
	connect(ui->pushButton_zoomIn, SIGNAL(clicked()), this, SLOT(slotAmplifyThePictureIsClick()));

	//��� ��С
	connect(ui->pushButton_zoomOut, SIGNAL(clicked()), this, SLOT(slotShrinkThePictureIsClick()));

	//��� ��óߴ�
	connect(ui->pushButton_zoomBest, SIGNAL(clicked()), this, SLOT(slotBestSizeOfPictureIsClick()));

	//��� ����ROI
	connect(ui->pushButton_lockRoiMove, SIGNAL(clicked()), this, SLOT(slotLockROIIsClick()));

	//��� ����
	connect(ui->pushButton_ones, SIGNAL(clicked()), this, SLOT(slotOnceIsClick()));

	//��� ȷ��
	connect(ui->pushButton_affirm, SIGNAL(clicked()), this, SLOT(slotMakeSureIsClick()));

	//��� ȡ��
	connect(ui->pbPrev_cancel, SIGNAL(clicked()), this, SLOT(slotCancelIsClick()));



	//��ȡ��������ѡ����Ϣ
	connect(ui->checkBox_valuTrig_4, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));


	//���ùر�ʱ�ͷ��ڴ�
	setAttribute(Qt::WA_DeleteOnClose);
}

CMvBlackAndWhiteConversionColor::~CMvBlackAndWhiteConversionColor()
{

	qDebug() << "��������";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	if (m_pBlackAndWhiteImageMenuData.size() != 0)
	{
		for (int index = 0; index < m_pBlackAndWhiteImageMenuData.size(); index++)
		{
			delete m_pBlackAndWhiteImageMenuData[index]->pAction;
			delete m_pBlackAndWhiteImageMenuData[index];
		}
		m_pBlackAndWhiteImageMenuData.clear();
	}

	delete ui;
}

CMvBlackAndWhiteConversionColor* CMvBlackAndWhiteConversionColor::Instance()
{
	if (s_pBlackAndWhiteConversionColor == nullptr)
	{
		s_pBlackAndWhiteConversionColor = new CMvBlackAndWhiteConversionColor;
	}
	return s_pBlackAndWhiteConversionColor;
}

void CMvBlackAndWhiteConversionColor::destroy()
{
	if (s_pBlackAndWhiteConversionColor)
	{
		delete s_pBlackAndWhiteConversionColor;
		s_pBlackAndWhiteConversionColor = nullptr;
	}
}

void CMvBlackAndWhiteConversionColor::initMenuByTest()
{
	//��ʼ��ͼƬ��Դ�˵�
	m_pBlackAndWhiteImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pBlackAndWhiteImageMenuData);
}

void CMvBlackAndWhiteConversionColor::slotClickPushButton(int row, int col)
{
	qDebug() << "λ��ȷ��";
	//������tabelWidget�����λ���жϸõ����Ĳ˵�
	if (col == 1 && row == 0)
	{
		m_pBlackAndWhiteImageMenu->move(cursor().pos());
		m_pBlackAndWhiteImageMenu->show();
	}

	//��¼�������������
	m_iRow = row;
	m_iCol = col;
}

//�˵��������
void CMvBlackAndWhiteConversionColor::soltMenuTriggered(QAction* action)
{
	//���õ��������ʾ����
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "����";

	if (m_iCol == 1)
	{
		allMenuData = m_pBlackAndWhiteImageMenuData;
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
	 //������ʾ����Ϊѡ������
	pTableItem->setText(showInfoText);

	//��ʼ����������
	m_iRow = -1;
	m_iCol = -1;
}

/*===============================================================================================*\
**====================================��������ҳ��ۺ���=========================================**
\*===============================================================================================*/
//��ȡ���������
void CMvBlackAndWhiteConversionColor::slotGetDetectorNameValue()
{
	if (m_signalEnable) {
		QString strText = ui->plainTextEdit_funcName_2->toPlainText();
		int nLength = strText.length();
		for (int index = 0; index < nLength; index++)
		{
			if (strText[index] == '\n') {
				ui->plainTextEdit_funcName_2->blockSignals(true);
				strText.remove("\n");
				qDebug() << "��ȡ���������" << strText;
				ui->plainTextEdit_funcName_2->setPlainText(strText);
				ui->plainTextEdit_funcName_2->blockSignals(false);
			}
		}
	}
}


//��ȡ���ü����ѡ����Ϣ
void CMvBlackAndWhiteConversionColor::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ���ü����ѡ����Ϣ" << ui->checkBox_enableFunc_2->isChecked();
	}
}

/*===============================================================================================*\
**=======================================�������ҳ��ۺ���======================================**
\*===============================================================================================*/
//��ȡ��������ѡ����Ϣ
void CMvBlackAndWhiteConversionColor::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ��������ѡ����Ϣ" << ui->checkBox_valuTrig_4->isChecked();
	}
}

/*===============================================================================================*\
**======================================�������ۺ���=============================================**
\*===============================================================================================*/
//��� �Ŵ�
void CMvBlackAndWhiteConversionColor::slotAmplifyThePictureIsClick()
{
	qDebug() << "�Ŵ󱻵���";
}

//��� ��С
void CMvBlackAndWhiteConversionColor::slotShrinkThePictureIsClick()
{
	qDebug() << "��С������";
}

//��� ��óߴ�
void CMvBlackAndWhiteConversionColor::slotBestSizeOfPictureIsClick()
{
	qDebug() << "��óߴ类����";
}

//��� ����ROI
void CMvBlackAndWhiteConversionColor::slotLockROIIsClick()
{
	qDebug() << "����ROI������";
}

//��� ����
void CMvBlackAndWhiteConversionColor::slotOnceIsClick()
{
	qDebug() << "���α�����";
}

//��� ȷ��
void CMvBlackAndWhiteConversionColor::slotMakeSureIsClick()
{
	qDebug() << "ȷ��������";
}

//��� ȡ��
void CMvBlackAndWhiteConversionColor::slotCancelIsClick()
{
	qDebug() << "ȡ��������";
}

