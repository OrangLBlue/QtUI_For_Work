#include "CMvImageEnhancement.h"
#include "ui_CMvImageEnhancement.h"
#include <QStringList>
#include <QTableWidgetItem>
#include <QDebug>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvImageEnhancement * CMvImageEnhancement::s_pCMvImageEnhancement = nullptr;

CMvImageEnhancement::CMvImageEnhancement(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvImageEnhancement)
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

	//��ʼ������
	initCMvImageEnhancement();

	//�㷨ѡ�񴥷�
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//���ݺڰ�ͼ�񵥶���ѡ�����õ�Ԫ����ʾ����
	connect(m_pBlackAndWhiteImageMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//��ȡ���������
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//��ȡ���ü����ѡ����Ϣ
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));


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
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));


	//���ùر�ʱ�ͷ��ڴ�
	//setAttribute(Qt::WA_DeleteOnClose);
}

CMvImageEnhancement::~CMvImageEnhancement()
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

CMvImageEnhancement* CMvImageEnhancement::Instance()
{
	if (s_pCMvImageEnhancement == nullptr)
	{
		s_pCMvImageEnhancement = new CMvImageEnhancement;
	}
	return s_pCMvImageEnhancement;
}

void CMvImageEnhancement::destroy()
{
	if (s_pCMvImageEnhancement)
	{
		delete s_pCMvImageEnhancement;
		s_pCMvImageEnhancement = nullptr;
	}
}

//��ʼ������
void CMvImageEnhancement::initCMvImageEnhancement()
{
	m_signalEnable = false;

	//��ʼ�����ж����˵�
	initMenuByTest();

	//���ü��������
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//���û�ͼ
	ui->checkBox_valuTrig->setChecked(true);

	m_signalEnable = true;
}

void CMvImageEnhancement::initMenuByTest()
{
	//��ʼ��ͼƬ��Դ�˵�
	m_pBlackAndWhiteImageMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pBlackAndWhiteImageMenuData);
}

void CMvImageEnhancement::slotClickPushButton(int row, int col)
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
void CMvImageEnhancement::soltMenuTriggered(QAction* action)
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
void CMvImageEnhancement::slotGetDetectorNameValue()
{
	if (m_signalEnable) {
		QString strText = ui->plainTextEdit_funcName->toPlainText();
		int nLength = strText.length();
		for (int index = 0; index < nLength; index++)
		{
			if (strText[index] == '\n') {
				ui->plainTextEdit_funcName->blockSignals(true);
				strText.remove("\n");
				qDebug() << "��ȡ���������" << strText;
				ui->plainTextEdit_funcName->setPlainText(strText);
				ui->plainTextEdit_funcName->blockSignals(false);
			}
		}
	}
}

//��ȡ���ü����ѡ����Ϣ
void CMvImageEnhancement::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ���ü����ѡ����Ϣ" << ui->checkBox_enableFunc->isChecked();
	}
}

/*===============================================================================================*\
**=======================================�������ҳ��ۺ���======================================**
\*===============================================================================================*/
//��ȡ��������ѡ����Ϣ
void CMvImageEnhancement::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ��������ѡ����Ϣ" << ui->checkBox_valuTrig->isChecked();
	}
}

/*===============================================================================================*\
**======================================�������ۺ���=============================================**
\*===============================================================================================*/
//��� �Ŵ�
void CMvImageEnhancement::slotAmplifyThePictureIsClick()
{
	qDebug() << "�Ŵ󱻵���";
}

//��� ��С
void CMvImageEnhancement::slotShrinkThePictureIsClick()
{
	qDebug() << "��С������";
}

//��� ��óߴ�
void CMvImageEnhancement::slotBestSizeOfPictureIsClick()
{
	qDebug() << "��óߴ类����";
}

//��� ����ROI
void CMvImageEnhancement::slotLockROIIsClick()
{
	qDebug() << "����ROI������";
}

//��� ����
void CMvImageEnhancement::slotOnceIsClick()
{
	qDebug() << "���α�����";
}

//��� ȷ��
void CMvImageEnhancement::slotMakeSureIsClick()
{
	qDebug() << "ȷ��������";
}

//��� ȡ��
void CMvImageEnhancement::slotCancelIsClick()
{
	qDebug() << "ȡ��������";
}

