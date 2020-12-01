#ifndef CMV_COLOR_IMAGES
#define CMV_COLOR_IMAGES


#include <QtWidgets/QWidget>
#include <QPushButton> 
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvColorImagesCut;
}

class CMvColorImagesCut : public QWidget
{
    Q_OBJECT

public:
	////��ʼ����ť
	//void initPushButton();

	//��ʵ��
	static CMvColorImagesCut * Instance();

	//�ͷ��ڴ�
	static void destory();

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

	//����ü�ͼƬ
	void soltCuttingPictureClick();


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
    Ui::CMvColorImagesCut * ui;
	
	static CMvColorImagesCut*  s_pcolorImages;

	CMvColorImagesCut(QWidget *parent = Q_NULLPTR);
	//��������
	~CMvColorImagesCut();

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