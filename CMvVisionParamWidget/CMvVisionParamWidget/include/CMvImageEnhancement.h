#ifndef CMV_IMAGE_ENGANCEMENT
#define CMV_IMAGE_ENGANCEMENT

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvImageEnhancement;
}

class CMvImageEnhancement : public QWidget
{
    Q_OBJECT

public:
	static CMvImageEnhancement* Instance();

	static void destroy();

	//��ʼ������
	void initCMvImageEnhancement();

	void initMenuByTest();

private slots:

	//���ݵ��λ��ѡ�񵯿�
	void slotClickPushButton(int row, int col);

	//�˵��������
	void soltMenuTriggered(QAction* action);


	/*===============================================================================================*\
	**=======================================�������ҳ��ۺ���======================================**
	\*===============================================================================================*/
	//��ȡ��������ѡ����Ϣ
	void slotGetStartUpDrawingValue(bool State);

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
	**======================================�������òۺ���===========================================**
	\*===============================================================================================*/
	//��ȡ���������
	void slotGetDetectorNameValue();

	//��ȡ���ü����ѡ����Ϣ
	void slotGetEnableDetectorValue(bool state);

private:
    Ui::CMvImageEnhancement *ui;

	static CMvImageEnhancement * s_pCMvImageEnhancement;

	CMvImageEnhancement(QWidget *parent = Q_NULLPTR);
	~CMvImageEnhancement();

	bool m_signalEnable;

	// ��¼��ǰ�����λ��
	int m_iRow;
	int m_iCol;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//������

	QMenu* m_pBlackAndWhiteImageMenu;//�ڰ�ͼ��˵�

	QVector<CMvSecondLevelMenu::cyAction*>  m_pBlackAndWhiteImageMenuData;//�ڰ�ͼ��˵�����

};

#endif