#ifndef CMV_ALGITHM_PROCESSING
#define CMV_ALGITHM_PROCESSING

#include <QtWidgets/QWidget>
#include "CMvSecondLevelMenu.h"

namespace Ui {
	class CMvAlgorithmProcessing;
}

class CMvAlgorithmProcessing : public QWidget
{
	Q_OBJECT
public:
    
	//单列
	static CMvAlgorithmProcessing * Instance();
	
	//释放内存
	static void destroy();

	//初始化数据
	void initCMvAlgorithmProcessing();

	void initMenuByTest();

private slots:
	//选择模板大小
	void slotChangeTemplateSize(int index);

	//选择算法处理选择
	void slotChangeAlgorithmSelection(int index);

	//根据点击位置选择弹框
	void slotClickPushButton(int row, int col);

	//菜单动作点击
	void soltMenuTriggered(QAction* action);

	/*===============================================================================================*\
	**=======================================结果绘制页面槽函数======================================**
	\*===============================================================================================*/
	//获取启动绘制选中信息
	void slotGetStartUpDrawingValue(bool State);

	/*===============================================================================================*\
	**======================================功能栏槽函数=============================================**
	\*===============================================================================================*/
	//点击 放大
	void slotAmplifyThePictureIsClick();

	//点击 缩小
	void slotShrinkThePictureIsClick();

	//点击 最好尺寸
	void slotBestSizeOfPictureIsClick();

	//点击 锁定ROI
	void slotLockROIIsClick();

	//点击 单次
	void slotOnceIsClick();

	//点击 确定
	void slotMakeSureIsClick();

	//点击 取消
	void slotCancelIsClick();

	/*===============================================================================================*\
	**======================================输入设置槽函数===========================================**
	\*===============================================================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

private:
    Ui::CMvAlgorithmProcessing * ui;

	static CMvAlgorithmProcessing * s_pCMvAlgorithmProcessing;

	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	bool m_signalEnable;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImageMenu;//彩色图像菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_pColorImageMenuData;//彩色图像菜单数据

	CMvAlgorithmProcessing(QWidget *parent = Q_NULLPTR);
	~CMvAlgorithmProcessing();
};

#endif