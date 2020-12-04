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
	////初始化按钮
	//void initPushButton();

	//单实例
	static CMvImagesCut * Instance();

	//释放内存
	static void destroy();

	//初始化数据
	void initCMvImagesCut();

	void initMenuByTest();

private slots:
	/*===============================================================================================*\
	**======================================输入设置槽函数===========================================**
	\*===============================================================================================*/
	//获取检测器名称
	void slotGetDetectorNameValue();

	//获取启用检测器选中信息
	void slotGetEnableDetectorValue(bool state);

	//获取ROI来源
	void slotGetROISourcesValue(int index);

	//获取自己创建选中信息
	void slotGetCreateYourselfValue(bool state);


	//根据点击位置选择弹框
	void slotClickPushButton(int row, int col);

	//菜单动作点击
	void soltMenuTriggered(QAction* action);


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
	**=======================================掩膜设置槽函数==========================================**
	\*===============================================================================================*/
	//检测区域的掩膜 数值
	void slotMaskOfDetectionAreaValue(int Index);

	//获取编辑方式 数值
	void slotEditModeValue(int Index);

	//获取画笔尺寸 数值
	void slotBrushSizeValue(int Value);

	//点击清空掩膜
	void slotEmptyMaskIsClick();

	//点击掩盖所有
	void slotCoverUpEverythingClick();

	//点击保存修改
	void slotSaveChangesClick();

	/*===============================================================================================*\
	**=======================================结果绘制页面槽函数======================================**
	\*===============================================================================================*/
	//获取启动绘制选中信息
	void slotGetStartUpDrawingValue(bool State);

private:
    Ui::CMvImagesCut * ui;
	
	static CMvImagesCut*  s_pimagesCut;

	CMvImagesCut(QWidget *parent = Q_NULLPTR);
	//析构函数
	~CMvImagesCut();

	bool m_signalEnable;

	int m_maskCount;//记录掩膜数量
	// 记录当前点击的位置
	int m_iRow;
	int m_iCol;

	CMvSecondLevelMenu *m_pSecondLevelMenu;//定义类

	QMenu* m_pColorImagesMenu;//彩色图像菜单
	QMenu* m_pCoordinateInputMenu;//坐标输入菜单

	QVector<CMvSecondLevelMenu::cyAction*>  m_ColorImagesMenuData;//彩色图像菜单
	QVector<CMvSecondLevelMenu::cyAction*>  m_pCoordinateInputMenuData;//坐标输入数据
};

#endif // ifndef 