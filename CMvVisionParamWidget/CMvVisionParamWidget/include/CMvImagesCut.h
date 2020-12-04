#ifndef CMV_IMAGES_CUT
#define CMV_IMAGES_CUT


#include <QtWidgets/QWidget>
#include <QPushButton> 
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvImagesCut;
}

class CMvImagesCut : public QWidget
{
    Q_OBJECT

public:
	////��ʼ����ť
	//void initPushButton();

	//��ʵ��
	static CMvImagesCut * Instance();

	//�ͷ��ڴ�
	static void destroy();

	//��ʼ������
	void initCMvImagesCut();

	void initMenuByTest();

private slots:
	/*===============================================================================================*\
	**======================================�������òۺ���===========================================**
	\*===============================================================================================*/
	//��ȡ���������
	void slotGetDetectorNameValue();

	//��ȡ���ü����ѡ����Ϣ
	void slotGetEnableDetectorValue(bool state);

	//��ȡROI��Դ
	void slotGetROISourcesValue(int index);

	//��ȡ�Լ�����ѡ����Ϣ
	void slotGetCreateYourselfValue(bool state);


	//���ݵ��λ��ѡ�񵯿�
	void slotClickPushButton(int row, int col);

	//�˵��������
	void soltMenuTriggered(QAction* action);


	/*===============================================================================================*\
	**======================================�������ۺ���=============================================**
	\*===============================================================================================*/
	//��� �Ŵ�
	void slotAmplifyThePictureIsClick();

	//��� ��С
	void slotShrinkThePictureIsClick();

	//��� ��óߴ�
	void slotBestSizeOfPictureIsClick();

	//��� ����ROI
	void slotLockROIIsClick();

	//��� ����
	void slotOnceIsClick();

	//��� ȷ��
	void slotMakeSureIsClick();

	//��� ȡ��
	void slotCancelIsClick();

	/*===============================================================================================*\
	**=======================================��Ĥ���òۺ���==========================================**
	\*===============================================================================================*/
	//����������Ĥ ��ֵ
	void slotMaskOfDetectionAreaValue(int Index);

	//��ȡ�༭��ʽ ��ֵ
	void slotEditModeValue(int Index);

	//��ȡ���ʳߴ� ��ֵ
	void slotBrushSizeValue(int Value);

	//��������Ĥ
	void slotEmptyMaskIsClick();

	//����ڸ�����
	void slotCoverUpEverythingClick();

	//��������޸�
	void slotSaveChangesClick();

	/*===============================================================================================*\
	**=======================================�������ҳ��ۺ���======================================**
	\*===============================================================================================*/
	//��ȡ��������ѡ����Ϣ
	void slotGetStartUpDrawingValue(bool State);

private:
    Ui::CMvImagesCut * ui;
	
	static CMvImagesCut*  s_pimagesCut;

	CMvImagesCut(QWidget *parent = Q_NULLPTR);
	//��������
	~CMvImagesCut();

	bool m_signalEnable;

	int m_maskCount;//��¼��Ĥ����
	// ��¼��ǰ�����λ��
	int m_iRow;
	int m_iCol;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//������

	QMenu* m_pColorImagesMenu;//��ɫͼ��˵�
	QMenu* m_pCoordinateInputMenu;//��������˵�

	QVector<CMvSecondLevelMenu::cyAction*>  m_ColorImagesMenuData;//��ɫͼ��˵�
	QVector<CMvSecondLevelMenu::cyAction*>  m_pCoordinateInputMenuData;//������������
};

#endif // ifndef 