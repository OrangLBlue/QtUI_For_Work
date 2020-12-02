#ifndef CMV_BLACK_AND_WHITE_CONVERSION_COLOR
#define CMV_BLACK_AND_WHITE_CONVERSION_COLOR

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvBlackAndWhiteConversionColor;
}

class CMvBlackAndWhiteConversionColor : public QWidget
{
    Q_OBJECT

public:
	static CMvBlackAndWhiteConversionColor* Instance();

	static void destroy();

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
    Ui::CMvBlackAndWhiteConversionColor *ui;

	static CMvBlackAndWhiteConversionColor * s_pBlackAndWhiteConversionColor;

	CMvBlackAndWhiteConversionColor(QWidget *parent = Q_NULLPTR);
	~CMvBlackAndWhiteConversionColor();

	bool m_signalEnable;

	// ��¼��ǰ�����λ��
	int m_iRow;
	int m_iCol;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//������

	QMenu* m_pBlackAndWhiteImageMenu;//�ڰ�ͼ��˵�

	QVector<CMvSecondLevelMenu::cyAction*>  m_pBlackAndWhiteImageMenuData;//�ڰ�ͼ��˵�����

};

#endif