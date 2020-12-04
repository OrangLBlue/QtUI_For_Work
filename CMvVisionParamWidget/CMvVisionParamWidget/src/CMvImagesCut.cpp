#include "CMvImagesCut.h"
#include "ui_CMvImagesCut.h"
#include <QTableWidgetItem>
#include "CMvSecondLevelMenu.h"
#include <QDebug>

#ifdef _MSC_VER
#pragma execution_character_set("utf-8") //set encoding character
#endif //_MSC_VER

////����QComboBox�ؼ�������������
//void QComboBox::wheelEvent(QWheelEvent *e)
//{
//
//}
//
////����SpinBox�ؼ�������������
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
	//���õ�Ԫ�� �ȿ�
	ui->tableWidget_input->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ui->tableWidget_input->setItem(0, 1, new QTableWidgetItem);
	ui->tableWidget_input->item(0, 1)->setBackground(Qt::red);
	ui->tableWidget_input->item(0, 1)->setText("ĳ������������");
	
	m_maskCount = 0;

	m_pSecondLevelMenu = new CMvSecondLevelMenu;
	//��ʼ������
	initCMvImagesCut();

	////��ʼ��ʾ�ü�ͼƬ��ť
	//initPushButton();

	//�㷨ѡ�񴥷�
	connect(ui->tableWidget_input, SIGNAL(cellClicked(int, int)), this, SLOT(slotClickPushButton(int, int)));

	//���ݲ�ɫͼƬ�˵�����ѡ�����õ�Ԫ����ʾ����
	connect(m_pColorImagesMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//������������˵�����ѡ�����õ�Ԫ����ʾ����
	connect(m_pCoordinateInputMenu, SIGNAL(triggered(QAction*)), this, SLOT(soltMenuTriggered(QAction*)));

	//��ȡ���������
	connect(ui->plainTextEdit_funcName, SIGNAL(textChanged()), this, SLOT(slotGetDetectorNameValue()));

	//��ȡ���ü����ѡ����Ϣ
	connect(ui->checkBox_enableFunc, SIGNAL(clicked(bool)), this, SLOT(slotGetEnableDetectorValue(bool)));

	//���ROI��Դѡ���ȡѡ����Ϣ
	connect(ui->comboBox_imageSource, SIGNAL(currentIndexChanged(int)), this, SLOT(slotGetROISourcesValue(int)));

	//��ȡ�Լ�����ѡ����Ϣ
	connect(ui->checkBox_roiCreat, SIGNAL(clicked(bool)), this, SLOT(slotGetCreateYourselfValue(bool)));

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
	connect(ui->comboBox_editMode, SIGNAL(activated(int)), this, SLOT(slotEditModeValue(int)));

	//��ȡ���ʳߴ� 
	connect(ui->spinBox_lightTime, SIGNAL(valueChanged(int)), this, SLOT(slotBrushSizeValue(int)));

	//��������Ĥ
	connect(ui->pushButton_maskNull, SIGNAL(clicked()), this, SLOT(slotEmptyMaskIsClick()));

	//����ڸ�����
	connect(ui->pushButton_maskAll, SIGNAL(clicked()), this, SLOT(slotCoverUpEverythingClick()));

	//��������޸�
	connect(ui->pushButton_saveMask, SIGNAL(clicked()), this, SLOT(slotSaveChangesClick()));


	//��ȡ��������ѡ����Ϣ
	connect(ui->checkBox_valuTrig, SIGNAL(clicked(bool)), this, SLOT(slotGetStartUpDrawingValue(bool)));

	//���ùرմ���ʱ�ͷ���Դ
	//setAttribute(Qt::WA_DeleteOnClose);
}

//��������
CMvImagesCut::~CMvImagesCut()
{
	qDebug() << "��������";

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

//��ʵ��
CMvImagesCut * CMvImagesCut::Instance()
{
	if (s_pimagesCut == nullptr)
	{
		s_pimagesCut = new CMvImagesCut;
	}
	return s_pimagesCut;
}

//�ͷ��ڴ�
void CMvImagesCut::destroy()
{
	if (s_pimagesCut)
	{
		delete s_pimagesCut;
		s_pimagesCut = nullptr;
	}
}


//��ʼ������
void CMvImagesCut::initCMvImagesCut()
{
	m_signalEnable = false;

	//��ʼ�����ж����˵�
	initMenuByTest();

	//���ü��������
	ui->plainTextEdit_funcName->setPlainText("");
	ui->checkBox_enableFunc->setChecked(true);

	//����ROI��Դ
	ui->comboBox_imageSource->setCurrentIndex(0);
	ui->checkBox_roiCreat->setChecked(true);

	//������Ĥ
	ui->comboBox_dEtectionMask->setCurrentIndex(0);
	ui->comboBox_editMode->setCurrentIndex(0);
	ui->spinBox_lightTime->setValue(5);

	if (ui->comboBox_dEtectionMask->currentIndex() == 0) {
		ui->widget_Mask->setEnabled(false);
	}
	else {
		ui->widget_Mask->setEnabled(false);
	}

	//���û�ͼ
	ui->checkBox_valuTrig->setChecked(false);

	m_signalEnable = true;
}


////��ʼ����ť
//void CMvImagesCut::initPushButton()
//{
//	m_pPushbutton_cuttingPicture = new QPushButton(this);
//	m_pPushbutton_cuttingPicture->setText(tr("��ʾ�ü�ͼ��"));
//
//	ui->tableWidget_input->setCellWidget(0, 2, m_pPushbutton_cuttingPicture);
//
//}

//��ʼ�������˵�
void CMvImagesCut::initMenuByTest()
{
	//��ʼ��ͼƬ��Դ�˵�
	m_pColorImagesMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_ColorImagesMenuData);

	//��ʼ��ROI��Դ�˵�
	m_pCoordinateInputMenu = m_pSecondLevelMenu->initMenuByTest(ui->tableWidget_input, m_pCoordinateInputMenuData);
}

//���ݵ��λ��ѡ�񵯿�
void CMvImagesCut::slotClickPushButton(int row, int col)
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
void CMvImagesCut::soltMenuTriggered(QAction* action)
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


/*===============================================================================================*\
**======================================�������ۺ���=============================================**
\*===============================================================================================*/
//��� �Ŵ�
void CMvImagesCut::slotAmplifyThePictureIsClick()
{
	qDebug() << "�Ŵ󱻵���";
	//pushButton_zoomIn
}

//��� ��С
void CMvImagesCut::slotShrinkThePictureIsClick()
{
	qDebug() << "��С������";
	//pushButton_zoomOut
}

//��� ��óߴ�
void CMvImagesCut::slotBestSizeOfPictureIsClick()
{
	qDebug() << "��óߴ类����";
	//pushButton_zoomBest
}

//��� ����ROI
void CMvImagesCut::slotLockROIIsClick()
{
	qDebug() << "����ROI������";
	//pushButton_lockRoiMove
}

//��� ����
void CMvImagesCut::slotOnceIsClick()
{
	qDebug() << "���α�����";
	//pushButton_ones
}

//��� ȷ��
void CMvImagesCut::slotMakeSureIsClick()
{
	qDebug() << "ȷ��������";
	//pushButton_ensure
}

//��� ȡ��
void CMvImagesCut::slotCancelIsClick()
{
	qDebug() << "ȡ��������";
	//pbPrev_cancel
}

/*===============================================================================================*\
**====================================��������ҳ��ۺ���=========================================**
\*===============================================================================================*/
//��ȡ���������
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
				qDebug() << "��ȡ���������" << strText;
				ui->plainTextEdit_funcName->setPlainText(strText);
				ui->plainTextEdit_funcName->blockSignals(false);
			}
		}
	}
}

//��ȡ���ü����ѡ����Ϣ
void CMvImagesCut::slotGetEnableDetectorValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ���ü����ѡ����Ϣ" << ui->checkBox_enableFunc->isChecked();
	}
}

//��ȡROI��Դ
void CMvImagesCut::slotGetROISourcesValue(int index)
{
	if (m_signalEnable) {
		qDebug() << "��ȡROI��Դѡ��" << ui->comboBox_imageSource->itemText(index);
	}
}

//��ȡ�Լ�����ѡ����Ϣ
void CMvImagesCut::slotGetCreateYourselfValue(bool state)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ�Լ�����ѡ����Ϣ" << ui->checkBox_roiCreat->isChecked();
	}
}

/*===============================================================================================*\
**=======================================��Ĥ���òۺ���==========================================**
\*===============================================================================================*/
//��ȡ����������Ĥ ��ֵ
void CMvImagesCut::slotMaskOfDetectionAreaValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ����������Ĥ" << ui->comboBox_dEtectionMask->itemText(Index) << " " << Index;

		if (Index == 0) {
			ui->widget_Mask->setEnabled(false);
		}
		else {
			ui->widget_Mask->setEnabled(true);
		}
	}
}

//��ȡ�༭��ʽ ��ֵ
void CMvImagesCut::slotEditModeValue(int Index)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ�༭��ʽ" << ui->comboBox_editMode->itemText(Index) << " " << Index;

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
			ui->pushButton_maskNull->setEnabled(false);
		}
		else {
			ui->pushButton_maskNull->setEnabled(true);
		}
	}
}

//��ȡ���ʳߴ� ��ֵ
void CMvImagesCut::slotBrushSizeValue(int Value)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ���ʳߴ�" << ui->spinBox_lightTime->value() << " " << Value;
	}
}

//��������Ĥ
void CMvImagesCut::slotEmptyMaskIsClick()
{
	if (m_signalEnable) {
		m_maskCount = 0;
		qDebug() << "�����Ĥ������,��ǰ��Ĥ����Ϊ:" << m_maskCount;
		ui->pushButton_maskNull->setEnabled(false);
	}
}

//����ڸ�����
void CMvImagesCut::slotCoverUpEverythingClick()
{
	if (m_signalEnable) {
		qDebug() << "�ڸ����б�����";
	}
}

//��������޸�
void CMvImagesCut::slotSaveChangesClick()
{
	if (m_signalEnable) {
		qDebug() << "�����޸ı�����";
	}
}


/*===============================================================================================*\
**=======================================�������ҳ��ۺ���======================================**
\*===============================================================================================*/
//��ȡ��������ѡ����Ϣ
void CMvImagesCut::slotGetStartUpDrawingValue(bool State)
{
	if (m_signalEnable) {
		qDebug() << "��ȡ��������ѡ����Ϣ" << ui->checkBox_valuTrig->isChecked();

	}
}