#include "CMvColorImagesCut.h"
#include "ui_CMvColorImagesCut.h"
#include <QTableWidgetItem>
#include "CMvSecondLevelMenu.h"
#include <QDebug>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

CMvColorImagesCut * CMvColorImagesCut::s_pcolorImages = nullptr;

CMvColorImagesCut::CMvColorImagesCut(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::CMvColorImagesCut)
{
	ui->setupUi(this);
	setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
	setWindowModality(Qt::WindowModal);

	m_iRow = -1;
	m_iCol = -1;
	//���õ�Ԫ�� �ȿ�
	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("��ɫͼƬ");

	m_pSecondLevelMenu = new CMvSecondLevelMenu;
	//��ʼ�����ж����˵�
	initMenuByTest();

	////��ʼ��ʾ�ü�ͼƬ��ť
	//initPushButton();

	//�㷨ѡ�񴥷�
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//���ݲ�ɫͼƬ�˵�����ѡ�����õ�Ԫ����ʾ����
	connect(m_pColorImagesMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//������������˵�����ѡ�����õ�Ԫ����ʾ����
	connect(m_pCoordinateInputMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//�����ʾ�ü�ͼƬ��ť
	connect(ui->pushbutton_cuttingPicture, SIGNAL(clicked()), this, SLOT(soltCuttingPictureClick()));

	//��ȡ���������
	connect(ui->plainTextEdit_funcName_2, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//��ȡ���ü����ѡ����Ϣ
	connect(ui->checkBox_enableFunc_2, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	//���ROI��Դѡ���ȡѡ����Ϣ
	connect(ui->comboBox_imageSource_3, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetROISourcesValue(int)));

	//��ȡ�Լ�����ѡ����Ϣ
	connect(ui->checkBox_roiCreat_2, SIGNAL(clicked(bool)), this, SLOT(slotGetCreateYourselfValue(bool)));

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

	/*===============================================================================================*\
	**====================================��Ĥ�����ź���۵�����=====================================**
	\*===============================================================================================*/
	//��ȡ����������Ĥ
	connect(ui->comboBox_dEtectionMask, SIGNAL(currentIndexChanged(int)), this, SLOT(slotMaskOfDetectionAreaValue(int)));

	//��ȡ�༭��ʽ
	connect(ui->comboBox_lightOutputIo_7, SIGNAL(activated(int)), this, SLOT(slotEditModeValue(int)));

	//��ȡ���ʳߴ� 
	connect(ui->spinBox_lightTime_3, SIGNAL(valueChanged(int)), this, SLOT(slotBrushSizeValue(int)));

	//��������Ĥ
	connect(ui->pushButton_maskNull_2, SIGNAL(clicked()), this, SLOT(slotEmptyMaskIsClick()));

	//����ڸ�����
	connect(ui->pushButton_maskAll_2, SIGNAL(clicked()), this, SLOT(slotCoverUpEverythingClick()));

	//��������޸�
	connect(ui->pushButton_saveMask_2, SIGNAL(clicked()), this, SLOT(slotSaveChangesClick()));


	//��ȡ��������ѡ����Ϣ
	connect(ui->checkBox_valuTrig_4, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//���ùرմ���ʱ�ͷ���Դ
	setAttribute(Qt::WA_DeleteOnClose);
}

//��������
CMvColorImagesCut::~CMvColorImagesCut()
{
	qDebug() << "��������";

	if (m_pSecondLevelMenu)
	{
		delete m_pSecondLevelMenu;
		m_pSecondLevelMenu = nullptr;
	}

	//if (m_pColorImagesMenu)
	//{
	//	for (int index = 0; index < m_pColorImagesMenu->actions().size(); index++)
	//	{
	//		delete m_pColorImagesMenu->actions()[0]->menu();
	//	}
	//	delete m_pColorImagesMenu;
	//	m_pColorImagesMenu = nullptr;
	//}

	//if (m_pCoordinateInputMenu)
	//{
	//	for (int index = 0; index < m_pCoordinateInputMenu->actions().size(); index++)
	//	{
	//		delete m_pCoordinateInputMenu->actions()[0]->menu();
	//	}
	//	delete m_pCoordinateInputMenu;
	//	m_pCoordinateInputMenu = nullptr;
	//}

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

//��ʵ��
CMvColorImagesCut * CMvColorImagesCut::Instance()
{
	if (s_pcolorImages == nullptr)
	{
		s_pcolorImages = new CMvColorImagesCut;
	}
	return s_pcolorImages;
}

//�ͷ��ڴ�
void CMvColorImagesCut::destory()
{
	if (s_pcolorImages)
	{
		delete s_pcolorImages;
		s_pcolorImages = nullptr;
	}
}

////��ʼ����ť
//void CMvColorImagesCut::initPushButton()
//{
//	m_pPushbutton_cuttingPicture = new QPushButton(this);
//	m_pPushbutton_cuttingPicture->setText(tr("��ʾ�ü�ͼ��"));
//
//	ui->tableWidget_input->setCellWidget(0, 2, m_pPushbutton_cuttingPicture);
//
//}


//��ʼ�������˵�
void CMvColorImagesCut::initMenuByTest()
{
	//��ʼ��ͼƬ��Դ�˵�
	m_pColorImagesMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_ColorImagesMenuData);

	//��ʼ��ROI��Դ�˵�
	m_pCoordinateInputMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pCoordinateInputMenuData);
}

//���ݵ��λ��ѡ�񵯿�
void CMvColorImagesCut::slotClickPushButton(int row, int col)
{
	qDebug() << "λ��ȷ��";
	//������tabelWidget�����λ���жϸõ����Ĳ˵�
	if (col == 1)
	{
		switch (row)
		{
		case 0:
			m_pColorImagesMenu->move(cursor().pos());
			m_pColorImagesMenu->show();
			ui->tableWidget_input->item(0, 0)->setBackground(Qt::yellow);
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

	//��¼�������������
	m_iRow = row;
	m_iCol = col;
}

//�˵��������
void CMvColorImagesCut::soltMenuTriggered(QAction* action)
{
	//���õ��������ʾ����
	QString showInfoText;
	QVector<CMvSecondLevelMenu::cyAction*> allMenuData;
	QTableWidgetItem *pTableItem = ui->tableWidget_input->item(m_iRow, m_iCol);

	qDebug() << "����";
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
	 //������ʾ����Ϊѡ������
	pTableItem->setText(showInfoText);

	//��ʼ����������
	m_iRow = -1;
	m_iCol = -1;
}

//�����ʾ�ü�ͼƬ��ť
void CMvColorImagesCut::soltCuttingPictureClick()
{
	if (m_signalEnable)
	{
		qDebug() << "�����ʾ�ü�ͼƬ��ť";
	}
}


/*===============================================================================================*\
**======================================�������ۺ���=============================================**
\*===============================================================================================*/
//��� �Ŵ�
void CMvColorImagesCut::slotAmplifyThePictureIsClick()
{
	qDebug() << "�Ŵ󱻵���";
	//pushButton_zoomIn
}

//��� ��С
void CMvColorImagesCut::slotShrinkThePictureIsClick()
{
	qDebug() << "��С������";
	//pushButton_zoomOut
}

//��� ��óߴ�
void CMvColorImagesCut::slotBestSizeOfPictureIsClick()
{
	qDebug() << "��óߴ类����";
	//pushButton_zoomBest
}

//��� ����ROI
void CMvColorImagesCut::slotLockROIIsClick()
{
	qDebug() << "����ROI������";
	//pushButton_lockRoiMove
}

//��� ����
void CMvColorImagesCut::slotOnceIsClick()
{
	qDebug() << "���α�����";
	//pushButton_ones
}

//��� ȷ��
void CMvColorImagesCut::slotMakeSureIsClick()
{
	qDebug() << "ȷ��������";
	//pushButton_ensure
}

//��� ȡ��
void CMvColorImagesCut::slotCancelIsClick()
{
	qDebug() << "ȡ��������";
	//pbPrev_cancel
}

/*===============================================================================================*\
**====================================��������ҳ��ۺ���=========================================**
\*===============================================================================================*/
//��ȡ���������
void CMvColorImagesCut::slotGetDetectorNameValue()
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
void CMvColorImagesCut::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ���ü����ѡ����Ϣ" << ui->checkBox_enableFunc_2->isChecked();
	}
}

//��ȡROI��Դ
void CMvColorImagesCut::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "��ȡROI��Դѡ��" << ui->comboBox_imageSource_3->itemText(index);
	}
}

//��ȡ�Լ�����ѡ����Ϣ
void CMvColorImagesCut::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ�Լ�����ѡ����Ϣ" << ui->checkBox_roiCreat_2->isChecked();
	}
}

/*===============================================================================================*\
**=======================================��Ĥ���òۺ���==========================================**
\*===============================================================================================*/
//��ȡ����������Ĥ ��ֵ
void CMvColorImagesCut::slotMaskOfDetectionAreaValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ����������Ĥ" << ui->comboBox_dEtectionMask->itemText(Index) << " " << Index;

		if (Index == 0) {
			ui->widget_3->setEnabled(false);
		}
		else {
			ui->widget_3->setEnabled(true);
		}
	}
}

//��ȡ�༭��ʽ ��ֵ
void CMvColorImagesCut::slotEditModeValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ�༭��ʽ" << ui->comboBox_lightOutputIo_7->itemText(Index) << " " << Index;

		if (Index == 0) {//������Ĥ����
			m_maskCount++;
			qDebug() << "��ѡ��������Ĥ,��ǰ��Ĥ����Ϊ:" << m_maskCount;

		}
		else if (Index == 1) {//������Ĥ����
			m_maskCount--;
			if (m_maskCount < 0) {
				m_maskCount = 0;
			}
			qDebug() << "��ѡ��ɾ����Ĥ,��ǰ��Ĥ����Ϊ:" << m_maskCount;
		}

		if (m_maskCount == 0) {
			ui->pushButton_maskNull_2->setEnabled(false);
		}
		else {
			ui->pushButton_maskNull_2->setEnabled(true);
		}
	}
}

//��ȡ���ʳߴ� ��ֵ
void CMvColorImagesCut::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ���ʳߴ�" << ui->spinBox_lightTime_3->value() << " " << Value;
	}
}

//��������Ĥ
void CMvColorImagesCut::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "�����Ĥ������,��ǰ��Ĥ����Ϊ:" << m_maskCount;
		ui->pushButton_maskNull_2->setEnabled(false);
	}
}

//����ڸ�����
void CMvColorImagesCut::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "�ڸ����б�����";
	}
}

//��������޸�
void CMvColorImagesCut::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "�����޸ı�����";
	}
}


/*===============================================================================================*\
**=======================================�������ҳ��ۺ���======================================**
\*===============================================================================================*/
//��ȡ��������ѡ����Ϣ
void CMvColorImagesCut::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ��������ѡ����Ϣ" << ui->checkBox_valuTrig_4->isChecked();

		ui->pushbutton_cuttingPicture->setEnabled(State);
		ui->label_cuttingPicture->setEnabled(State);
	}
}